#include "args.h"
#include <string.h> //TODO replace libc calls by libft calls

t_arg*		create_arg(char short_name, char* long_name, char* desc, int8_t optional, int8_t mult)
{
	t_arg*	ret;

	ret = (!short_name && (!long_name || !strlen(long_name))) ? NULL : malloc(sizeof(t_arg));
	if (ret)
	{
		ret->short_name = short_name;
		ret->long_name = (!long_name) ? NULL : strdup(long_name);
		ret->_hash = _hash_argname(short_name, long_name);
		ret->desc = strdup(desc);
		ret->optional = optional;
		ret->mult = mult;
	}
	return ret;
}
