#include <stdlib.h>
#include <stdio.h>
#include "bst_1.c"

int main(int argc, const char** argv) {

    if(argc != 3){
        printf("Not enough arguments\n");
        exit(1);
    }else{
        printf("%s, %s , %s .. \n",argv[0],argv[1],argv[2]);
    }

    // Create Tree from datafile
    struct node* root = readdatafile(argv[1]);

 //   char* key = "hoem";
    char buffer[128];
    while (fgets(buffer, sizeof buffer, stdin) != NULL) {

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[--len] = '\0';
        }
        bst_search(root,buffer,argv[2]);
    }
}