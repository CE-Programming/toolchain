#include <stdlib.h>

static struct quick_exit_function {
    struct quick_exit_function *next;
    void (*function)(void);
} *quick_exit_functions;

int at_quick_exit(void (*function)(void)) {
    struct quick_exit_function *quick_exit_function = malloc(sizeof(struct quick_exit_function));
    if (!quick_exit_function)
        return 1;
    quick_exit_function->next = quick_exit_functions;
    quick_exit_function->function = function;
    quick_exit_functions = quick_exit_function;
    return 0;
}

void quick_exit(int status) {
    while (quick_exit_functions) {
        struct quick_exit_function *quick_exit_function = quick_exit_functions;
        quick_exit_functions = quick_exit_function->next;
        void (*function)(void) = quick_exit_function->function;
        free(quick_exit_function);
        function();
    }
    _Exit(status);
}
