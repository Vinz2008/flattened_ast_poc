#include "arena.h"
#include <sys/mman.h>
#include <assert.h>
#include <stdio.h>

int PAGE = 4096;
int HUGE_PAGE = 2 * 1024 * 1024;
// https://github.com/rust-lang/rust/blob/master/compiler/rustc_arena/src/lib.rs could be useful


ArenaChunk::ArenaChunk(int size) : size(size), used(0) {
    this->ptr = (char*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    assert(this->ptr != MAP_FAILED);
    printf("new chunk of size %d allocated at %p\n", this->size, this->ptr);
}

Arena::Arena(){
    this->arenaChunks = std::vector<ArenaChunk>({ ArenaChunk(PAGE) });
    // TODO
}

Arena::~Arena(){
    for (int i = 0; i < this->arenaChunks.size(); i++){
        auto& chunk = arenaChunks.at(i);
        munmap((void*)chunk.get_ptr(), chunk.size);
        printf("unmapped page at %p\n", chunk.get_ptr());
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

int Arena::get_offset(void* expr_ptr){
    return 0;
}