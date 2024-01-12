#include "../headers/compile.h"



int main(int argc, char **args) {
    C_setup *setup = init_compiler(argc, args);
    int enter;

    while((enter = getchar()) != 'q') {
        compile(setup);
        system("./a.out");
    }

    return 0;
}
