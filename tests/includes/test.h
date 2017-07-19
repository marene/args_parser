/* file: minunit.h */
#ifndef TEST_H
# define TEST_H

	//ALL CREDITS TO MINUNIT

# define mu_assert(message, test) do { if (!(test)) return message; } while (0)
# define mu_run_test(test) do { char *message = test(); tests_ran++; if (message) return message; } while (0)
# define mu_run_subtest(test) do { char *message = test(); subtests_ran++; if (message) return message; } while (0)

#endif
