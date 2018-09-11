/*
 * arg_parser.h
 *
 *  Created on: Sep 10, 2018
 *      Author: puch
 */

#ifndef ARG_PARSER_H_
#define ARG_PARSER_H_

#include "cobject.h"

union Console;

typedef union Arg_Parser
{
	struct Arg_Parser_Class _private * _private vtbl;
	struct
	{
		struct Object Object;
		char _private ** _private argv;
		char _private * _private line;
		size_t _private line_max_length;
		size_t _private max_argc;
	};
}Arg_Parser_T;

typedef struct Arg_Parser_Class
{
	struct Class Class;
	char ** (*_private parse)(union Arg_Parser * const, size_t * const, FILE * const);
}Arg_Parser_Class_T;

extern struct Arg_Parser_Class _private Arg_Parser_Class;

extern void Populate_Arg_Parser(union Arg_Parser * const parser,
		char * const line_buff,
		size_t const line_max_length,
		char ** const argv_buff,
		size_t const max_argc);

#endif /* ARG_PARSER_H_ */
