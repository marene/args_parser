#include "args.h"

t_parser*			create_args_parser(void)
{
	t_parser*		ret;

	ret = malloc(sizeof(t_parser));
	if (ret)
	{
		ret->args = NULL;
		ret->last_mentionned = NULL;
		ret->_iterator = NULL;
		ret->_add_arg = _linkedlist_add_arg;
		ret->_add_long = _linkedlist_add_long;
		ret->_add_short = _linkedlist_add_short;
		ret->iterate_next = _linkedlist_iterate_next;
		ret->iterate_reinit = _linkedlist_iterate_reinit;
	}
	return (ret);
}
