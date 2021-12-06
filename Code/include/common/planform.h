#ifndef _PLANTFORM_H_
#define _PLANTFORM_H_
#ifdef WIN32
#else
#include <signal.h>
const int BIND_FAILED_EXIT = SIGUSR2*2;
#endif

#endif