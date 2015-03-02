/* James Park
 * CIT 595 HW #1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

FILE *infile;

char file_word[BUFFER];

/*
 * For the given string refered to by the pointer "string",
 * calculate the hashcode and update the variable pointed to by "value".
 *
 * Return 1 if successful, and 0 if an error occurred
 * (e.g. if the string is null).
 */
int hash(char* string, unsigned long* value)
{
	if (string == NULL || value == NULL){
		return 0;
	}
	int i = 0;
	int hashcode = 0;
	while (string[i] != '\0'){
		hashcode = hashcode + (int)string[i];
		i++;
	}
	*value = hashcode;
	return 1;
}

/*
 * Add the string to the hashtable in the appropriate "bucket".
 *
 * Return 1 if successful, and 0 if an error occurred
 * (e.g. if the string is null, if memory could not be allocated,
 * or if the string is already in the hashtable).
 */
int put(char* string, hashtable* h)
{
	//1. get the hashcode
	unsigned long hashcode;
	int hashWorked = hash(string, &hashcode);
	if (hashWorked != 1) return 0;

	//2. figure out which bucket
	int bucket_num = hashcode % CAPACITY;

	//3. add to that bucket, or linked list
	node* head = h->list[bucket_num];
	while (head != NULL){
		if (strcmp(string, head->value) == 0){
			return 0;
		}
		head = head->next;
	}
	node* new = malloc(sizeof(node));
	if (new == NULL) return 0;

	new->value = malloc(strlen(string)+ 1);
	if(new->value == NULL) return 0;
	new->counter = 1;
	strcpy(new->value, string);
	new->next = h->list[bucket_num];
	h->list[bucket_num] = new;
	return 1;
}

/*
 * Determine whether the specified string is in the hashtable.
 * Return 1 if it is found, 0 if it is not (or if it is null).
 */
int get(char* string, hashtable* h)
{
//get or finds or contains
//int indiciates true or false (found or not)

	unsigned long hashcode;
	int hashWorked = hash(string, &hashcode);
	if (hashWorked != 1) return 0;
	int bucket_num = hashcode % CAPACITY;
	node* head = h->list[bucket_num];
		while (head != NULL){
			if (strcmp(string, head->value) == 0){
				head->counter+=1;
				return 1;
			}
			head = head->next;
	}
	return 0;
}

/*
 * Opens file that's given in command line
 */
int file_initialize(char* name) {
  if (name == NULL) {
    printf("Error! File name provided to file_initialize is null\n");
    return 0;
  }
  infile = fopen(name, "r");
  if (infile == NULL) {
    printf("Error! Could not open file \"%s\" for reading\n", name);
    return 0;
  }
  else {
	return 1;
  }
}

/*
 * Closes file that's given in command line
 */
int file_close(){
	int close_worked = fclose(infile);
	if (close_worked !=0){
		printf("Error!  File did not close properly\n");
		return 0;
	}
	return 1;
}

/*
 * Reads next word
 */
char* file_read_next() {
  if (fscanf(infile, "%s", file_word) == EOF) return NULL;
  else return file_word;
}

/*
 * Prints out the top ten popular hashtags in inputted file
 */
void top_ten(hashtable* h){

	node* top_hashtags[10] = { NULL };
	for (int i = 0; i < CAPACITY; i++){
		node* curr_node = h->list[i];
		while (curr_node != NULL){
			for (int j = 0; j < 10; j++){
				node* top_node = top_hashtags[j];
				if (top_node == NULL){
					top_hashtags[j] = curr_node;
					break;
				}
				else if (top_node->counter <= curr_node->counter){
                	for (int n = 8; n >= j; n--){
                		top_hashtags[n + 1] = top_hashtags[n];
                	}
                	top_hashtags[j] = curr_node;
                	break;
				}

			}
			curr_node = curr_node->next;
		}
	}
	for (int i = 0; i < 10; i++){
		node* head = top_hashtags[i];
		if (head == NULL){
			break;
		}
		printf("%s:  %d\n", head->value, head->counter);
	}
}