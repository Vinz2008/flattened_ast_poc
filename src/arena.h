class ArenaChunk {

};


class Arena {
    void* ptr;
    
public:
    Arena();
    template <typename T>
    T* allocate();
    void* get_ptr(){
        return ptr;
    }

    int get_offset(void* expr_ptr);
};