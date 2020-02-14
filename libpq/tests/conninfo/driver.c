/* file      : tests/conninfo/driver.c
 * license   : PostgreSQL License; see accompanying COPYRIGHT file
 */

/*
 * Include the upstream package test and rename it's main() function to test()
 * (see below for details).
 */
#define main test
#include <uri-regress.c>
#undef main

/*
 * Enable assertions.
 */
#ifdef NDEBUG
#  undef NDEBUG
#endif

#include <stdio.h>
#include <assert.h>
#include <string.h> /* strlen() */

/*
 * Usage: argv[0]
 *
 * Read connection info strings from STDIN and call upstream test main()
 * function for each of them. The function prints the parsed connection info to
 * stdout on success or error message to stderr on failure.
 */
int
main (int argc, char* argv[])
{
  assert (argc == 1);

  char s[1024];

  while (fgets (s, sizeof(s), stdin) != NULL)
  {
    /*
     * Print the conninfo string that will be tested.
     */
    printf ("trying %s", s);

    /*
     * Strip the newline character and make sure it is printed to stdout.
     */
    size_t n = strlen (s);
    if (n != 0 && s[n - 1] == '\n')
      s[n - 1] = '\0';
    else
      printf ("\n");

    /*
     * Make sure the output make sense if stderr is redirected to stdout (and
     * vice versa).
     */
    fflush (stdout);

    /*
     * Run the test.
     *
     * Note that we need to print the trailing newline character ourselves.
     */
    char* args[] = {argv[0], s, NULL};
    int r = test (2, args);

    fprintf (r == 0 ? stdout : stderr, "\n");
    fflush (r == 0 ? stdout : stderr);
  }

  return 0;
}
