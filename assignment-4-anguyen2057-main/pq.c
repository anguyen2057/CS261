/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include <assert.h>
#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq {
  struct dynarray* heap;
};

/*
 * This is the structure that represents the elements in the queue. It has the 
 * value and its priority
 */
struct pq_element {
  void* value;
  int priority;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  assert(pq);
  pq -> heap = dynarray_create();
  return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  assert(pq);
  int size = dynarray_size(pq -> heap);
  for (int i = 0; i < size; i++) {
    free(dynarray_get(pq -> heap, i));
  }
  dynarray_free(pq -> heap);
  free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  assert(pq);
  return dynarray_size(pq -> heap) == 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */


/*
 * Helper Function
 * 
 */

void filter_up(struct dynarray* da, int index) {
  while (index > 0) {
    int parent_index = (index - 1)/ 2;

    struct pq_element* current = dynarray_get(da, index);
    struct pq_element* parent = dynarray_get(da, parent_index);

    if (current -> priority < parent -> priority) {
      dynarray_set(da, index, parent);
      dynarray_set(da, parent_index, current);


      index = parent_index;
    } else {
        break;
    }
  }
}




void pq_insert(struct pq* pq, void* value, int priority) {
  assert(pq);
  struct pq_element* entry = malloc(sizeof(struct pq_element));

  assert(entry);
  entry -> value = value;
  entry -> priority = priority;
  dynarray_insert(pq -> heap, entry);
  filter_up(pq -> heap, dynarray_size(pq -> heap) - 1);
}









/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  assert(pq && !pq_isempty(pq));
  struct pq_element* entry = dynarray_get(pq -> heap, 0);
  return entry -> value;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  assert(pq && !pq_isempty(pq));

  struct pq_element* entry = dynarray_get(pq -> heap, 0);

  return entry -> priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */

/*
 * Helper Function
 * 
 */

void filter_down(struct dynarray* da, int index) {
  int size = dynarray_size(da);
  while (2 * index + 1 < size) {
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int smallest = index;

    struct pq_element* current = dynarray_get(da, index);
    struct pq_element* left = dynarray_get(da, left_child);

    if (left -> priority < current -> priority) {
      smallest = left_child;
    }

    if (right_child < size) {
      struct pq_element* right = dynarray_get(da, right_child);
      if (right -> priority < ((struct pq_element*)dynarray_get(da, smallest)) -> priority) {
        smallest = right_child;
      }
    }
    if (smallest != index) {
      struct pq_element* temp = dynarray_get(da, index);

      dynarray_set(da, index, dynarray_get(da, smallest));
      dynarray_set(da, smallest, temp);

      index = smallest;

    } else {
      break;
    }
  }
}




void* pq_remove_first(struct pq* pq) {
  assert(pq && !pq_isempty(pq));
  struct pq_element* first = dynarray_get(pq -> heap, 0);
  void* value = first -> value;
  free(first);

  int last_index = dynarray_size(pq->heap) - 1;
  if (last_index > 0) {
    dynarray_set(pq -> heap, 0, dynarray_get(pq->heap, last_index));
  }
  dynarray_remove(pq -> heap, last_index);

  if (!pq_isempty(pq)) {
    filter_down(pq -> heap, 0);
  }

  return value;
}
