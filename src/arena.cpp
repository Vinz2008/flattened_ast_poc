#include "arena.h"

long PAGE = 4096;
long HUGE_PAGE = 2 * 1024 * 1024;
// https://github.com/rust-lang/rust/blob/master/compiler/rustc_arena/src/lib.rs could be useful

Arena::Arena(){
    // TODO
}

int Arena::get_offset(void* expr_ptr){

}

template <typename T> 
T* Arena::allocate(){

}