#ifndef ARGS_H
# define ARGS_H

# include <stdlib.h>
# include <stdint.h>

# define ARG_OK		0
# define ARG_NOK	1
# define ARG_WSP	" \t\v\n\r"

typedef struct		s_arg
{
	char						short_name;
	char*						long_name;
	char*						desc;
	char*						_hash;
	char**					values;
	int8_t					optional;
	int8_t					mult;
	int8_t					mentionned;
	struct s_arg*		right;
	struct s_arg*		left;
}									t_arg;

typedef struct	s_token
{
	char*							value;
	struct s_token*		next;
	struct s_token*		prev;
}							t_token;

typedef struct		s_parser
{
	t_arg*											args;
	t_arg*											last_mentionned;
	t_arg*											_iterator;
	int (*_add_arg)(struct s_parser*, t_arg*);
	int (*_add_long)(struct s_parser*, t_token*);
	int (*_add_short)(struct s_parser*, t_token*);
	t_arg* (*iterate_next)(struct s_parser*);
	void (*iterate_reinit)(struct s_parser*);
}								t_parser;

t_parser*				create_args_parser(void);
t_arg*					create_arg(char short_name, char* long_name, char* desc, int8_t optional, int8_t mult);
int							add_arg(t_parser* p, char short_name, char* long_name, char* desc, int8_t optional, int8_t mult);
int							add_long(t_parser* p, t_token* tok);
int							add_short(t_parser* p, t_token* tok);
int							parse_args(t_parser* p, int argc, char** argv);
void						print_args(t_parser* p);
char*						get_arg_sng_val(t_parser* p, char* arg_name);
int							parse(t_parser* p, int argc, char **argv);
t_token*				create_tokens_string(int argc, char** argv);

char*						_hash_argname(char short_name, char* long_name);

t_arg*					_linkedlist_iterate_next(t_parser* p);
void						_linkedlist_iterate_reinit(t_parser* p);
int							_linkedlist_add_arg(t_parser *p, t_arg* new_arg);
int							_linkedlist_add_long(t_parser* p, t_token* tok);
int							_linkedlist_add_short(t_parser* p, t_token* tok);

# endif
