#include <string.h>
#include "args.h"

# include <stdio.h>

/**
 * TODO find a better way to sort-insert into the linked list, i'm am absolutely not satisfied with this current version
 */
int				_linkedlist_add_arg(t_parser* p, t_arg* new_arg)
{
	t_arg*		iterator;
	t_arg*		tmp;

	if (p->args == NULL || !new_arg->long_name || (p->args->long_name && strcmp(new_arg->long_name, p->args->long_name) <= 0))
	{
		printf("inserted --%s at root\n", new_arg->long_name);
		new_arg->left = p->args;
		p->args = new_arg;
		return (ARG_OK);
	}
	iterator = p->args;
	while (iterator)
	{
		if ((iterator->long_name && strcmp(new_arg->long_name, iterator->long_name) > 0) || iterator->left == NULL)
		{
			printf("inserted --%s between --%s and --%s\n", new_arg->long_name, iterator->long_name, (iterator->left) ? iterator->left->long_name : "END");
			tmp = iterator->left;
			iterator->left = new_arg;
			new_arg->left = tmp;
			return ARG_OK;
		}
		else if (!iterator->long_name)
		{
			if (iterator->left->long_name && strcmp(iterator->left->long_name, new_arg->long_name) > 0)
			{
				printf("inserted --%s between --%s and --%s\n", new_arg->long_name, iterator->long_name, (iterator->left) ? iterator->left->long_name : "END");
				tmp = iterator->left;
				iterator->left = new_arg;
				new_arg->left = tmp; // TODO I'm not sure tmp is actually needed for all insertions operations, checkthat after you get some sleep
			}
			else
			{
				new_arg = iterator->left->left;
				iterator->left->left = new_arg;
			}
			return ARG_OK;
		}
		iterator = iterator->left;
	}
	return (ARG_NOK);
}

t_arg*		_linkedlist_iterate_next(t_parser* p)
{
	if (p->_iterator == NULL)
		p->_iterator = p->args;
	else
	{
		p->_iterator = p->_iterator->left;
	}
	return p->_iterator;
}

void			_linkedlist_iterate_reinit(t_parser* p)
{
	p->_iterator = NULL;
}
