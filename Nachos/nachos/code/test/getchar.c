#ifdef CHANGED //~~

#include "syscall.h"

//permet de récupérer un caractère et de l'afficher sur la console
// Pour lancer le test depuis /userprog§ ./nachos -x ../test/getchar



int main()
{
    char c;
    
    PutString("\t ********** Test getstring.c ********** \n \n");
    
    PutChar('\n');
    PutString("Pour sortir de la boucle taper q\n");

    //Tant que 'q' n'est pas tapé la boucle continue
    while (c != 'q'  ) {
        c = GetChar(); //stock le caractère récupéré dans c 
        PutChar(c); //affiche le caratère
    }

}

#endif
