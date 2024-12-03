#include "arena.h"
#include <stdio.h>
#include <string.h>

// for testing
// create a big AST, get the memory size used
// then use this implementation, compare the memory size
// measure the speed to traverse the tree ?
// use a microbenchmarking lib ?

struct BigClass {
    char c[1024];
};

int main(){
    Arena arena = Arena();

    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    for (int i = 0; i < 3500000; i++){
        BigClass* a_ptr = arena.allocate<BigClass>();
        memset(a_ptr->c, 1, 1);

        printf("arena ptr : %p\n", a_ptr);
    }

    fflush(stdout);
}