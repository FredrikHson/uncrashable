#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib.h"
#include <dlfcn.h>

sigjmp_buf before = {0};


static void sighandler(int sig, siginfo_t* info, void* ucontext)
{
    fprintf(stderr, "\e[1;31mops! something went wrong\e[0m\n");
    longjmp(before, 1);
}

void* libhandle = 0;
char libtouse = 0;
void (*lfun)() = 0;
void loadlibfun()
{
    if(libhandle != 0)
    {
        dlclose(libhandle);
    }

    if(libtouse == 0)
    {
        libhandle = dlopen("./libfun1.so", RTLD_LAZY);
        printf("loading libfun1.so\n");
        libtouse=1;
    }
    else
    {
        libhandle = dlopen("./libfun2.so", RTLD_LAZY);
        printf("loading libfun2.so\n");
        libtouse=0;
    }

    lfun = dlsym(libhandle, "libfunc");
}


int main(int argc, char* argv[])
{
    srand(time(0));
    struct sigaction sa = {0};
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_NODEFER;
    sa.sa_sigaction = sighandler;
    sigaction(SIGSEGV, &sa, 0);

    if(setjmp(before) == 0)
    {
        int* i = 0;
        *i = 1;
    }
    else
    {
        printf("only if something goes wrong\n");
    }

    while(1)
    {
        if(setjmp(before) == 0)
        {
            lfun();
            int r = rand() % 50;

            if(r == 0)
            {
                int* i = 0;
                *i = 1;
            }
            else
            {
                printf("rand %i\n", r);
            }
        }
        else
        {
            loadlibfun();
        }
    }

    sa.sa_sigaction = 0;
    sa.sa_handler = SIG_DFL;
    sigaction(SIGSEGV, &sa, 0);

    /*if(setjmp(before) == 0)*/
    /*{*/
    /*printf("should crash for reals now\n");*/
    /*int* i = 0;*/
    /**i = 1;*/
    /*}*/
    if(libhandle != 0)
    {
        dlclose(libhandle);
    }

    printf("exiting now");
    return 0;
}
