#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MMAP_NUM 100

char *filename(int i)
{
    static char name[10];

    sprintf(name, "%d", i);

    return name;
}

int main()
{
    printf("This is page fault creator.\n");

    int i;
    FILE *fp[MMAP_NUM];

    for (i=0; i<MMAP_NUM; i++) {
        //fp[i] = fopen();
        printf("%s ", filename(i));
    }
    
    printf("\n");

    return 0;
}
