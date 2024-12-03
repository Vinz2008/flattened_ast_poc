#include "arena.h"

// TODO : add a static check that T is Derived from ExprAST

template<class T>
class ASTPtr {
    int offset; // TODO : if there is multiple arena chunk like in the rust one, need to have a global offset and not a offset from the current chunk
public:
    ASTPtr(Arena* arena, T expr) {
        std::pair<T*, int> new_expr = arena->allocate_internal<T>();
        *(new_expr.first) = expr;
        this->offset = new_expr.second;
    }
    T* get(Arena* arena){
        return (T*)arena->ptr_from_offset(offset);
    }

    void destroy(){
        this->offset = -1; // just make the offset -1, the memory will be freed when the arena is destroyed 
    }

    // for debug
    // remove it ? (TODO ?)
    int get_offset(){
        return offset;
    }

    template <class... Args>
    static ASTPtr<T> create_new(Arena* arena, Args&&... args){
        return ASTPtr<T>(arena, T(args...));
    }
};
