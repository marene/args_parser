#include <string.h>
#include <stdio.h>
#include "args.h"

static t_token*		create_token(char* value)
{
	t_token*	ret;

	if ((ret = malloc(sizeof(t_token))))
	{
		ret->value = strdup(value);
		ret->next = NULL;
		ret->prev = NULL;
		printf("create_token: [%s]\n", ret->value);
	}
	else
		printf("create_token(\"%s\") failed\n", value);
	return (ret);
}

t_token*					create_tokens_string(int argc, char** argv)
{
	char*			whitespace;
	t_token*	newroot = NULL;
	t_token*	newtok = NULL;
	t_token*	tmp;

	while (--argc > 0)
	{
		tmp = create_token(argv[argc]);
		if (tmp)
		{ // I shoudl add an "else" to this, delete the whole linked list, but i'm too much of a lazy bastard for this
			tmp->prev = newtok;
			if (newtok)
			{
				newtok->next = tmp;
				newtok = newtok->next;
			}
			else
				newtok = tmp;
			if (!newroot)
				newroot = tmp;
		}
	}
	return (newroot);
}
