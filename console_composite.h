#ifndef CONSOLE_COMPOSITE_H_
#define CONSOLE_COMPOSITE_H_
#include "console.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef union Console * Console_Ptr_T;

#define CSet_Params Console_Ptr
#include "cset.h"
#undef CSet_Params

typedef union Console_Composite
{
    union Console_Composite_Class _private * _private vtbl;
    struct Object Object;
    struct
    {
        union Console Console;
        CSet_Console_Ptr_T _private console_set;
    };
}Console_Composite_T;


typedef union Console_Composite_Class
{
    struct
    {
        struct Console_Class Console;
        void (*_private insert)(union Console_Composite * const, Console_Ptr_T const);
        void (*_private erase)(union Console_Composite * const, Console_Ptr_T const);
    };
    struct Class Class;
}Console_Composite_Class_T;

extern union Console_Composite_Class _private Console_Composite_Class;

extern void Populate_Console_Composite(union Console_Composite * const console, 
    char const * const name,
    char const * const usage,
    FILE * const in,
    FILE * const out,
    Console_Ptr_T * const consoles,
    size_t const n_consoles);

#ifdef __cplusplus
}
#endif

#endif /*CONSOLE_COMPOSITE_H_*/