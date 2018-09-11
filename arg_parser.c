/*
 * arg_parser.c
 *
 *  Created on: Sep 10, 2018
 *      Author: puch
 */
#define COBJECT_IMPLEMENTATION

#include "arg_parser.h"

static void arg_parser_delete(struct Object * const obj);
static char ** arg_parser_parse(union Arg_Parser * const this, size_t * const argc, FILE * const stream);
static size_t arg_parser_split(union Arg_Parser * const this, char const delim);

struct Arg_Parser_Class Arg_Parser_Class =
{
      {arg_parser_delete, NULL},
      arg_parser_parse
};

static char Line_Fmt[32];

static union Arg_Parser Arg_Parser = {NULL};

void arg_parser_delete(struct Object * const obj)
{}

char ** arg_parser_parse(union Arg_Parser * const this, size_t * const argc, FILE * const stream)
{
    size_t i = sprintf(Line_Fmt, "%lu", this->line_max_length);
    strcpy(Line_Fmt + i, "[^\n]");

    i = fscanf(stream, Line_Fmt, this->line);
    *argc = arg_parser_split(this, ' ');

    return this->argv;
}

size_t arg_parser_split(union Arg_Parser * const this, char const delim)
{
	char * i;
	char * begin;
	size_t argc;
	memset(this->argv, 0, this->max_argc);

	for(argc = 0, i = NULL, begin = this->line;
			NULL != i && argc < this->max_argc;
			++argc, begin = i)
	{
		i = strchr(begin, delim);
		if(NULL != i)
		{
			*i = '\0';
			++i;
		}
		this->argv[argc] = begin;
	}
	return argc;
}

void Populate_Arg_Parser(union Arg_Parser * const this,
      char * const line_buff,
      size_t const line_max_length,
      char ** const argv_buff,
      size_t const max_argc)
{
    if(NULL == Arg_Parser.vtbl)
    {
        Arg_Parser.vtbl = &Arg_Parser_Class;
    }
    _clone(this, Arg_Parser);
    this->line = line_buff;
    this->line_max_length = line_max_length;
    this->max_argc = max_argc;
    this->argv = argv_buff;
}




