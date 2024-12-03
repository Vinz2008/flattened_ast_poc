#include <vector>
#include <stdio.h>
#include <stdlib.h>

class ArenaChunk {
public:
    char* ptr;
    int size;
    int used;
    ArenaChunk(int size);
};


class Arena {
private:
    bool should_grow; // if more, replace with flags var
    std::vector<ArenaChunk> arenaChunks;
    
    ArenaChunk& add_chunk();

public:

    // TODO : does returning a pair reduce performance (TODO : verify this ?)
    template <typename T> 
    std::pair<T*, int> allocate_internal(){
        ArenaChunk& last_chunk = this->arenaChunks.back();
        if (last_chunk.size <= last_chunk.used + sizeof(T)){
            if (!should_grow){
                fprintf(stderr, "No space left in not growing arena\n");
                exit(1);
            }
            last_chunk = this->add_chunk();
        }
        int previous_chunks_size = 0;
        for (int i = 0; i < this->arenaChunks.size()-1; i++){
            previous_chunks_size += this->arenaChunks[i].size;
        }
        int offset = previous_chunks_size + last_chunk.used;

        T* data = (T*) ((long)last_chunk.ptr + (long)last_chunk.used);
        last_chunk.used += sizeof(T);

        return std::make_pair(data, offset);
    }
    Arena();
    Arena(int initial_size, bool should_grow);
    ~Arena();
    template <typename T>
    T* allocate(){
        return allocate_internal<T>().first;
    }
    template <typename T>
    int allocate_offset(){
        return allocate_internal<T>().second;
    }

    void* ptr_from_offset(int offset);

    //int get_offset(void* expr_ptr);
};