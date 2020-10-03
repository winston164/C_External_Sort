#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    FILE *file = fopen("input.txt", "w");

    srand(time(0));

    const long n = 32000000000;

    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d\n", rand());
    }
    

    fclose(file);
    return 0;
}


