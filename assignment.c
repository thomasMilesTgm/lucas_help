#include "assignment.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <assert.h>

key_s* new_key_s() {
    key_s* k;
    k = (key_s*)malloc(sizeof(key_s));
    assert(k != NULL);
    k->sizeofarray = INTSIZEOFARRAY;
    k->index = -1;
    k->keysearchesarrayv = (char**)malloc(INTSIZEOFARRAY*sizeof(char*));
    return k;
}

void add_key (key_s* k, char* value){
    assert(k!=NULL);
    assert(k->keysearchesarrayv!=NULL);
    assert(value!=NULL);
    if(k->index == k->sizeofarray){
        k->keysearchesarrayv = (char**)realloc(k->keysearchesarrayv,k->sizeofarray*2*sizeof(char*));
        assert(k->keysearchesarrayv!=NULL);
        k->sizeofarray *= 2;
    }
    k->index ++;
    strcpy(k->keysearchesarrayv[k->index],value);
}


int bst_insert(struct node* root, athletes_d new_ath)
{
    struct node* tmp = root;
    char* key = new_ath.name;

    printf("inserting %s... \n", new_ath.name);

    struct node* new_node = malloc(sizeof(struct node));
    new_node->key = new_ath.name;
    new_node->ad = new_ath;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    /* Find nodes position in the tree */
    while (TRUE) {

        if (strcasecmp(tmp->key, new_node->key) >= 0) { // element is smaller, go left
            // found the right position, insert
            if (tmp->left == NULL) {
                tmp->left = new_node;
                new_node->parent = tmp;
                printf("inserted node with key %s to the left of %s\n", new_node->key, tmp->key);
                return BST_SUCCESS;

            } else {
                tmp = tmp->left;
            }

        } else if (strcasecmp(tmp->key, new_node->key) < 0) { // element is bigger
            if (tmp->right == NULL) {
                tmp->right = new_node;
                new_node->parent = tmp;
                printf("inserted node with key %s to the right of %s\n", new_node->key, tmp->key);
                return BST_SUCCESS;

            } else {
                tmp = tmp->right;
            }
        }
    }
    return BST_SUCCESS;
}


athletes_d parse_line(char* line)

{

    athletes_d an_athlete;

    an_athlete.i =  atoi(strtok(line, ","));

    an_athlete.name =  strtok(NULL, ",");

    an_athlete.sex =  strtok(NULL, ",");

    an_athlete.age =  atoi(strtok(NULL, ","));

    an_athlete.h =  strtok(NULL, ",");

    an_athlete.w =  strtok(NULL, ",");

    an_athlete.tm =  strtok(NULL, ",");

    an_athlete.nat =  strtok(NULL, ",");

    an_athlete.g =  strtok(NULL, ",");

    an_athlete.y =  atoi(strtok(NULL, ","));

    an_athlete.season =  strtok(NULL, ",");

    an_athlete.c =  strtok(NULL, ",");

    an_athlete.sp =  strtok(NULL, ",");

    an_athlete.e =  strtok(NULL, ",");

    an_athlete.m =  strtok(NULL, ",");

//    printf("i %d\n", an_athlete.i);
//    printf("name %s\n", an_athlete.name);
//    printf("sex %s\n", an_athlete.sex);
//    printf("age %d\n", an_athlete.age);
//    printf("h %s\n", an_athlete.h);
//    printf("w %s\n", an_athlete.w);
//    printf("tm %s\n", an_athlete.tm);
//    printf("nat %s\n", an_athlete.nat);
//    printf("g %s\n", an_athlete.g);
//    printf("y %d\n", an_athlete.y);
//    printf("season %s\n", an_athlete.season);
//    printf("c %s\n", an_athlete.c);
//    printf("sp %s\n", an_athlete.sp);
//    printf("e %s\n", an_athlete.e);
//    printf("m %s\n", an_athlete.m);

    return an_athlete;
}
char * create_buffer (int buffer_size) {
    /**
    Creates the buffer for scanning data from the CSV file and returns a
    pointer to it
    */
    char *buffer;
    buffer = (char*) malloc (buffer_size);

    if (buffer == NULL) {
        printf("--> ERROR: ERROR: In create_buffer: malloc failure.");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

struct node* readdatafile (const char* filename){

    char *buffer;
    
    printf("REadinf filess ... \n");
    FILE* fp;
    fp = fopen(filename,"r");
    
    if(fp == NULL){
        printf("File not read\n");
        exit(1);
    }

//    tree = bst_new(namecompare);
//    printf("tree initialized \n");

    buffer = create_buffer(MAX_LEN);

    athletes_d new_ath;
    struct node* root = NULL;        // NULL so root is assigned in first iteration

    while (fgets (buffer, MAX_LEN, fp)) {

        new_ath = parse_line(buffer);

        // Make tree root if first iteration
        if (root == NULL) {

            root = malloc(sizeof(struct node));
            // TODO safe malloc
            root->ad = new_ath;
            root->key = new_ath.name;
            root->left = NULL;
            root->right = NULL;
            root->parent = NULL;

        // Otherwise add new node to the tree
        } else {
            bst_insert(root, new_ath);
        }
    }

    printf("return tree \n");
    return root;

}

void writing_to_file(const char* outputfile, char* message) {
    
    FILE* fp ;
    fp = fopen(outputfile,"a");
    
    if (fp == NULL) {
        perror("file open error.");
        exit(EXIT_FAILURE);
    }
    
    size_t len = strlen(message);
    size_t written = fwrite(message, sizeof(char), len, fp);
    if (written != len) {
        perror("fwrite error");
        exit(EXIT_FAILURE);
    }
    fclose(fp);
}


// search in bst
void bst_search(struct node* root, char* key, const char* outputfile){

    struct node* tmp = root;
    int found = 0;
    int count = 0;

    while (tmp != NULL) {

        printf("searching for %s\n", key);
        printf("tmp->key: %s\n", tmp->key);
        printf("comp: %d\n",strcasecmp(tmp->key, key));

        if (strcasecmp(tmp->key, key) == 0) {
            // Found it, write to file and return
            athletes_d d = tmp->ad;

            char* message = (char*)malloc(STRING_BUFFER* sizeof(char));
            sprintf(message, "%s --> ID: %d Sex: %s || Age: %d || Height: %s || Weight: %s || Team: %s || NOC: %s"
                            " ||Games: %s ||Year: %d || Season: %s || City: %s || Sport: %s || Event: %s || Medal: %s ||",
                    key, d.i,d.sex,d.age,d.h,d.w,d.tm,d.nat,d.g,d.y,d.season,d.c,d.sp,d.e,d.m );
            writing_to_file(outputfile, message);
            free(message);
            break;

        } else if (strcasecmp(tmp->key, key) >= 0) { // element is smaller, go left
            // Not found, reached leaf node, write to file and return
            if (tmp->left == NULL) {
                count++;

                char* message = (char*)malloc(STRING_BUFFER* sizeof(char));
                sprintf(message, "%s --> NOTFOUND ", key);
                writing_to_file(outputfile, message);
                free(message);
                break;

            } else {
                count++;
                tmp = tmp->left;
            }

        } else if (strcasecmp(tmp->key, key) < 0) { // element is bigger

            // Not found, reached leaf node, write to file and return
            if (tmp->right == NULL) {
                char* message = (char*)malloc(STRING_BUFFER* sizeof(char));
                sprintf(message, "%s --> NOTFOUND ", key);
                writing_to_file(outputfile, message);
                free(message);

                // Not found, keep looking
            } else {
                count++;
                tmp = tmp->left;
            }
        }
    }
    printf("%s --> %d\n", key,count);
}


