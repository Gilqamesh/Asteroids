internal inline i32
_Heap_Parent(i32 Index)
{
    return ((Index - 1) / 2);
}

internal inline i32
_Heap_Child_Left(i32 Index)
{
    return (2 * Index + 1);
}

internal inline i32
_Heap_Child_Right(i32 Index)
{
    return (2 * Index + 2);
}

internal inline void
_Swap_TimedEvents(timed_event *EventA, timed_event *EventB)
{
    // check assembly code for this and memcpy
    timed_event Tmp = *EventA;
    *EventA = *EventB;
    *EventB = Tmp;
}

internal void
PushTimedEvent(game_state *GameState, u32 Target, timed_event_handler *Handler, timed_event_type Type, u32 CustomData = 0)
{
    ASSERT(GameState->TimedEventHeapSize < ArrayCount(GameState->TimedEventHeap));

    timed_event Event = {};
    Event.Target = Target;
    Event.Handler = Handler;
    Event.Type = Type;
    Event.CustomData = CustomData;

    GameState->TimedEventHeap[GameState->TimedEventHeapSize] = Event;

    // Swim operation on heap to restore heap property
    i32 Index = GameState->TimedEventHeapSize++;
    i32 ParentIndex = _Heap_Parent(Index);
    while (Index && GameState->TimedEventHeap[Index].Target < GameState->TimedEventHeap[ParentIndex].Target)
    {
        _Swap_TimedEvents(GameState->TimedEventHeap + ParentIndex, GameState->TimedEventHeap + Index);
        Index = ParentIndex;
        ParentIndex = _Heap_Parent(ParentIndex);
    }
}

internal timed_event
PopTimedEvent(game_state *GameState)
{
    ASSERT(GameState->TimedEventHeapSize);

    timed_event Result = GameState->TimedEventHeap[0];
    GameState->TimedEventHeap[0] = GameState->TimedEventHeap[--GameState->TimedEventHeapSize];

    // Sink operation on heap to restore heap property
    if (GameState->TimedEventHeapSize)
    {
        b32 Swapped;
        i32 SwapIndex;
        i32 Index = 0;
        do
        {
            Swapped = false;
            SwapIndex = 0;
            i32 LeftChildIndex = _Heap_Child_Left(Index);
            i32 RightChildIndex = _Heap_Child_Right(Index);
            if (LeftChildIndex < GameState->TimedEventHeapSize)
            {
                if (RightChildIndex < GameState->TimedEventHeapSize)
                {
                    if (GameState->TimedEventHeap[LeftChildIndex].Target < GameState->TimedEventHeap[RightChildIndex].Target)
                    {
                        SwapIndex = LeftChildIndex;
                    }
                    else
                    {
                        SwapIndex = RightChildIndex;
                    }
                }
                else
                {
                    SwapIndex = LeftChildIndex;
                }
            }
            if (SwapIndex && GameState->TimedEventHeap[SwapIndex].Target < GameState->TimedEventHeap[Index].Target)
            {
                Swapped = true;
                _Swap_TimedEvents(GameState->TimedEventHeap + SwapIndex, GameState->TimedEventHeap + Index);
                Index = SwapIndex;
            }
        } while (Swapped);
    }

    return (Result);
}

internal inline timed_event
PeakTimedEvent(game_state *GameState)
{
    ASSERT(GameState->TimedEventHeapSize);

    return (GameState->TimedEventHeap[0]);
}
