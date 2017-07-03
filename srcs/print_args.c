#include <stdio.h>
#include "args.h"

void			print_args(t_parser* p)
{
	t_arg*		iterator = NULL;

	while ((iterator = p->iterate_next(p)))
	{
		printf("-%c | --%s | %s | opt[%d] | mult[%d] -> [%s]\n", iterator->short_name, iterator->long_name, iterator->desc, iterator->optional, iterator->mult, iterator->_hash);
	}
}
