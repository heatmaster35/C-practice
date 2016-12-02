//###########################
//# Name: Leo Gomez         #
//# CruzID: legomez         #
//# Class: CMPS-12M         #
//# Date: Nov 7, 2014       #
//# filename: queue.c       #
//# Details: code that tests#
//# for queue functions     #
//###########################

#include <stdio.h>
#include <stdlib.h>

#include "minunit.h"

#define MAXSIZE 100

int tests_run = 0; // keep track of number of unit tests run

typedef enum q_status {
	/* Enumerated status codes for queue operations */
	q_success = 0,
	q_failure
} q_status;

/**** Private variables for queue ****/

int i, front, back, nItems;
int queue[MAXSIZE];
/**** Functions on queues ****/

q_status q_init(void) {
	// Initialize the queue
	front = -1;
	back = -1;
	nItems = 0;
	return q_success;
}

q_status q_is_empty(void) {
	//Checks queue for items
	if(nItems == 0)
		return 1;
	return 0;
}

q_status q_insert(int value) {
	// Insert an item into back of queue
	if((front == back)&&(nItems == 0))
	{
		front = -1;
		back = -1;
	}
	if(front == MAXSIZE)
		front = 0;
	if(nItems == 100)
	{
		return q_failure;
	}
	if(back == -1)
	{
		back = 0;
		front = 0;
		queue[back] = value;
	}else
	{
		back++;
		if(back == MAXSIZE)
			back = 0;
		queue[back] = value;
	}
	nItems++;
	return q_success;
}

q_status q_remove(int *value) {
	// Remove item from front of queue   
	if(nItems == 0)
	{
		return q_failure;
	}
	if(value == NULL)
	{
		return q_failure;
	}
	if((front == -1)||(front == MAXSIZE))
		front = 0;
	*value = queue[front];
	front++;
	nItems--;

	//   Stores item at front of queue into pointer
	//   given as argument. Removes item from queue.
	//     Returns qSuccess on success.
	return q_success;
}

q_status q_peek(int *value) {
	//Peek at item at front of queue
	if(nItems == 0)
	{
		return q_failure;
	}
	if(value == NULL)
		return q_failure;
	printf(" %d\n", queue[front]);
	//Stores item at front of queue into pointer
	//given as argument. Queue is not altered.
	*value = queue[front];
	//Returns qSuccess on success.

	return q_success;
}

q_status q_destroy(void) {
	/* Destroy the queue */
	front = 0;
	back = -1;
	nItems = 0;
	return q_success;
}

/**** Unit tests ****/

char * test_lifecycle(void) {
	mu_assert("init", q_init() == q_success);
	mu_assert("destroy", q_destroy() == q_success);
	return NULL;
}

char * test_one_insert(void) {
	mu_assert("init", q_init() == q_success);
	mu_assert("insert", q_insert(7) == q_success);
	mu_assert("destroy", q_destroy() == q_success);
	return NULL;
}

char * test_one_is_empty(void) {
	mu_assert("init", q_init() == q_success);
	mu_assert("is_empty", q_is_empty() == 1);
	mu_assert("destroy", q_destroy() == q_success);
	return NULL;
}

char * test_two_is_empty(void) {
	mu_assert("init", q_init() == q_success);
	mu_assert("insert", q_insert(9) == q_success);
	mu_assert("is_empty", q_is_empty() == 0);
	mu_assert("destroy", q_destroy() == q_success);
	return NULL;
}

char * test_one_insert_remove(void) {
	int v;
	mu_assert("init", q_init() == q_success);
	mu_assert("insert", q_insert(16) == q_success);
	mu_assert("remove", q_remove(&v) == q_success);
	mu_assert("value", v == 16);
	mu_assert("destroy", q_destroy() == q_success);
	return NULL;
}

char * test_two_insert_remove(void) {
	int v;
	mu_assert("init", q_init() == q_success);
	mu_assert("insert", q_insert(8) == q_success);
	mu_assert("insert", q_insert(91) == q_success);
	mu_assert("remove", q_remove(&v) == q_success);
	mu_assert("value", v == 8);
	mu_assert("remove", q_remove(&v) == q_success);
	mu_assert("value", v == 91);
	mu_assert("destroy", q_destroy() == q_success);
	return NULL;
}

char * test_three_insert_remove(void) {
	int v;
	mu_assert("init", q_init() == q_success);
	mu_assert("insert", q_insert(10) == q_success);
	mu_assert("insert", q_insert(61) == q_success);
	mu_assert("insert", q_insert(210) == q_success);
	mu_assert("remove", q_remove(&v) == q_success);
	mu_assert("value", v == 10);
	mu_assert("remove", q_remove(&v) == q_success);
	mu_assert("value", v == 61);
	mu_assert("remove", q_remove(&v) == q_success);
	mu_assert("value", v == 210);
	mu_assert("destroy", q_destroy() == q_success);
	return NULL;
}

char * test_multi_insert_remove(void) {
	int v;
	mu_assert("init", q_init() == q_success);
	mu_assert("insert", q_insert(8) == q_success);
	mu_assert("insert", q_insert(91) == q_success);
	for(int i = 0; i < 1000; i++) {
		mu_assert("insert", q_insert(8) == q_success);
		mu_assert("insert", q_insert(91) == q_success);
		mu_assert("remove", q_remove(&v) == q_success);
		mu_assert("value", v == 8);
		mu_assert("remove", q_remove(&v) == q_success);
		mu_assert("value", v == 91);
	}
	mu_assert("remove", q_remove(&v) == q_success);
	mu_assert("value", v == 8);
	mu_assert("destroy", q_destroy() == q_success);
	return NULL;
}

char * test_indexed_insert_remove(void) {
	int v;
	mu_assert("init", q_init() == q_success);
	for(int i = 0; i < 30; i++) {
		mu_assert("insert", q_insert(i) == q_success);
	}
	for(int i = 0; i < 1000; i++) {
		mu_assert("remove", q_remove(&v) == q_success);
		mu_assert("value", v == i);
		mu_assert("insert", q_insert(30 + i) == q_success);
	}
	mu_assert("destroy", q_destroy() == q_success);
	return NULL;
}

char * test_too_many_remove(void) {
	int v;
	mu_assert("init", q_init() == q_success);
	mu_assert("remove", q_remove(&v) == q_failure);
	return NULL;
}

char * test_insert_too_many_remove(void) {
	int v;
	mu_assert("init", q_init() == q_success);
	for(int i = 0; i < 30; i++) {
		mu_assert("insert", q_insert(i) == q_success);
	}
	for(int i = 0; i < 30; i++) {
		mu_assert("remove", q_remove(&v) == q_success);
		mu_assert("value", v == i);
	}
	mu_assert("remove", q_remove(&v) == q_failure);
	return NULL;
}

char * test_peek(void) {
	int v;
	mu_assert("init", q_init() == q_success);
	mu_assert("insert", q_insert(18) == q_success);
	mu_assert("peek", q_peek(&v) == q_success);
	mu_assert("value", v == 18);
	mu_assert("destroy", q_destroy() == q_success);
	return NULL;
}

char * test_peek_two(void) {
	int v;
	mu_assert("init", q_init() == q_success);
	mu_assert("insert", q_insert(18) == q_success);
	mu_assert("insert", q_insert(42) == q_success);
	mu_assert("peek", q_peek(&v) == q_success);
	mu_assert("value", v == 18);
	mu_assert("destroy", q_destroy() == q_success);
	return NULL;
}

char * test_peek_deep(void) {
	int v;
	mu_assert("init", q_init() == q_success);
	for(int i = 0; i < 30; i++) {
		mu_assert("insert", q_insert(i) == q_success);
	}
	for(int i = 0; i < 1000; i++) {
		mu_assert("peek", q_peek(&v) == q_success);
		mu_assert("value", v == i);
		mu_assert("remove", q_remove(&v) == q_success);
		mu_assert("value", v == i);
		mu_assert("insert", q_insert(30 + i) == q_success);
	}
	mu_assert("destroy", q_destroy() == q_success);
	return NULL;
}

char * test_peek_empty(void) {
	int v;
	mu_assert("init", q_init() == q_success);
	mu_assert("peek", q_peek(&v) == q_failure);
	return NULL;
}

char * test_peek_two_empty(void) {
	int v;
	mu_assert("init", q_init() == q_success);
	mu_assert("insert", q_insert(18) == q_success);
	mu_assert("insert", q_insert(42) == q_success);
	mu_assert("remove", q_remove(&v) == q_success);
	mu_assert("remove", q_remove(&v) == q_success);
	mu_assert("peek", q_peek(&v) == q_failure);
	return NULL;
}

char * test_remove_null(void) {
	mu_assert("init", q_init() == q_success);
	mu_assert("insert", q_insert(18) == q_success);
	mu_assert("peek", q_remove(NULL) == q_failure);
	return NULL;
}

char * test_peek_null(void) {
	mu_assert("init", q_init() == q_success);
	mu_assert("insert", q_insert(18) == q_success);
	mu_assert("peek", q_peek(NULL) == q_failure);
	return NULL;
}

char * all_tests(void) {
	/* Run all unit tests */
	mu_run_test(test_lifecycle);
	mu_run_test(test_one_insert);
	mu_run_test(test_one_is_empty);
	mu_run_test(test_two_is_empty);
	mu_run_test(test_one_insert_remove);
	mu_run_test(test_two_insert_remove);
	mu_run_test(test_three_insert_remove);
	mu_run_test(test_multi_insert_remove);
	mu_run_test(test_indexed_insert_remove);
	mu_run_test(test_too_many_remove);
	mu_run_test(test_insert_too_many_remove);
	mu_run_test(test_peek);
	mu_run_test(test_peek_two);
	mu_run_test(test_peek_deep);
	mu_run_test(test_peek_empty);
	mu_run_test(test_peek_two_empty);
	mu_run_test(test_remove_null);
	mu_run_test(test_peek_null);
	return NULL;
}

/**** Main unit test runner ****/

int main(int argc, char *argv[]) {
	printf("Queue Module unit tests\n");
	char *result = all_tests();
	if (result) {
		printf("FAILURE at %s\n", result);
	} else {
		printf("ALL TESTS PASS\n");
	}
	printf("Tests run: %d\n", tests_run);
	return EXIT_SUCCESS;
}
