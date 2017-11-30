#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define MMAP_NUM 100
#define PAGE_NUM 100
#define PAGE_SIZE 4096

char data[20] = "@@@@@@@@@@@@@@@@@@@@";

char *filename(int i)
{
    static char name[10];

    sprintf(name, "%d.data", i);

    return name;
}

int main()
{
    printf("This is page fault creator.\n");

    int i;
    FILE *fp[MMAP_NUM];
    void *p[MMAP_NUM];

    p[0] = mmap((void *)0x600000000000, PAGE_SIZE * PAGE_NUM, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
   
    printf("address:[%lx]\n", (unsigned long)(p[0]));
    //for (i=0; i<MMAP_NUM; i++) {
    //    fp[i] = fopen(filename(i), "wb+");
    //    fwrite(data, 16, 1, fp[i]);
    //    p[i] = mmap(0, 409600, PROT_READ, MAP_SHARED, -1, 0);
    //    printf("%lx\n", (unsigned long)(p[i]));
    //}

    //for (i=0; i<MMAP_NUM; i++) {
    //    munmap(p[i], 16);
    //    fclose(fp[i]);
    //}
   
    unsigned long add = (unsigned long)(p[0]);

    for (i=0; i<PAGE_NUM; i++) {
        printf("%lx\n", add);
        *((int *)add) = i;
        add += PAGE_SIZE;
    }

    add = (unsigned long)(p[0]);

    //for (i=0; i<100; i++) {
    //    volatile int num;
    //    printf("%lx\n", add);
    //    num = *((int *)add);
    //    if (num != 0x12345678) {printf("WTF!!!\n");}
    //    add += 4096;
    //}

    munmap((void *)0x600000000000, PAGE_SIZE * PAGE_NUM);

    printf("Module End.\n");

    return 0;
}
