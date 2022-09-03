#include "platform.hpp"
#include "win32_asteroids.hpp"
#include <fstream>

using namespace std;

inline FILETIME
Win32GetLastWriteTime(char *Filename)
{
    FILETIME LastWriteTime = {};

    WIN32_FILE_ATTRIBUTE_DATA Data = {};
    LINE();
    LOG(Filename);
    if (GetFileAttributesEx(Filename, GetFileExInfoStandard, &Data))
    {
        LINE();
        LastWriteTime = Data.ftLastWriteTime;
    }
    LINE();

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

#include "win32_raylib_wrapper_loader.cpp"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)
{
    ofstream file;
    file.open("cout.txt");
    streambuf *sbuf = cout.rdbuf();
    cout.rdbuf(file.rdbuf());

    game_memory GameMemory = {};
    GameMemory.PermanentStorageSize = Megabytes(64);
    GameMemory.TransientStorageSize = Gigabytes(1);
    u64 TotalStorageSize = GameMemory.PermanentStorageSize + GameMemory.TransientStorageSize;
    GameMemory.PermanentStorage = VirtualAlloc(0, TotalStorageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (GameMemory.PermanentStorage == 0)
    {
        LOG("VirtualAlloc failed to allocate size of memory in bytes: " << TotalStorageSize);
        exit(1);
    }
    GameMemory.TransientStorage = (u8 *)GameMemory.PermanentStorage + GameMemory.PermanentStorageSize;
    win32_game_code Game = {};
    game_window GameWindow = {};

    GameMemory.RaylibWrapper = LoadRaylibWrapperDLL("raylib_wrapper.dll");

    char *SourceGameCodeDLLPath = "GameLayer.dll";
    char *TempGameCodeDLLPath = "GameLayer_temp.dll";
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

    GameMemory.IsRunning = true;
    while (GameMemory.IsRunning)
    {
        LINE();
        FILETIME NewDLLWriteTime = Win32GetLastWriteTime(SourceGameCodeDLLPath);
        LINE();
        if (CompareFileTime(&NewDLLWriteTime, &Game.DLLLastWriteTime) != 0)
        {
            LINE();
            Win32UnloadGameCode(&Game);
            LINE();
            Game = Win32LoadGameCode(SourceGameCodeDLLPath,
                                     TempGameCodeDLLPath,
                                     GameCodeLockPath);
        }

        LINE();
        if (Game.UpdateAndRender)
        {
            LINE();
            Game.UpdateAndRender(&GameMemory, &GameWindow);
        }
        LINE();
    }

    return (0);
}
