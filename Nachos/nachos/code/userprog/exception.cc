// exception.cc 
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.  
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"


#ifdef CHANGED

#include "userthread.h"

#endif

//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC ()
{
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}


#ifdef CHANGED //CHANGED
int copyStringFromMachine(int from, char *to, unsigned size);
int copyStringToMachine(char *from, int to, unsigned int size);
#endif




//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions 
//      are in machine.h.
//----------------------------------------------------------------------



void
ExceptionHandler (ExceptionType which)
{
    int type = machine->ReadRegister (2);
    int address = machine->registers[BadVAddrReg];

    switch (which)
      {
	case SyscallException:
          {
	    switch (type)
	      {
		case SC_Halt:
		  {
			printf("\n");
		    DEBUG ('s', "Shutdown, initiated by user program.\n");
		    interrupt->Halt ();
		    break;
		  }

		#ifdef CHANGED //CHANGED
		case SC_Exit :
		{
			DEBUG('a', "Arrêt du programme.\n");
			interrupt->Halt ();
            break;
		}

		case SC_PutChar:
		  {
			DEBUG ('s', "debing PutChar... \n");
			char ch =(char) machine-> ReadRegister(4);
			consoledriver->PutChar(ch);
			
			break;	
		  }

		case SC_PutString:
		  {
		    DEBUG ('s', "debing PutString... \n");

			int from;
			int tmp;
			char to[MAX_STRING_SIZE];

			from  = machine -> ReadRegister(4);

			while( (tmp = copyStringFromMachine(from, to, MAX_STRING_SIZE)) != 0 )
			{
				consoledriver->PutString(to);
				from = from + tmp;
			}
			break;	
		  }

		case SC_GetChar:
		  {
		    DEBUG ('s', "debing GetChar... \n");
            
            int c = consoledriver-> GetChar(); //valeur lu -> c
            machine->WriteRegister(2, (int) c); //  valeur -> registre 2

			break;	
		  }

		case SC_GetString:
		  {
		    DEBUG ('s', "debing GetString... \n");

			char from[MAX_STRING_SIZE];
            int to = machine->ReadRegister(4);
            int n = machine->ReadRegister(5); 
               
            consoledriver->GetString(from, n);
			copyStringToMachine(from, to, n);

			break;	
		  }

		case SC_PutInt:
		  {
			DEBUG ('s', "debing PutInt... \n");

			int n = machine->ReadRegister(4);
            consoledriver->PutInt(n);

            break;
          }

		case SC_GetInt:
          {
			  DEBUG ('s', "debing GetInt... \n");

			  int n;
              int to = machine->ReadRegister(4);

              consoledriver->GetInt(&n);
              machine->WriteMem(to, sizeof (int), n);

              break;
         }

		case SC_ThreadCreate:
		{
			DEBUG ('s', "debing ThreadCreate... \n");

			int f = machine->ReadRegister(4);
			int arg = machine->ReadRegister(5);
			
			do_ThreadCreate(f, arg);

			break;
		}

		case SC_ThreadExit:
		{
			DEBUG ('s', "debing ThreadExit... \n");

			do_ThreadExit();

			break;
		}

#endif //CHANGED

		

		default:
		  {
		    printf("Unimplemented system call %d\n", type);
		    ASSERT(FALSE);
		  }
	     }

	    // Do not forget to increment the pc before returning!
	    UpdatePC ();
	    break;
	  }

	case PageFaultException:
	  if (!address) {
	    printf("NULL dereference at PC %x!\n", machine->registers[PCReg]);
	    ASSERT (FALSE);
	  } else {
	    printf ("Page Fault at address %x at PC %x\n", address, machine->registers[PCReg]);
	    ASSERT (FALSE);	// For now
	  }
	  break;

	case ReadOnlyException:
	  printf ("Read-Only at address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case BusErrorException:
	  printf ("Invalid physical address at address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case AddressErrorException:
	  printf ("Invalid address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case OverflowException:
	  printf ("Overflow at PC %x\n", machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case IllegalInstrException:
	  printf ("Illegal instruction at PC %x\n", machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	default:
	  printf ("Unexpected user mode exception %d %d %x at PC %x\n", which, type, address, machine->registers[PCReg]);
	  ASSERT (FALSE);
	  break;
      }
}


#ifdef CHANGED //CHANGED
int copyStringFromMachine(int from, char *to, unsigned size)
{
    unsigned int i=0;
    int tmp;
    
    for(i = 0; i < size /*&& (char) tmp != '\0'*/; ++i)
    {
        machine -> ReadMem(from + i, 1, &tmp);
        to[i] =  tmp;
		if(tmp == '\0')
			return i;
        //printf("to[%d] : %d \n",i, to[i]);
    }
	
    to[i] = '\0';

    return size;
}
#endif



#ifdef CHANGED //CHANGED
int copyStringToMachine(char *from, int to, unsigned int size)
{
     int i; int tmp =0;

    for (i = 0; i < size - 1 && from[i] != '\0'; ++i)
        machine->WriteMem(to + i, 1, (unsigned int) from[i]);

    machine->WriteMem(to + i, 1, 0);

    return i;
}
#endif