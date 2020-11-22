#ifdef CHANGED //CHANGED
#include "syscall.h"

void print(char c, int n)
{
    int i;
    #ifdef CHANGED //~~
    for( i = 0; i<n; i++){
        PutChar(c + i);
    }

    PutChar('\n');
    #endif
}



int main()
{
    PutString("\t ********** Test putchar.c ********** \n \n");

    print('a', 4);
    //Halt();

}
#endif