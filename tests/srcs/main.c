#include <stdio.h>
#include <string.h>
#include "test.h"
#include "args.h"

int tests_ran = 0;

static char*		test_create_args_parser()
{
	t_parser*	p = create_args_parser();
	mu_assert("parser is NULL", p != NULL);
	free(p);
	return 0;
}

static char*		test_add_arg()
{
	t_parser*	p = create_args_parser();

	add_arg(p, 's', "sort", "toto", 1, 0);            // arg 0
	add_arg(p, 't', NULL, "short - no long", 1, 0);   // arg 1
	add_arg(p, 0, "foobar", "no short - long", 1, 0); // arg 2
	add_arg(p, 0, "", "no short - empty long", 1, 0); // arg 3
	add_arg(p, 0, NULL, "no short - no long", 1, 0);  // arg 4
	mu_assert("arg 0 not added", p->args != NULL);
	mu_assert("arg 1 not added", p->args->left != NULL);
	mu_assert("arg 2 not added", p->args->left->left != NULL);
	mu_assert("arg 3 added", p->args->left->left->left == NULL);
	mu_assert("arg 0 short not valid", p->args->short_name == 's');
	mu_assert("arg 0 long not valid", strcmp(p->args->long_name, "sort") == 0);
	mu_assert("arg 0 opt not valid", p->args->optional == 1);
	mu_assert("arg 0 mult not valid", p->args->left->mult == 0);
	mu_assert("arg 1 short not valid", p->args->left->short_name == 't');
	mu_assert("arg 1 long not valid", p->args->left->long_name == NULL);
	mu_assert("arg 1 opt not valid", p->args->left->optional == 1);
	mu_assert("arg 1 mult not valid", p->args->left->mult == 0);
	mu_assert("arg 2 short not valid", p->args->left->left->short_name == '\0');
	mu_assert("arg 2 long not valid", strcmp(p->args->left->left->long_name, "foobar") == 0);
	mu_assert("arg 2 opt not valid", p->args->left->left->optional == 1);
	mu_assert("arg 2 mult not valid", p->args->left->left->mult == 0);
	mu_assert("arg 0 hash not valid", strcmp(p->args->_hash, "ssort") == 0);
	mu_assert("arg 1 hash not valid", strcmp(p->args->left->_hash, "t") == 0);
	mu_assert("arg 2 hash not valid", strcmp(p->args->left->left->_hash, "foobar") == 0);
}

static char*		subtest_tokens()
{
	t_parser*		p = create_args_parser();
	t_token*		t = NULL;
	const int		argc = 4;
	char*				argv[4] = {"NOT AN ARG", "--foobar", "tata yoyo", "-test"};

	add_arg(p, 's', "sort", "toto", 1, 0);            // arg 0
	add_arg(p, 't', NULL, "short - no long", 1, 0);   // arg 1
	add_arg(p, 0, "foobar", "no short - long", 1, 0); // arg 2
	t = create_tokens_string(argc, argv);
	mu_assert("tokens string not generated", t != NULL);
	mu_assert("token 0 is invalid (-test)", strcmp(t->value, "-test") == 0);
	mu_assert("token 1 is invalid (tata yoyo)", strcmp(t->next->value, "tata yoyo") == 0);
	mu_assert("token 2 is invalid (--foobar)", strcmp(t->next->next->value, "--foobar") == 0);
	mu_assert("token 3 should not be generated", t->next->next->next == NULL);
}

static char*		test_parse()
{
	mu_run_test(subtest_tokens);
	return NULL;
}

static char*		all_tests()
{
	mu_run_test(test_create_args_parser);
	mu_run_test(test_add_arg);
	mu_run_test(test_parse);
	return NULL;
}

int		main(int argc, char** argv)
{
	char* results = all_tests();

	if (results)
	{
		printf("FAIL: %s\n", results);
		return(1);
	}
	printf("ALL TESTS PASSED (ran %d tests)\n", tests_ran);
	return (0);
	/*
	t_parser* p = create_args_parser();

	if (p != NULL)
	{
		printf("It worked out\n");
		add_arg(p, 's', "sort", "sort stuff", 1, 0);
		add_arg(p, 'b', "binary", "print binary data", 1, 0);
		add_arg(p, 'l', "long", "print long format", 1, 0);
		add_arg(p, 'v', "verbose", "outputs more verbose ", 1, 0);
		add_arg(p, 't', NULL, "short - no long", 1, 0);
		add_arg(p, 0, "foobar", "no short - long", 1, 0);
		add_arg(p, 0, "", "no short - empty long", 1, 0);
		add_arg(p, 0, NULL, "no short - no long", 1, 0);
		print_args(p);
		parse(p, argc, argv);
	}
	else
		printf("error");
		*/
}
