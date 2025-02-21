/*
 * In this file, you should implement an application that compares the
 * performance of a dynamic array and a linked list, as described in the
 * README. Don't forget to include your name and @oregonstate.edu email
 * address below.
 *
 * Name: An Nguyen 
 * Email: nguyea22@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "dynarray.h"
#include "list.h"

#define TEST_DATA_SIZE 1000000

/*
 * This function generates and an array of random integers of size n.
 */
int* generate_random_array(int n) {
  int* arr = malloc(n * sizeof(int));
  int i;

  for (i = 0; i < n; i++) {
    arr[i] = rand();
  }

  return arr;
}

int main(int argc, char const *argv[]) {
  int* test_data = generate_random_array(TEST_DATA_SIZE);

  /*
   * You should write code here to insert the data in test_data into a
   * dynamic array using the dynamic array interface you implemented.  As
   * you're doing this, measure two things:
   *   1. The total amount of time it takes to insert all the data into the
   *      dynamic array.
   *   2. The maximum amount of time it takes to insert any single element into
   *      the dynamic array.
   * To help with this, you can use the C functions time() and difftime()
   * from time.h.  Don't forget to include time.h above!
   */
  
  //Dynamic Array
  struct dynarray* da = dynarray_create();
  clock_t start;
  clock_t end;

  double total_t_dynarray;  //total insertion time
  double one_t_dynarray;  //insertion time for 1 element
  double insert_t_dyna;  //hold the time in seconds

  // Insert elements into the dynamic array and measure time
  for (int i = 0; i < TEST_DATA_SIZE; i++) {
      start = clock();  // Start the clock for a 1 insertion
      dynarray_insert(da, &test_data[i]);  // Insert element
      end = clock();  // End the clock for the insertion



      //calculate the time in seconds
      insert_t_dyna = ((double)(end - start)) / CLOCKS_PER_SEC;  

      //accumulate the time for total time of dynarrya
      total_t_dynarray = total_t_dynarray + insert_t_dyna;

      if (insert_t_dyna > one_t_dynarray) {
            one_t_dynarray = insert_t_dyna;  //getting the max one time insertion
      }
  }


   /*
    * You should write code here to insert the data in test_data into a
    * linked list using the linked list interface you implemented.  As
    * you're doing this, measure two things:
    *   1. The total amount of time it takes to insert all the data into the
    *      linked list.
    *   2. The maximum amount of time it takes to insert any single element into
    *      the linked list.
    * Again, you can use the C functions time() and difftime() from time.h to
    * help with this.
    *
    * How do the times associated with the dynamic array compare to the times
    * associated with the linked list?  How does this change if you modify the
    * value of TEST_DATA_SIZE above?
    */

  struct list* lilist = list_create();
  double total_t_list;
  double one_t_list;
  double insert_t_list;

  for (int i = 0; i < TEST_DATA_SIZE; i++) {
    start = clock();
    list_insert(lilist, &test_data[i]);
    end = clock();

    //calculate the time in seconds
    insert_t_list = ((double)(end - start)) / CLOCKS_PER_SEC;

    //accumulate the time for total time link list
    total_t_list = total_t_list + insert_t_list;

    if (insert_t_list > one_t_list) {
      one_t_list = insert_t_list;
    }

  }






  
  printf("\nDynamic:\n");
  printf("Total Insertion Time: %lf\n", total_t_dynarray);
  printf("Max Insertion Time of One Element: %lf\n", one_t_dynarray);

  
  printf("\nLinked :List\n");
  printf("Total Insertion Time: %lf\n", total_t_list);
  printf("Max Insertion Time of One Element: %lf\n", one_t_list);
  printf("\n");
  
  free(test_data);
  return 0;
}
