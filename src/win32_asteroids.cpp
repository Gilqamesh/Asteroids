#if defined(SINGLE_FILE_BUILD)
# include "raylib.h"
# include "platform.hpp"
# include "game_layer.cpp"
# include <cstdlib>
#else
# include "platform.hpp"
# include "win32_asteroids.hpp"
#endif

using namespace std;

#if !defined(SINGLE_FILE_BUILD)
inline FILETIME
Win32GetLastWriteTime(char *Filename)
{
    FILETIME LastWriteTime = {};

    WIN32_FILE_ATTRIBUTE_DATA Data = {};
    if (GetFileAttributesEx(Filename, GetFileExInfoStandard, &Data))
    {
        LastWriteTime = Data.ftLastWriteTime;
    }

    return (LastWriteTime);
}

internal win32_game_code
Win32LoadGameCode(char *SourceDLLName, char *TempDLLName, char *LockFileName)
{
    win32_game_code Result = {};

    WIN32_FILE_ATTRIBUTE_DATA Ignored;
    if (!GetFileAttributesEx(LockFileName, GetFileExInfoStandard, &Ignored))
    {
        Result.DLLLastWriteTime = Win32GetLastWriteTime(SourceDLLName);

        CopyFile(SourceDLLName, TempDLLName, FALSE);

        Result.GameCodeDLL = LoadLibraryA(TempDLLName);
        if (Result.GameCodeDLL)
        {
            Result.SetupWindows = (setup_windows_fn)GetProcAddress(Result.GameCodeDLL, "SetupWindows");
            Result.UpdateAndRender = (update_and_render_fn)GetProcAddress(Result.GameCodeDLL, "UpdateAndRender");
            Result.LoadResources = (load_resources_fn)GetProcAddress(Result.GameCodeDLL, "LoadResources");

            Result.IsValid = (Result.SetupWindows &&
                              Result.UpdateAndRender &&
                              Result.LoadResources);
        }
    }

    if (!Result.IsValid)
    {
        Result.SetupWindows = 0;
        Result.UpdateAndRender = 0;
        Result.LoadResources = 0;
    }

    return (Result);
}

internal void
Win32UnloadGameCode(win32_game_code *GameCode)
{
    if (GameCode->GameCodeDLL)
    {
        FreeLibrary(GameCode->GameCodeDLL);
        GameCode->GameCodeDLL = 0;
    }

    GameCode->IsValid = false;
    GameCode->UpdateAndRender = 0;
}
#endif

#include "platform_raylib_wrapper_loader.cpp"

#if defined(G_DEBUG)
#include <fstream>
#endif

#if defined(SINGLE_FILE_BUILD)
int main()
#else
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)
#endif
{
#if defined(G_DEBUG)
    ofstream file;
    file.open("cout.txt");
    streambuf *sbuf = cout.rdbuf();
    cout.rdbuf(file.rdbuf());
#endif

    game_memory GameMemory = {};
    GameMemory.PermanentStorageSize = Megabytes(64);
    GameMemory.TransientStorageSize = Gigabytes(1);
    u64 TotalStorageSize = GameMemory.PermanentStorageSize + GameMemory.TransientStorageSize;
#if defined(SINGLE_FILE_BUILD)
    GameMemory.PermanentStorage = malloc(TotalStorageSize);
#else
    GameMemory.PermanentStorage = VirtualAlloc(0, TotalStorageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#endif
    if (GameMemory.PermanentStorage == 0)
    {
        LOG("failed to allocate size of memory in bytes: " << TotalStorageSize);
        exit(1);
    }
    GameMemory.TransientStorage = (u8 *)GameMemory.PermanentStorage + GameMemory.PermanentStorageSize;
#if !defined(SINGLE_FILE_BUILD)
    win32_game_code Game = {};
#endif
    game_window GameWindow = {};

#if !defined(SINGLE_FILE_BUILD)
    GameMemory.RaylibWrapper = LoadRaylibWrapperDLL("raylib_wrapper.dll");
    char *SourceGameCodeDLLPath = "game_layer.dll";
    char *TempGameCodeDLLPath = "game_layer_temp.dll";
    char *GameCodeLockPath = "lock.tmp";
    Game = Win32LoadGameCode(SourceGameCodeDLLPath,
                             TempGameCodeDLLPath,
                             GameCodeLockPath);
    if (Game.SetupWindows)
    {
        Game.SetupWindows(&GameMemory, &GameWindow);
    }
    if (Game.LoadResources)
    {
        Game.LoadResources(&GameMemory, &GameWindow);
    }
#else
    GameMemory.RaylibWrapper = SingleFileRaylibWrapper();
    SetupWindows(&GameMemory, &GameWindow);
    LoadResources(&GameMemory, &GameWindow);
#endif

    GameMemory.IsRunning = true;
    while (GameMemory.IsRunning)
    {
#if defined(SINGLE_FILE_BUILD)
        UpdateAndRender(&GameMemory, &GameWindow);
#else
        FILETIME NewDLLWriteTime = Win32GetLastWriteTime(SourceGameCodeDLLPath);
        if (CompareFileTime(&NewDLLWriteTime, &Game.DLLLastWriteTime) != 0)
        {
            Win32UnloadGameCode(&Game);
            Game = Win32LoadGameCode(SourceGameCodeDLLPath,
                                     TempGameCodeDLLPath,
                                     GameCodeLockPath);
        }

        if (Game.UpdateAndRender)
        {
            Game.UpdateAndRender(&GameMemory, &GameWindow);
        }
#endif
    }

    return (0);
}
