NAME=						libarg_parser.a
CC=							gcc
AR=							ar
SRCS_DIR=				./srcs/
INCLUDES_DIR=		./includes/
OBJS_DIR=				./objs/
TESTS_DIR=			./tests/
SRCS=						_hash_argname.c\
								add_arg.c\
								add_long.c\
								add_short.c\
								create_arg.c\
								create_args_parser.c\
								linked_list_handlers.c\
								parse.c\
								print_args.c\
								token.c
OBJS=						$(SRCS:.c=.o)
CFLAGS=					-I$(INCLUDES_DIR) -g -c -o
LDFLAGS=				-r

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	mkdir -p $@

$(NAME): $(addprefix $(OBJS_DIR), $(OBJS))
	$(AR) $(LDFLAGS) $(NAME) $^

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) $@ $<

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests:
	make -C $(TESTS_DIR)

.PHONY: all clean fclean re tests
