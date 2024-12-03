#include "arena.h"
#include <sys/mman.h>
#include <assert.h>

int PAGE = 4096;
int HUGE_PAGE = 2 * 1024 * 1024;
// https://github.com/rust-lang/rust/blob/master/compiler/rustc_arena/src/lib.rs could be useful


ArenaChunk::ArenaChunk(int size) : size(size), used(0) {
    this->ptr = (char*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    assert(this->ptr != MAP_FAILED);
    printf("new chunk of size %d allocated at %p\n", this->size, this->ptr);
}

Arena::Arena() : should_grow(true) {
    this->arenaChunks = std::vector<ArenaChunk>({ ArenaChunk(PAGE) });
}


Arena::Arena(int initial_size, bool should_grow) : should_grow(should_grow) {
    this->arenaChunks = std::vector<ArenaChunk>({ ArenaChunk(initial_size) });
}

Arena::~Arena(){
    for (int i = 0; i < this->arenaChunks.size(); i++){
        auto& chunk = arenaChunks.at(i);
        munmap((void*)chunk.ptr, chunk.size);
        printf("unmapped page at %p\n", chunk.ptr);
    }
}

ArenaChunk& Arena::add_chunk(){
    int new_size = this->arenaChunks.back().size * 2;
    if (new_size > HUGE_PAGE){
        new_size = HUGE_PAGE;
    }
    this->arenaChunks.push_back(ArenaChunk(new_size));

    return this->arenaChunks.back();
}

void* Arena::ptr_from_offset(int offset){
    if (arenaChunks.size() == 1){
        return (void*)(arenaChunks.begin()->ptr + (long)offset);
    }


    int pos_arena = -1;
    int size_arenas = 0;
    for (int i = 0; i < arenaChunks.size(); i++){
        if (size_arenas + arenaChunks[i].size > offset){
            pos_arena = i;
            break;
        }
        size_arenas += arenaChunks[i].size;
    }
    if (pos_arena == -1){
        fprintf(stderr, "Offset %d out of bounds\n", offset);
        exit(1);
    }

    int local_arena_offset = offset - size_arenas;

    return (void*)(arenaChunks[pos_arena].ptr + (long)local_arena_offset);
}

/*int Arena::get_offset(void* expr_ptr){
    
    return 0;
}*/