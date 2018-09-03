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
//    const char* filename = ;
//    const char* outputfile = ;
    // Create Tree from datafile
    bst_key* tree = readdatafile(argv[1]);

    // read the keyfile
    char key[128];

    while(fgets(key, sizeof(key), stdin)!=NULL){
        bst_search(tree,key,argv[2]);

    }


}