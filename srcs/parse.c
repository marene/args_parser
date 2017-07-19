#include <stdio.h>
#include <string.h>
#include "args.h"

static int8_t		is_long(char* str)
{
	return ((str && strlen(str) > 2 && strstr(str, "--") == str));
}

static int8_t		is_short(char* str)
{
	return ((str && strlen(str) > 1 && str[0] == '-' && str[1] != '-'));
}

static int8_t		is_arg(char* str)
{
	return (is_long(str) || is_short(str));
}

int							parse(t_parser* p, int argc, char** argv)
{
	t_token*	toks;
	t_token*	it;

	toks = create_tokens_string(argc, argv);
	it = toks;
	while (it)
	{
		if ()
		it = it->next;
	}
	return ARG_OK;
}
