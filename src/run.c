#include "../headers/compile.h"

bool run = 1;
#include <unistd.h>


int main(int argc, char **args) {
    C_setup *setup = init_compiler(argc, args);

    return 0;
}
