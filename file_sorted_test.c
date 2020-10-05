#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int main(int argc, char const *argv[])
{
    FILE * testFile = fopen("output.txt","r");

    int inputNum = INT_MIN, prev =INT_MIN, count=0;

    while(fscanf(testFile, "%d", &inputNum) == 1){
        if(inputNum < prev){
            printf("Wrong sorting at %d", inputNum);
        }
        count ++;
        prev = inputNum;
    }

    printf("%d\n", count);
    return 0;
}
