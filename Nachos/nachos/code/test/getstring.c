#ifdef CHANGED // CHANGED

#include "syscall.h"

//Permet de tester getstring

// Pour lancer le test depuis /userprog§ ./nachos -x ../test/getstring


int main()
{
    int n = 10, i=0;
    char s[n]; //déclaration d'un tableau de taille 10
    
    PutString("\t ********** Test getstring.c ********** \n \n");

    GetString(s, n); //écrire dans le tableau s
    PutString(s);// afficher ce qui vient d'être écrit
    PutChar('\n');

    //Halt();
}

#endif