#ifdef CHANGED //CHANGED
#include "syscall.h"

//Permet d'afficher une chaine de caractère sur la console
// Pour lancer le test depuis /userprog§ ./nachos -x ../test/putstring

int main() 
{
    PutString("\t ********** Test putsring.c ********** \n \n");

    PutString("putsring : bla bla bla "); //appelle putstring pour afficher la chaine

   Halt();
}

#endif