#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <assert.h>

#define MAX_LEN 512
#define BST_SUCCESS 1
#define BST_FAILURE 0
#define BST_PREORDER 0
#define BST_INORDER 1
#define BST_POSTORDER 2
#define INTSIZEOFARRAY 50
#define STRING_BUFFER 200




/*    Struct Definitions      */






// keysearchlist
typedef struct {
    int sizeofarray;
    char** keysearchesarrayv;
    int index;
} key_s ;

// Making the array for athletes information
typedef struct {
//TODO refactor naming
    int i;
    char* name;
    char* sex;
    int age;
    char* h;
    char* w;
    char* tm;
    char* nat;
    char* g;
    int y;
    char* season;
    char* c;
    char* sp;
    char* e;
    char* m;
} athletes_d;


// Characterizing the key to the athlete
//typedef struct{
//    char* key;
//    athletes_d ad;
//
//} key_val;

/* node structure */
typedef struct node node_k;

struct node {
    char* key;
    athletes_d ad;
//    key_val* key_n;
    node_k* left;
    node_k* right;
};
/* bst type */
typedef struct {
    int num_elements;
    node_k* root;
    int (*cmp)(char*, char*);
} bst_key;


/*     FUNCTION DECLARATIONS     */
char * create_buffer (int buffer_size);

bst_key* bst_new(int (*cmpfunc)(char*,char*));

athletes_d new_athletes_d(int i,char* sex,int age, char* h, char* w, char* tm, char* nat,char*
        , int y, char* season, char* c, char* sp, char* e, char* m);

void add_key (key_s* k, char* value);

key_s* new_key_s();

//key_val* new_key_val(athletes_d ath, char* key);

int bst_insert(bst_key* bst, athletes_d new_ath);

int namecompare(char* a, char* b);

athletes_d parse_line(char* line);

bst_key* readdatafile (const char* filename);

void writing_to_file(const char* outputfile, char* message);

void bst_search(bst_key* tree,char* key, const char* outputfile);