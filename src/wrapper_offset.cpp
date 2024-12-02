#include "arena.h"

// TODO : add a static check that T is Derived from ExprAST


template<class T>
class ASTPtr {
    int offset; // TODO : if there is multiple arena chunk like in the rust one, need to have a global offset and not a offset from the current chunk
public:
    ASTPtr(Arena* arena, T expr) {
        auto new_type_ptr = arena->allocate<T>();
        *new_type_ptr = expr;
        this->offset = arena->get_offset((void*)new_type_ptr);
    }
    T* get(Arena* arena){
        return (T*)(arena->get_ptr() + offset);
    }

    void destroy(){
        this->offset = 0; // just make the offset 0, the memory will be freed when the arena is destroyed 
    }
};