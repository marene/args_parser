#include "args.h"

int			add_arg(t_parser* p, char short_name, char* long_name, char *desc, int8_t optional, int8_t mult)
{
	t_arg*		new_arg;

	new_arg = create_arg(short_name, long_name, desc, optional, mult);
	if (new_arg)
		return (p->_add_arg(p, new_arg));
	return (ARG_OK);
}
