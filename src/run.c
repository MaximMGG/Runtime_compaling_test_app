#include "../headers/compile.h"

bool run = 1;
#include <unistd.h>


int main(int argc, char **args) {
    C_setup *setup = init_compiler(argc, args);
    if (setup == NULL) {
        fprintf(stderr, "Init Compiling arror");
        exit(1);
    }
    int enter;

    while(run) {
        compile(setup);
        system("./a.out");
        sleep(1);
    }

    return 0;
}
