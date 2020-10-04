#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int value;
    struct node *prev;
    struct node *next;
};

int main(int argc, char const *argv[])
{
    // Set input file
    FILE *inFile = fopen("input.txt", "r");

    // Get amount of memory in gigabytes argument, if not set default
    int memoryAmm = 0, i;
    if (argc > 1 && (memoryAmm = atoi(argv[1])));
    else memoryAmm = 1;

    // Allocate memory in gigabytes of data [2^28 * 4(size of int) = 1GB]
    const int page_size = memoryAmm * 268435456 ;
    int * page = malloc((sizeof (int)) * page_size );
    
    // Temporary file pointers
    FILE  * tempFiles[1024];
    int fileCount = 0;

    // Create temporary files based on the page size
    int inputNum = 0, numCount = 0;
    

    while(fscanf(inFile, "%d", &inputNum) == 1 /*testing purpose*/ && fileCount < 3){
        page[numCount] = inputNum;
        if(numCount+1 < page_size){
            numCount++;
        }else {
        // TODO: Sort integers in page 
        
        // Save page in a temporary file
            tempFiles[fileCount] = tmpfile();
            fwrite(page, sizeof(page[0]), sizeof(page)/sizeof(page[0]), tempFiles[fileCount]);
            fileCount++;
        }
    }

    // Set buffers to start
    for(i = 0; i<fileCount; i++){
        rewind(tempFiles[i]);
    }

    // Test for file viewing.
    for(i = 0; i<fileCount; i++){
        int * p;
        *p = 0;
        while(fread(p,sizeof(int),1,tempFiles[i]) == 1){
            printf("File %d: %d", i, *p);
        }
    }

    for(i = 0; i<fileCount; i++)
        fcloes(tempFiles[i]);
    fclose(inFile);
    return 0;
}
