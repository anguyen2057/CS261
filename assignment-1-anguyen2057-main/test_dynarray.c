/*
 * This file contains executable code for testing your dynamic array
 * implementation.
 */

#include <stdio.h>
#include <stdlib.h>

#include "dynarray.h"

/*
 * The first couple things in this file represent a set of testing data that
 * will be used to test your dynamic array implementation.  The data consists
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
 * Function to run tests on dynamic array implementation.
 */
void test_dynarray(struct student** students, int n) {
  struct dynarray* da;
  struct student* repl, * s;
  int i, k, n_removed = 0;

  /*
   * Create a dynamic array.
   */
  da = dynarray_create();
  printf("Checking that array is not NULL... ");
  fflush(stdout);
  if (da == NULL) {
    printf("FAIL\n");
  } else {
    printf("OK\n");
  }

  /*
   * Add students to dynamic array.
   */
  printf("\n");
  for (i = 0; i < n; i++) {
    printf("Adding students[%d] to the array... ", i);
    fflush(stdout);
    dynarray_insert(da, students[i]);
    printf("OK (check for correct array contents below)\n");
  }

  /*
   * Check dynamic array size.
   */
  printf("\nChecking array size (%d == %d?)... ", n, dynarray_size(da));
  fflush(stdout);
  if (n == dynarray_size(da)) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }

  /*
   * Check that we can fetch values from the dynamic array.
   */
  printf("\nArray contents:\n");
  for (i = 0; i < dynarray_size(da); i++) {
    s = dynarray_get(da, i);
    if (s) {
      printf("  %-16s\t%d\t%f\n", s->name, s->id, s->gpa);
    } else {
      printf("  NULL\n");
    }
  }

  /*
   * Test updating values stored in the dynamic array.
   */
  repl = malloc(sizeof(struct student));
  repl->name = "Kylo Ren";
  repl->id = 933999999;
  repl->gpa = 0.75;
  for (i = n - 1; i > 0; i /= 2) {
    printf("\nReplacing element %d... ", i);
    fflush(stdout);
    dynarray_set(da, i, repl);
    printf("OK (check that values below match)\n");
    printf("Inserted:  %-16s\t%d\t%f\n", repl->name, repl->id, repl->gpa);
    s = dynarray_get(da, i);
    if (s) {
      printf("Array @ %1d: %-16s\t%d\t%f\n", i, s->name, s->id, s->gpa);
    } else {
      printf("Array @ %1d: %-16s\n", i, "NULL");
    }
  }

  /*
   * Test removing elements from the dynamic array by removing the copies of
   * repl that were inserted above.
   */
  printf("\n");
  for (i = n - 1; i > 0; i /= 2) {
    printf("Removing element %d... ", i);
    fflush(stdout);
    dynarray_remove(da, i);
    printf("OK (check updated array contents below)\n");
    n_removed++;
  }

  printf("\nNew array size (should be %d): %d\n", n - n_removed,
    dynarray_size(da));
  printf("New array contents (should have no %s):\n", repl->name);
  for (i = 0; i < dynarray_size(da); i++) {
    s = dynarray_get(da, i);
    if (s) {
      printf("  %-16s\t%d\t%f\n", s->name, s->id, s->gpa);
    } else {
      printf("  NULL\n");
    }
  }

  free(repl);

  printf("\nFreeing array... ");
  fflush(stdout);
  dynarray_free(da);
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

  test_dynarray(students, NUM_TESTING_STUDENTS);

  /*
   * Free the array of student structs.
   */
  for (i = 0; i < NUM_TESTING_STUDENTS; i++) {
    free(students[i]);
  }
  free(students);
}
