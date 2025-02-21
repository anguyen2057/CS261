#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"
#include "stack.h"
#include <stdint.h>

#define MAX_STR_LEN 256

/*
 * This function prompts the user for input and stores a maximum of `n`
 * characters of the string they enter into `dest`.  Any trailing line ending
 * characters are removed from the input string.  Returns 1 if a string was
 * successfully read from the user or 0 otherwise.
 */
int get_user_str(char* dest, int n) {
  printf("\nEnter a string, and we'll check whether it's a palindrome (ctrl-d to quit):\n");
  if (fgets(dest, MAX_STR_LEN, stdin) != NULL) {
    /*
     * If a string was successfully read from the user, remove any trailing
     * line ending characters.  Here's some documentation on strcspn() to help
     * understand how this works:
     *
     * https://en.cppreference.com/w/c/string/byte/strcspn
     */
    dest[strcspn(dest, "\r\n")] = '\0';
    return 1;
  } else {
    return 0;
  }
}

int palindrome(const char* in) {
  struct stack* stack = stack_create();
  struct queue* queue = queue_create();
  
  for (int i = 0; i < strlen(in); i++) {
    if (isalpha(in[i])) {
      char character = tolower(in[i]);
      stack_push(stack, (void*) (intptr_t) character);
      queue_enqueue(queue, (void*) (intptr_t) character);
    }
  }


  int is_palindrome = 1;
  while (!stack_isempty(stack) && !queue_isempty(queue)) {
    char stack_character = (char)(intptr_t)stack_pop(stack);
    char queue_character = (char)(intptr_t)queue_dequeue(queue);
    if (stack_character != queue_character) {
      is_palindrome = 0;
      break;
    }
  }

  stack_free(stack);
  queue_free(queue);

  return is_palindrome;


}












int main(int argc, char const *argv[]) {
  char* in = malloc(MAX_STR_LEN * sizeof(char));

  if (!in) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }


  while (get_user_str(in, MAX_STR_LEN)) {
    /*
     * Inside this loop body, you'll have an input string from the user in `in`.
     * You should use your stack and your queue to test whether that string is
     * a palindrome (i.e. a string that reads the same backward as forward, e.g.
     * "ABCBA" or "Madam, I'm Adam").  For each string input by the user,
     * print a message letting the user know whether or not their string is
     * is a palindrome.
     *
     * When you test whether the user's string is a palindrome, you should
     * ignore any non-letter characters (e.g. spaces, numbers, punctuation,
     * etc.), and you should ignore the case of letters (e.g. the characters
     * 'a' and 'A' should be considered as equal).  The C functions isalpha()
     * and tolower() from ctype.h might help with this.
     */

      if (palindrome(in)) {
      printf("The string \"%s\" is a palindrome.\n", in);
    } else {
      printf("The string \"%s\" is not a palindrome.\n", in);
    }
  }



  free(in);
  return 0;
}
