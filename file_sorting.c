#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct file_item
{
    int value;
    FILE *originFile;
};

void sort(int stat, int end, int array[]);

int main(int argc, char const *argv[])
{
    // Set input file
    FILE *inFile = fopen("input.txt", "r");
    clock_t t1, t2, T = clock();

    // Get amount of memory in gigabytes argument, if not set default
    int memoryAmm = 0, i, aux = 0;
    if (argc > 1 && (memoryAmm = atoi(argv[1])))
        ;
    else
        memoryAmm = 1;

    // Allocate memory in gigabytes of data [2^28 * 4(size of int) = 1GB]
    const int page_size = memoryAmm * 268435456
                          /*testing with MB  262144*/;
    int *page = malloc((sizeof(int)) * page_size);

    // Temporary file pointers
    int fileCount = 0;
    FILE **tempFiles = malloc(sizeof(FILE *) * (fileCount + 1));

    // Create temporary files based on the page size
    int inputNum = 0, numCount = 0;
    t1 = clock();
    while (fscanf(inFile, "%d", &inputNum) == 1 /*testing purpose && fileCount < 3*/)
    {
        page[numCount] = inputNum;
        if (numCount + 1 < page_size)
        {
            numCount++;
        }
        else
        {
            sort(0, numCount, page);
            // Save page in a temporary file
            tempFiles = realloc(tempFiles, sizeof(FILE *) * (fileCount + 1));
            tempFiles[fileCount] = tmpfile();
            fwrite(page, sizeof(page[0]), numCount + 1, tempFiles[fileCount]);
            fileCount++;
            numCount = 0;
        }
    }

    sort(0, numCount, page);
    // Save page in a temporary file
    tempFiles = realloc(tempFiles, sizeof(FILE *) * (fileCount + 1));
    tempFiles[fileCount] = tmpfile();
    fwrite(page, sizeof(page[0]), numCount + 1 , tempFiles[fileCount]);
    fileCount++;

    t1 = clock() - t1;
    printf("time elapsed in making temp files: %f\n", ((double)t1)/CLOCKS_PER_SEC);

    // Set buffers to start
    for (i = 0; i < fileCount; i++)
    {
        rewind(tempFiles[i]);
    }

    // Merge files into one with k-way sorting

    // Create output file
    FILE *outFile = fopen("output.txt", "w");

    //Make array with top values of each file
    struct file_item *items = malloc(sizeof(struct file_item) * fileCount);
    for (i = 0; i < fileCount; i++)
    {
        fread(&inputNum, sizeof(int), 1, tempFiles[i]);
        items[i].originFile = tempFiles[i];
        items[i].value = inputNum;
    }

    t2 = clock();

    int minIndex;
    while (fileCount > 0)
    {
        // Find the smallest element [currently O(n)]
        minIndex = 0;
        for (i = 0; i < fileCount; i++)
            if (items[i].value < items[minIndex].value)
                minIndex = i;
        fprintf(outFile, "%d\n", items[minIndex].value);
        if (fread(&inputNum, sizeof(int), 1, items[minIndex].originFile))
        {
            items[minIndex].value = inputNum;
        }
        else
        {
            for (i = minIndex; i < (fileCount - 1); i++)
                items[i] = items[i + 1];
            fileCount--;
        }
    }

    t2= clock() - t2;
    printf("Time elapsed after merging files: %f\n", ((double) t2)/CLOCKS_PER_SEC);

    // Generate heap from files' first value
    // struct heap_item * heap = malloc(sizeof(struct heap_item) * fileCount);
    // for(i = 0; i< fileCount; i++){
    //     fread(&inputNum, sizeof(int), 1, tempFiles[i]);
    //     heap[i].value = inputNum;
    //     heap[i].originFile = tempFiles[i];
    // }

    // Test for file viewing.
    // for(i = 0; i<fileCount; i++){
    //     int p[1];
    //     p[0] = 0;
    //     while(fread(p,sizeof(int),1,tempFiles[i]) == 1){
    //         printf("File %d: %d \n", i, *p);
    //     }
    // }

    for (i = 0; i < fileCount; i++)
        fclose(tempFiles[i]);
    fclose(inFile);
    fclose(outFile);

    T = clock() - T;
    printf("Elapsed time is %f\n", ((double)T)/CLOCKS_PER_SEC);
    return 0;
}

void sort(int start, int end, int a[])
{
    // Validation
    if (start >= end)
        return;

    //Selecting a middle variable
    int val, left = start, right = end, temp;

    val = a[start];

    while (left < right)
    {
        while (a[left] <= val)
            left++;
        while (a[right] > val)
            right--;
        if (left < right)
        {
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
