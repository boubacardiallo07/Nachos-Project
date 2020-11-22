// progtest.h
//      Declarations for test routines for demonstrating that Nachos can load a
//      user program and execute it.  
//
//      Also, routines for testing the Console hardware device.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef PROGTEST_H
#define PROGTEST_H

extern void StartProcess (char *filename);

extern void ConsoleTest (const char *in, const char *out);

#endif // PROGTEST_H

#ifdef CHANGED
extern void ConsoleDriverTest (const char *in, const char *out);
#endif //CHANGED

#ifdef CHANGED
int copyStringFromMachine(int from, char *to, unsigned size);
#endif //CHANGED

#ifdef CHANGED
int copyStringToMachine(char *from, int to, unsigned int size);
#endif //CHANGED