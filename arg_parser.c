/*
 * arg_parser.c
 *
 *  Created on: Sep 10, 2018
 *      Author: puch
 */
#define COBJECT_IMPLEMENTATION
#define Dbg_FID CONSOLE_FID, 1
#include "dbg_log.h"
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
    memset(this->line, 0, this->line_max_length);

    size_t scan_size = fscanf(stream, Line_Fmt, this->line);
    Dbg_Info("%s: %d bytes read from stream =\"%s\"", __func__, scan_size, (scan_size)?this->line : "empty");

    *argc = 0;
    if(scan_size)
    {
        *argc = arg_parser_split(this, ' ');
    }
    return this->argv;
}

size_t arg_parser_split(union Arg_Parser * const this, char const delim)
{
	char * i;
	char * begin;
	size_t argc;
	memset(this->argv, 0, this->max_argc);

	for(argc = 0, i = this->line, begin = this->line;
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
    Dbg_Info("%s: %d args", __func__, argc);
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
    this->line_max_length = line_max_length - 1;
    this->max_argc = max_argc;
    this->argv = argv_buff;
    memset(Line_Fmt, 0, sizeof(Line_Fmt));
    size_t i = sprintf(Line_Fmt + 1, "%d", this->line_max_length);
    strcpy(Line_Fmt + 1 + i, "[^\n]");
    Line_Fmt[0] = '%';
    Dbg_Info("%s: scanf \"%s\"", __func__, Line_Fmt);
}




