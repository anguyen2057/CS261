/*
 * This file contains executable code for testing your linked list
 * implementation.
 */

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/*
 * The first couple things in this file represent a set of testing data that
 * will be used to test your linked list implementation.  The data consists
 * of a set of students with names, student ID numbers, and GPAs.
 */

/*
 * This is the total number of students in the testing data set.
 */
#define NUM_TESTING_STUDENTS 8


/*
 * These are the names of the students that'll be used for testing.
 */
char* STUDENT_NAMES[] = {
  "Luke Skywalker",
  "Leia Organa",
  "Rey",
  "Han Solo",
  "Lando Calrissian",
  "Darth Vader",
  "Finn",
  "R2-D2"
};


/*
 * These are the student IDs for the students in the array above that will be
 * used for testing.
 */
int STUDENT_IDS[] = {
  933111111,
  933222222,
  933333333,
  933444444,
  933555555,
  933666666,
  933777777,
  933888888
};


/*
 * These are the GPAs of the students above that will be used for testing.
 */
float STUDENT_GPAS[] = {
  3.75,
  4.0,
  3.9,
  2.5,
  3.67,
  1.33,
  3.25,
  3.9
};


/*
 * This structure represents information about a single university student.
 */
struct student {
  char* name;
  int id;
  float gpa;
};


/*
 * This function compares two students based on their `id`.  Specifically, it
 * returns 0 if their `id` fields are equal and returns a non-zero value
 * otherwise.  It is used to compare students stored in the linked list when
 * calling list_remove() and list_position().
 */
int compare_students(void* a, void* b) {
  struct student* s_a = a, * s_b = b;
  return s_a->id - s_b->id;
}

/*
 * Function to run tests on linked list implementation.
 */
void test_list(struct student** students, int n) {
  struct list* list;
  struct student* s;
  int i, p;

  /*
   * Create a list.
   */
  list = list_create();
  printf("Checking that list is not NULL... ");
  fflush(stdout);
  if (list == NULL) {
    printf("FAIL\n");
  } else {
    printf("OK\n");
  }

  /*
   * Add students to list (in reverse order, so the list order matches the
   * order of the input array).
   */
  printf("\n");
  for (i = n - 1; i >= 0; i--) {
    printf("Adding students[%d] to the list... ", i);
    fflush(stdout);
    list_insert(list, students[i]);
    printf("OK (check for correct positions below)\n");
  }

  /*
   * Check that we can fetch values from the dynamic array.
   */
  printf("\n");
  for (i = 0; i < n; i++) {
    printf("Position of students[%d] (should be %d)... ", i, i);
    fflush(stdout);
    p = list_position(list, students[i], &compare_students);
    printf("%d\n", p);
  }

  /*
   * Reverse list and check for reversed positions.
   */
  printf("\nReversing list... ");
  fflush(stdout);
  list_reverse(list);
  printf("OK (check for correct positions below)\n");
  for (i = 0; i < n; i++) {
    printf("Position of students[%d] (should be %d)... ", i, n - i - 1);
    fflush(stdout);
    p = list_position(list, students[i], &compare_students);
    printf("%d\n", p);
  }

  /*
   * Check for nonexistent student.
   */
  s = malloc(sizeof(struct student));
  s->name = "Kylo Ren";
  s->id = 933999999;
  s->gpa = 0.75;
  printf("\nPosition of non-existent student (should be -1)... ");
  fflush(stdout);
  p = list_position(list, s, &compare_students);
  printf("%d\n", p);
  free(s);

  /*
   * Test removing students.
   */
  for (i = n - 1; i > 0; i /= 2) {
    printf("\nRemoving students[%d]... ", i);
    fflush(stdout);
    list_remove(list, students[i], &compare_students);
    printf("OK (check below to make sure removed correctly)\n");
    printf("Position of students[%d] (should be -1)... ", i);
    fflush(stdout);
    p = list_position(list, students[i], &compare_students);
    printf("%d\n", p);
  }


  printf("\nFreeing list... ");
  fflush(stdout);
  list_free(list);
  printf("OK (check valgrind output to ensure no memory leaks)\n");
}

int main(int argc, char** argv) {
  struct student** students;
  int i;

  /*
   * Create and fill an array of student structs.
   */
  students = malloc(NUM_TESTING_STUDENTS * sizeof(struct student*));
  for (i = 0; i < NUM_TESTING_STUDENTS; i++) {
    students[i] = malloc(sizeof(struct student));
    students[i]->name = STUDENT_NAMES[i];
    students[i]->id = STUDENT_IDS[i];
    students[i]->gpa = STUDENT_GPAS[i];
  }

  test_list(students, NUM_TESTING_STUDENTS);

  /*
   * Free the array of student structs.
   */
  for (i = 0; i < NUM_TESTING_STUDENTS; i++) {
    free(students[i]);
  }
  free(students);
}
