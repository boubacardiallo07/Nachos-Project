#ifdef CHANGED //~~

#include "copyright.h"
#include "system.h"
#include "consoledriver.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static Semaphore *nWrite;
static Semaphore *nRead;

static Semaphore *myread;
static Semaphore *mywrite;

static Lock* readLock;
static Lock* writeLock;

static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }

ConsoleDriver::ConsoleDriver(const char *in, const char *out)
{
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    nWrite = new Semaphore("write done", 1);
    nRead = new Semaphore("write done", 1);
    
    readLock = new Lock("readLock");
    writeLock = new Lock("writeLock");

    myread = new Semaphore("write done", 1);
    mywrite = new Semaphore("read avail", 0);
    
    console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, NULL);
}

ConsoleDriver::~ConsoleDriver()
{
    delete console;
    delete writeDone;
    delete readAvail;

    delete readLock;
    delete writeLock;

    delete myread;
    delete mywrite;
}

void ConsoleDriver::PutChar(int ch)
{
    writeLock->Acquire();

    console->TX (ch);
    writeDone->P (); 

    writeLock->Release();
}

int ConsoleDriver::GetChar()
{   
    readLock->Acquire();
    
    readAvail->P (); //

    readLock->Release();

	return console->RX ();
}

void ConsoleDriver::PutString(const char s[])
{
    int cp =0;

    if ( s == NULL)
        return;

    //writeLock->Acquire();

    while(s[cp] != '\0' && cp < MAX_STRING_SIZE)
    {
        PutChar(s[cp]);
        cp++;
    }

    //writeLock->Release();
}
 
void ConsoleDriver::GetString(char *s, int n)
{
    char buffer[MAX_STRING_SIZE];
    int cp = 0;

    if (s == NULL)
        return;

    //readLock->Acquire();
    
    while (cp < MAX_STRING_SIZE) //buffer
    { 
        buffer[cp] = consoledriver->GetChar();

        if (buffer[cp] == EOF || buffer[cp] == '\n' || buffer[cp] == '\0') {
            break;
        }
        cp++;
    }

    cp = 0;

    while (cp < n - 1) 
    {
        if (buffer[cp] == EOF || buffer[cp] == '\n')
            break;

        s[cp] = buffer[cp];
        cp++;
    }

    s[cp] = '\0';

    //readLock->Release();
}


void ConsoleDriver::PutInt(int n) 
{
    char s[MAX_STRING_SIZE];
    int r = snprintf(s, MAX_STRING_SIZE, "%i", n);

    if(r >-1)
        PutString(s);
}

void ConsoleDriver::GetInt(int *n) 
{
    char s[MAX_STRING_SIZE];

    GetString(s, MAX_STRING_SIZE);
    sscanf(s, "%i", n);
}


#endif // CHANGED
