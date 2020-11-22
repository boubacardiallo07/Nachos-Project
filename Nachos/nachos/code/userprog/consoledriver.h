#ifdef CHANGED //~~

#ifndef CONSOLEDRIVER_H
#define CONSOLEDRIVER_H
#include "copyright.h"
#include "utility.h"
#include "console.h"


class ConsoleDriver:dontcopythis {
    public:
        ConsoleDriver(const char *readFile, const char *writeFile);

// initialize the hardware console device
        ~ConsoleDriver(); // clean up

        void PutChar(int ch); 
        int GetChar();

        void PutString(const char *s); 
        void GetString(char *s, int n);
        void PutInt(int n);
        void GetInt(int *n);

        int copyStringFromMachine(int from, char *to, unsigned size);

        int copyStringToMachine(char *from, int to, unsigned int size);
    
    private:
        Console *console;

};

#endif // CONSOLEDRIVER_H
#endif // CHANGED