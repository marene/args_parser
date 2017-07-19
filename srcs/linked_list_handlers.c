#include <string.h>
#include "args.h"

static int8_t		is_lower(t_arg* src, t_arg* ref)
{
	return (!src->long_name || (ref->long_name && strcmp(src->long_name, ref->long_name) < 0));
}

static int8_t		is_greater(t_arg* src, t_arg* ref)
{
	return (!ref->long_name || (src->long_name && strcmp(src->long_name, ref->long_name) >= 0));
}

static int8_t		is_between(t_arg* new, t_arg* min, t_arg* max)
{
	return (is_lower(min, new) && (!max || is_greater(max, new)));
}

int							_linkedlist_add_arg(t_parser* p, t_arg* new_arg)
{
	t_arg*		it;

	if (p->args == NULL || is_lower(new_arg, p->args))
	{
		new_arg->left = p->args;
		p->args = new_arg;
		return (ARG_OK);
	}
	it = p->args;
	while (it)
	{
		if (is_between(new_arg, it, it->left))
		{
			new_arg->left = it->left;
			it->left = new_arg;
			return (ARG_OK);
		}
		it = it->left;
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

int				_linked_list_add_short(t_parser* p, t_token* tok)
{
	t_arg*	it;

	it = p->args;
	while (it)
	{
		if (strcmp(it->short_name, tok->value[1]))
		{
			p->last_mentionned = it;
			return (ARG_OK);
		}
		it = it->left;
	}
	return (ARG_NOK);
}

int				_linked_list_add_long(t_parser* p, t_token* tok)
{
	char*		equal;
	char*		arg;
	char*		value;
	size_t	len;
	t_arg*	it;

	equal = strstr(tok->value, "=");
	if (equal)
	{
		len = equal - (tok->value + strlen("--"));
		arg = strndup(tok->value + 2, len);
		value = strdup(equal + 1); // TODO what if --arg= and nothing after equal
	}
	else
	{
		arg = strdup(tok->value + 2);
		value = NULL;
		len = 0;
	}
	it = p->args;
	while (it)
	{
		if (it->long_name && strcmp(arg, it->long_name))
		{
			// TODO add value to it->values if any
			free(arg);
			free(value);
			return (ARG_OK);
		}
		it = it->left;
	}
	return (ARG_NOK);
}
