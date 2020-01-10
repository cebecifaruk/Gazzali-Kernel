#ifndef     __MODULE_H
#define     __MODULE_H

struct kmod {
    void (*init)();
    void (*exit)();
};


#define MODULE (init_function,exit_function) struct kmod testserver = { \
    .init = init_function,                                                       \
    .exit = exit_function                                                        \
};




#endif
