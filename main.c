#include <stdlib.h>
#include <stdio.h>
#include "assignment.c"

int main(int argc, const char** argv) {

    if(argc != 3){
        printf("Not enough arguments\n");
        exit(1);
    }else{
        printf("%s, %s , %s .. \n",argv[0],argv[1],argv[2]);
    }

    // Create Tree from datafile
    struct node* root = readdatafile(argv[1]);
//
//    char* key = "guus";
//
//    bst_search(root,key,argv[2]);
    char key[128];
    while(fgets(key, sizeof(key), stdin)!=NULL){
        bst_search(root,key,argv[2]);

    }





    //bst_key* tree =
    // read the keyfile
//    char key[128];
//
//    while(fgets(key, sizeof(key), stdin)!=NULL){
//
//        printf("Searching for %s\n", key);
//        //bst_search(tree,key,argv[2]);
//
//    }
    return 0;

}