#ifdef CHANGED

#include "machine.h"
#include "thread.h"
#include "userthread.h"

struct myThread {
    int f;
    int arg;
};


myThread *thrd =(myThread*) malloc (sizeof(myThread));

extern Machine* machine;
extern Thread* currentThread;

 

static void StartUserThread(void *schmurtz)
{
    myThread *str = (myThread*) schmurtz;

    int i;
    for (i = 0; i < NumTotalRegs; i++)
	    machine->WriteRegister (i, 0);

    machine->WriteRegister (4, str->arg);
    machine->WriteRegister (PCReg, str->f);

    machine->WriteRegister(NextPCReg, machine->ReadRegister(PCReg) + 4);

    machine->WriteRegister (StackReg, currentThread->space->AllocateUserStack() );
    DEBUG ('x', "Registre de pile : 0x%x\n",
	   currentThread->space->AllocateUserStack() );
       

    machine->DumpMem("threads.svg");
    machine->Run();
}


int do_ThreadCreate(int f, int arg)
{
    //printf("debug......................");
    thrd->f = f;
    thrd->arg = arg;    

    Thread* thread = new Thread("new thread");
    
    thread->Start(StartUserThread, (void*)thrd);

    return 0;
}


void do_ThreadExit(){
    currentThread->Finish();
}



// //renvoie une case libre du tableau userThreadList

// int FreeUserThread() {
//     int i;

//     for (i = 0; i < MAX_USERTHREAD; i++) {
//         if (currentThread->space->getThreadTab(i) == 0) {
//             return i;
//         }
//     }

//     return -1;
// }


#endif //CHANGED
