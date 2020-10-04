#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(int stat, int end, int array[]);

int main(int argc, char const *argv[])
{
    // Set input file
    FILE *inFile = fopen("input.txt", "r");

    // Get amount of memory in gigabytes argument, if not set default
    int memoryAmm = 0, i;
    if (argc > 1 && (memoryAmm = atoi(argv[1])));
    else memoryAmm = 1;

    // Allocate memory in gigabytes of data [2^28 * 4(size of int) = 1GB]
    const int page_size = memoryAmm * /*268435456*/ 
    /*testing with MB */ 262144;
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
            sort(0, numCount - 1, page);
        // Save page in a temporary file
            tempFiles[fileCount] = tmpfile();
            fwrite(page, sizeof(page[0]), numCount, tempFiles[fileCount]);
            fileCount++;
            numCount = 0;
        }
    }

    // Set buffers to start
    for(i = 0; i<fileCount; i++){
        rewind(tempFiles[i]);
    }

    // Test for file viewing.
    for(i = 0; i<fileCount; i++){
        int p[1];
        p[0] = 0;
        while(fread(p,sizeof(int),1,tempFiles[i]) == 1){
            printf("File %d: %d \n", i, *p);
        }
    }

    for(i = 0; i<fileCount; i++)
        fclose(tempFiles[i]);
    fclose(inFile);
    return 0;
}



void sort(int start, int end, int a[]){
    // Validation
    if(start >= end) return;

    //Selecting a middle variable
    int val, left = start, right = end, temp;

    val = a[start];

    while(left < right){
        while(a[left] <= val) left++;
        while(a[right] > val) right--;
        if(left < right){
            temp = a[left];
            a[left] = a[right];
            a[right] = temp;
        }
    }

    
    temp = a[right];
    a[right] = a[start];
    a[start] = temp;
    
    sort(start, right - 1, a);
    sort(right + 1, end, a);
}