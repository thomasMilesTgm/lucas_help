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




athletes_d new_athletes_d(int i,char* sex,int age, char* h, char* w, char* tm, char* nat,char* g, int y, char* season, char* c, char* sp, char* e, char* m)
{
    printf("athlete creating \n");
    athletes_d a;
    a.i = i;
    a.sex = sex;
    a.age = age;
    a.h = h;
    a.w = w;
    a.tm = tm;
    a.nat = nat;
    a.g = g;
    a.y = y;
    a.season = season;
    a.c = c;
    a.sp = sp;
    a.e = e;
    a.m = m;
    printf("athlete created \n");
    return a;
}



//key_val* new_key_val(athletes_d ath, char* key){
//    key_val* kv = (key_val*)malloc(sizeof(key_val));
//    strcpy(kv->key,key);
//    kv->ad = ath;
//    return kv;
//}


/* create a new empty bst structure */
bst_key* bst_new(int (*cmpfunc)(char*,char*))
{
    bst_key* bst;
    bst = (bst_key*)malloc(sizeof(bst_key));        //TODO make safe malloc
    assert(bst != NULL);
    bst->root = NULL;
    bst->num_elements = 0;
    bst->cmp = cmpfunc;
    return bst;
}



/* insert a new element into the bst */
int bst_insert(bst_key* bst, athletes_d new_ath)
{

    char* key = new_ath.name;

    printf("inserting %s... \n", new_ath.name);

    assert(bst != NULL);
//    assert(n != NULL);
    node_k* parent = NULL;
    node_k* tmp = bst->root;

    /* Finding the node in bst */
    while (tmp) {

        parent = tmp;

        if (bst->cmp(tmp->key, key) >= 0) { // element is smaller
            tmp = tmp->left;
        }
        else if (bst->cmp(tmp->key, key) < 0) { // element is bigger
            tmp = tmp->right;
        }
    }
    
    /* insert as child of parent */
    /* allocating the space to hold the key value */
    node_k* new_node = (node_k*)malloc(sizeof(node_k));
    assert(new_node != NULL);
//    new_node = n;
    new_node->left = NULL;
    new_node->right = NULL;
    if (parent != NULL) {
        if (bst->cmp(parent->key, key) >= 0) { // element is smaller
            assert(parent->left == NULL);
            parent->left = new_node;

        } else {
            assert(parent->right == NULL);
            parent->right = new_node;
        }
    }
    else {
        assert(bst->root == NULL);
        bst->root = new_node;
    }
    bst->num_elements++;
    printf("inserted \n");
    return BST_SUCCESS;
}

int namecompare(char* a, char* b)
{
    return strcasecmp(a, b);
}

athletes_d parse_line(char* line)
 // TODO return athletes_d
{

    athletes_d an_athlete;

    an_athlete.i =  atoi(strtok(line, ","));

    an_athlete.name =  strtok(line, ",");

    an_athlete.sex =  strtok(line, ",");

    an_athlete.age =  atoi(strtok(line, ","));

    an_athlete.h =  strtok(line, ",");

    an_athlete.w =  strtok(line, ",");

    an_athlete.tm =  strtok(line, ",");

    an_athlete.nat =  strtok(line, ",");

    an_athlete.g =  strtok(line, ",");

    an_athlete.y =  atoi(strtok(line, ","));

    an_athlete.season =  strtok(line, ",");

    an_athlete.c =  strtok(line, ",");

    an_athlete.sp =  strtok(line, ",");

    an_athlete.e =  strtok(line, ",");

    an_athlete.m =  strtok(line, ",");

    printf("Name is:: %s\n", an_athlete.name);

    return an_athlete;
//    char* tok;
//    for (tok = strtok(line, ",");
//         tok && *tok;
//         tok = strtok(NULL, ";\n"))
//    {
//        if (!--num)
//            return tok;
//    }
    //return NULL;
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

bst_key* readdatafile (const char* filename){



    char *buffer;
    
    printf("REadinf filess ... \n");
    FILE* fp;
    fp = fopen(filename,"r");
    
    if(fp == NULL){
        printf("File not read\n");
        exit(1);
    }

    bst_key* tree;
    tree = bst_new(namecompare);
    printf("tree initialized \n");

    buffer = create_buffer(MAX_LEN);

    // TODO Read in root node first

    while (fgets (buffer, MAX_LEN, fp)) {

        athletes_d new_ath = parse_line(buffer);

    }




    printf("return treee \n");
    return tree;
    //return NULL;
}
//write file keyvalues
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
void bst_search(bst_key* tree, char* key, const char* outputfile){
    node_k* tmp = tree->root;
    int found = 0;
    int count = 0;

    while (tmp) {
        if (tree->cmp(tmp->key, key) > 0) { // element is smaller
            tmp = tmp->left;
            count++;

        } else if (tree->cmp(tmp->key, key) < 0) { // element is bigger
            tmp = tmp->right;
            count++;

        } else {
            athletes_d d = tmp->ad;
            char* message = (char*)malloc(STRING_BUFFER* sizeof(char));
            sprintf(message, "%s --> ID: %d Sex: %s || Age: %d || Height: %s || Weight: %s || Team: %s || NOC: %s"
                    " ||Games: %s ||Year: %d || Season: %s || City: %s || Sport: %s || Event: %s || Medal: %s ||",
                    key, d.i,d.sex,d.age,d.h,d.w,d.tm,d.nat,d.g,d.y,d.season,d.c,d.sp,d.e,d.m );
            writing_to_file(outputfile, message);
            tmp = tmp->left;
            free(message);
            found = 1;
            count++;
        }
    
    } if(found ==0) {
        char* message = (char*)malloc(STRING_BUFFER* sizeof(char));
        sprintf(message, "%s --> NOTFOUND ", key);
        writing_to_file(outputfile, message);
        free(message);
    }
    printf("%s --> %d", key,count);
}


