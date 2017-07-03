#include "args.h"

int				_linkedlist_add_arg(t_parser* p, t_arg* new_arg)
{
	t_arg*		iterator;

	if (p->args == NULL)
	{
		p->args = new_arg;
		return (ARG_OK);
	}
	iterator = p->args;
	while (iterator)
	{
		if (iterator->left == NULL)
		{
			iterator->left = new_arg;
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
