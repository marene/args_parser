#include <stdio.h>
#include "args.h"

int			parse(t_parser* p, int argc, char** argv)
{
	t_token*	toks;
	t_token*	it;

	toks = create_tokens_string(argc, argv);
	it = toks;
	while (it)
	{

		it = it->next;
	}
	return ARG_OK;
}
