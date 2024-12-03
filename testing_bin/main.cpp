#include "wrapper_offset.h"
#include <string.h>
#include <unistd.h>
//#include <memory>

// for testing
// create a big AST, get the memory size used
// then use this implementation, compare the memory size
// measure the speed to traverse the tree ?
// use a microbenchmarking lib ?

struct BigClass {
    char c[1024];
public:
    int test;
    BigClass(int test) : test(test) {}
};

static int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}


static int get_mem_usage(){
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int main(){


    printf("mem usage at start : %d\n", get_mem_usage());

    /*printf("pid : %d\n", getpid());
    int i = 0;
    while (1){
        if (i % 110 == 0){
            char* a = (char*)malloc(1);
            //printf("new mem usage : %d\n", get_mem_usage());
        }
        i++;
    }*/

    Arena arena = Arena(100 * 1024 * 1024, false);


    /*for (int i = 0; i < 3500000; i++){
        BigClass* a_ptr = arena.allocate<BigClass>();
        memset(a_ptr->c, 1, 1);

        printf("arena ptr : %p\n", a_ptr);
    }*/

    /*for (int i = 0; i < 35; i++){
        int a_offset = arena.allocate_offset<BigClass>();
        ((BigClass*)arena.ptr_from_offset(a_offset))->c[0] = 'c';
        printf("arena offset : %d\n", a_offset);
    }*/

    for (int i = 0; i < 35; i++){
        auto ast_offset = ASTPtr<BigClass>::create_new(&arena, 10);
        ast_offset.get(&arena)->test = i;
        printf("arena offset : %d\n", ast_offset.get_offset());
    }

    printf("mem usage at end : %d\n", get_mem_usage());

}