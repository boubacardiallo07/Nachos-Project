#ifdef CHANGED

#include "syscall.h"

void print(void *ch) 
{
    int  i;
    
    //PutString("in print func \n");

    // PutChar(ch);

    for(i = 0; i<5; i++){
        //PutChar('b');
        PutChar( (int) ch);
    }

    PutChar(ch);

    ThreadExit();
}

int main() 
{
    //PutString("\t ********** Test makethreads.c ********** \n \n");
    PutString("Début Test Thread\n");

    ThreadCreate(print, (void*)'a');

    // PutChar('\n');

    //PutChar('B');
    // PutChar('\n');
    //PutString("Fin Test Thread\n");

    while (1)
    {
        /* code */
    }
    
    ThreadExit();

}

#endif //CHANGED
