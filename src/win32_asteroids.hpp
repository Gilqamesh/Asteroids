#ifndef WIN32_ASTEROIDS_HPP
# define WIN32_ASTEROIDS_HPP

# include <Windows.h>
# include "platform.hpp"

typedef void (*update_and_render_fn)(game_memory *GameMemory, game_window *GameWindow);
typedef void (*load_resources_fn)(game_memory *GameMemory, game_window *GameWindow);
typedef void (*setup_windows_fn)(game_memory *GameMemory, game_window *GameWindow);

struct win32_game_code
{
    HMODULE GameCodeDLL;
    FILETIME DLLLastWriteTime;

    setup_windows_fn SetupWindows;
    update_and_render_fn UpdateAndRender;
    load_resources_fn LoadResources;

    b32 IsValid;
};

#endif
