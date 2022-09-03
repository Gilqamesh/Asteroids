#ifndef WORLD_CHUNK_HPP
# define WORLD_CHUNK_HPP

struct world_entity_block
{
    world_entity_block *Next;
    u32 EntityIndex[16];
    u32 EntityCount;
};

struct world_chunk
{
    i32 X;
    i32 Y;
    i32 Z;
    world_entity_block FirstBlock;
    world_chunk *Next;
};

struct world
{
    entity Entities[8192];
    u32 EntitiesSize;
    world_chunk Chunks[16384];
};

#endif
