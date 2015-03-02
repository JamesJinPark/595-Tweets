/* James Park
 * CIT 595 HW #1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

int main(int argc, char* argv[]) {

	hashtable* h_tweets = malloc(sizeof(hashtable));

	file_initialize(argv[1]);

	char* file_word = file_read_next();

	while (file_word != NULL) {

		if (file_word[0] == '#' && file_word[1] != '\0'){
			int getWorked = get(file_word, h_tweets);
			if (getWorked != 1){
				int putWorked = put(file_word, h_tweets);
				if (putWorked != 1) {
				printf("Error! Putting word into hashtable failed for %s\n", file_word);
					return 0;
				}
			}
		}

		file_word = file_read_next();
	}

	file_close();

	top_ten(h_tweets);
}