#include <stdio.h>
#include <string.h>
#include "test.h"
#include "args.h"

int tests_ran = 0;
int subtests_ran = 0;

static char*		test_create_args_parser()
{
	t_parser*	p = create_args_parser();
	mu_assert("parser is NULL", p != NULL);
	free(p);
	return 0;
}

static char*		subtest_add_arg()
{
	t_parser*	p = create_args_parser();

	add_arg(p, 'd', NULL, "-short +long", 1, 0);      // arg 0
	add_arg(p, 'a', "aaaa", "ok",  1, 0);             // arg 1
	add_arg(p, 'b', "bbbb", "ok", 1, 0);              // arg 2
	add_arg(p, '\0', "cccc", "+short -long", 1, 0);   // arg 3
	add_arg(p, '\0', "", "-short empty long", 1, 0);  // arg 4
	add_arg(p, '\0', NULL, "-short -long", 1, 0);     // arg 5
	print_args(p);
	mu_assert("arg 0 not added", p->args != NULL);
	mu_assert("arg 1 not added", p->args->left != NULL);
	mu_assert("arg 2 not added", p->args->left->left != NULL);
	mu_assert("arg 3 not added", p->args->left->left->left != NULL);
	mu_assert("arg 4 added", p->args->left->left->left->left == NULL);
	mu_assert("arg 0 short not valid", p->args->short_name == 'd');
	mu_assert("arg 0 long not valid", p->args->long_name == NULL);
	mu_assert("arg 0 opt not valid", p->args->optional == 1);
	mu_assert("arg 0 mult not valid", p->args->left->mult == 0);
	mu_assert("arg 1 short not valid", p->args->left->short_name == 'a');
	mu_assert("arg 1 long not valid", strcmp(p->args->left->long_name, "aaaa") == 0);
	mu_assert("arg 1 opt not valid", p->args->left->optional == 1);
	mu_assert("arg 1 mult not valid", p->args->left->mult == 0);
	mu_assert("arg 2 short not valid", p->args->left->left->short_name == 'b');
	mu_assert("arg 2 long not valid", strcmp(p->args->left->left->long_name, "bbbb") == 0);
	mu_assert("arg 2 opt not valid", p->args->left->left->optional == 1);
	mu_assert("arg 2 mult not valid", p->args->left->left->mult == 0);
	mu_assert("arg 3 short not valid", p->args->left->left->left->short_name == '\0');
	mu_assert("arg 3 long not valid", strcmp(p->args->left->left->left->long_name, "cccc") == 0);
	mu_assert("arg 3 opt not valid", p->args->left->left->left->optional == 1);
	mu_assert("arg 3 mult not valid", p->args->left->left->left->mult == 0);
	mu_assert("arg 0 hash not valid", strcmp(p->args->_hash, "d") == 0);
	mu_assert("arg 1 hash not valid", strcmp(p->args->left->_hash, "aaaaa") == 0);
	mu_assert("arg 2 hash not valid", strcmp(p->args->left->left->_hash, "bbbbb") == 0);
	mu_assert("arg 3 hashnot valid", strcmp(p->args->left->left->left->_hash, "cccc") == 0);
	return NULL;
}

static char*		subtest_sort_args()
{
	t_parser*	p = create_args_parser();

	add_arg(p, '\0', "cccc", "+short -long", 1, 0);   // arg 3
	add_arg(p, 'b', "bbbb", "ok", 1, 0);              // arg 2
	add_arg(p, 'd', NULL, "-short +long", 1, 0);      // arg 0
	add_arg(p, 'a', "aaaa", "ok",  1, 0);             // arg 1
	print_args(p);
	mu_assert("arg 0 not added", p->args != NULL);
	mu_assert("arg 1 not added", p->args->left != NULL);
	mu_assert("arg 2 not added", p->args->left->left != NULL);
	mu_assert("arg 3 not added", p->args->left->left->left != NULL);
	mu_assert("arg 0 short not valid", p->args->short_name == 'd');
	mu_assert("arg 1 short not valid", p->args->left->short_name == 'a');
	mu_assert("arg 2 short not valid", p->args->left->left->short_name == 'b');
	mu_assert("arg 3 short not valid", p->args->left->left->left->short_name == '\0');
	return NULL;
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
	return NULL;
}

static char*		test_parse()
{
	mu_run_subtest(subtest_tokens);
	return NULL;
}

static char*		test_add_arg()
{
	mu_run_subtest(subtest_add_arg);
	mu_run_subtest(subtest_sort_args);
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
	printf("ALL TESTS PASSED (ran %d tests, %d subtests)\n", tests_ran, subtests_ran);
	return 0;
}
