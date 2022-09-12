#ifndef EVENT_HPP
# define EVENT_HPP

enum timed_event_type
{
    TimedEvent_Invalid,
    TimedEvent_SplashScreenSound,
    TimedEvent_SplashToMain,
    TimedEvent_Ufo,
    TimedEvent_Womp,
    TimedEvent_Womp2,
    TimedEvent_Size
};

# define TIMED_EVENT_HANDLER(name) void name(game_state *GameState, game_window *GameWindow, raylib_wrapper_code *RL)
typedef TIMED_EVENT_HANDLER(timed_event_handler);
struct timed_event
{
    u32 Target;
    timed_event_type Type;
    timed_event_handler *Handler;

    u32 CustomData;
};

#endif
