/* James Park
 * CIT 595 HW #1
 */

// the initial capacity (number of buckets)
#define CAPACITY 10000

// the initial capacity for words
#define BUFFER 20000

typedef struct Node node;
struct Node {
  char* value;
  int counter;
  node* next; // next node in the list
};

typedef struct Hashtable hashtable;
struct Hashtable {
  node* list[CAPACITY]; // "buckets" of linked lists
};

/* Function prototypes */
int hash(char*, unsigned long*);
int put(char*, hashtable*);
int get(char*, hashtable*);
int file_initialize(char*);
char* file_read_next();
int file_close();
void top_ten(hashtable*);

