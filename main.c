#include <stdio.h>

void print_bits(char c)
{
        int i = 128;
        while (i)
        {
                (c & i) ? printf("1") : printf("0");
                i = i >> 1;
        }
        printf("\n");
}

int main(void)
{
        char h = 'h';
        print_bits(h);
        return 0;
}
