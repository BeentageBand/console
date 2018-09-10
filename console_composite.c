#define COBJECT_IMPLEMENTATION
#define Dbg_FID CONSOLE_FID, 1
#include "dbg_log.h"
#include "console_composite.h"

#define CSet_Params Console_Ptr
#include "cset.c"
#undef CSet_Params

static int console_cmp(Console_Ptr_T const * a, Console_Ptr_T const * b);
static void console_composite_delete(struct Object * const obj);
static void console_composite_on_call(union Console * const, int const, char const ** const);
static void console_composite_insert(union Console_Composite * const, Console_Ptr_T const);
static void console_composite_erase(union Console_Composite * const, Console_Ptr_T const);

union Console_Composite_Class Console_Composite_Class = 
{{
    {
        {console_composite_delete, NULL},
        NULL,
        NULL,
        NULL
    },
    console_composite_insert,
    console_composite_erase
}};

static union Console_Composite Console_Composite = {NULL};

int console_cmp(Console_Ptr_T const * a, Console_Ptr_T const * b)
{
    return strcmp((*a)->name, (*b)->name);
}

void console_composite_delete(struct Object * const obj)
{}

void console_composite_on_call(union Console * const console, int const argc, char const ** const argv)
{
    union Console_Composite * const this = _cast(Console_Composite, console);
    Isnt_Nullptr(this, );
    if(argc > 0)
    {
        union Console keycon = {NULL};
        keycon.name = argv[0];
        Console_Ptr_T * found = this->console_set.vtbl->find(&this->console_set, &keycon);
        if(found != this->console_set.vtbl->end(&this->console_set))
        {
            (*found)->vtbl->on_call(*found, argc - 1, argv + 1);
        }
        else
        {
            console->vtbl->usage(console);
        }
    }
    else
    {
        console->vtbl->usage(console);
    }
}

void console_composite_insert(union Console_Composite * const this, Console_Ptr_T const console)
{
    this->console_set.vtbl->erase(&this->console_set, console);
}

void console_composite_erase(union Console_Composite * const this, Console_Ptr_T const console)
{
    this->console_set.vtbl->insert(&this->console_set, console);
}

void Populate_Console_Composite(union Console_Composite * const this, 
    char const * const name,
    char const * const usage,
    FILE * const in,
    FILE * const out,
    Console_Ptr_T * const console_buff,
    size_t const n_consoles)
{
    if(NULL == Console_Composite.vtbl)
    {
        Populate_Console(&Console_Composite.Console,
            NULL,
            NULL,
            NULL,
            NULL);
        Object_Init(&Console_Composite.Object,
            &Console_Composite_Class.Class,
            sizeof(Console_Composite_Class));
        Console_Class.on_call = console_composite_on_call;
        Console_Composite.console_set.vtbl = NULL;
    }
    Populate_Console(&this->Console, name, usage, in, out);
    this->vtbl = &Console_Composite_Class;
    Populate_CSet_Cmp_Console_Ptr(&this->console_set,
        console_buff,
        n_consoles,
        (CSet_Cmp_T) console_cmp);
}
