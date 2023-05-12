#include "func.h"

#include "stdio.h"

#define CUST_NUM   1100
#define CUST_STR   "uuid-1200-tytt"

int main(void)
{
    int i;
    printf("Hello world\r\n");

for (i = 0; i < 10; i++)
    {
        printf("%d\r\n", i);
    }
    i += 108;

    printf("i is %d\n", i);
    printf("NUM is %d\n", CUST_NUM);
    printf("STR is %s\n", CUST_STR);
    
    
    return 0;
}
