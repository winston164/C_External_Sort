#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int value;
    struct node * prev;
    struct node * next;
};

int main(int argc, char const *argv[])
{
    FILE * inFile = fopen("input.txt", "r");

    int inputNum = 0;

    fscanf(inFile,"%d\n", inputNum);
    int count = 0;
    while(fscanf(inFile,"%d", inputNum) == 1){
        struct node * np = malloc(sizeof(struct node));
        count++;
        if(np == NULL) printf("%d\n", count);
    }

    fclose(inFile);
    return 0;
}
