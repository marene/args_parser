#include "args.h"
#include <string.h>

char		*_hash_argname(char short_name, char* long_name)
{
	char*		hash;
	size_t	hash_len =  !!short_name + (!long_name) ? 0 : strlen(long_name);

	hash = malloc(hash_len + 1);
	hash[hash_len] = '\0';
	if (hash)
	{
		if (short_name)
			hash[0] = short_name;
		if (long_name)
			strcpy(&(hash[!!short_name]), long_name); //TODO make sure this is safe
	}
	return (hash);
}
