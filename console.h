#ifndef CONSOLE_H_
#define CONSOLE_H_
#include "cobject.h"

#ifdef __cplusplus
extern "C"{
#endif
typedef union Console
{
    struct Console_Class _private * _private vtbl;
    struct
    {
        struct Object Object;
        char const * _private name;
        char const * _private usage;
        FILE * _private in;
        FILE * _private out;
    };
}Console_T;

typedef struct Console_Class
{
    struct Class Class;
    void (*_private on_call)(union Console * const, int const, char const ** const);
    void (*_private printf)(union Console * const, char const * const, ...); 
    void (*_private usage)(union Console * const);
}Console_Class_T;

extern struct Console_Class _private Console_Class;

extern void Populate_Console(union Console * const console,
    char const * const name,
    char const * const usage,
    FILE * const in,
    FILE * const out);

#ifdef __cplusplus
}
#endif
#endif /*CONSOLE_H_*/