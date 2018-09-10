#define COBJECT_IMPLEMENTATION
#define Dbg_FID CONSOLE_FID, 0
#include <stdarg.h>
#include "dbg_log.h"
#include "console.h"

static void console_delete(struct Object * const obj);
static void console_on_call(union Console * const this, int const argc, char const ** const argv);
static void console_printf(union Console * const this, char const * const fmt, ...);
static void console_usage(union Console * const this);

struct Console_Class Console_Class =
{
    {console_delete, NULL},
    console_on_call,
    console_printf
};

static union Console Console = {NULL};

void console_delete(struct Object * const obj)
{

}

void console_on_call(union Console * const this, int const argc, char const ** const argv)
{
    Dbg_Warn("%s: implement", __func__);
    this->vtbl->usage(this);
}

void console_printf(union Console * const this, char const * const fmt, ...) 
{
    va_list va;
    va_start(va, fmt);
    vfprintf(this->out, fmt, va);
    va_end(va);
}

void console_usage(union Console * const this)
{
    this->vtbl->printf(this, this->usage, this->name, "[]");
}

void Populate_Console(union Console * const this, char const * const name, char const * const usage, FILE * const in, FILE * const out)
{
    if(NULL == Console.vtbl)
    {
        Console.vtbl = & Console_Class;
        Console.in = NULL;
        Console.out = NULL;
        Console.name = "0";
        Console.usage = "%s: OPTIONS %s";
    }
    _clone(this, Console);
    if(name)
        this->name = name;
    if(usage)
        this->usage = usage;
    this->in = in;
    this->out = out;
}