#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE * testFile = fopen("output.txt","r");

    int inputNum = INT_MIN, prev =INT_MIN;

    while(fscanf(testFile, "%d", &inputNum)){
        if(inputNum < prev){
            printf("Wrong sorting at %d", inputNum);
        }
        prev = inputNum;
    }

    return 0;
}
