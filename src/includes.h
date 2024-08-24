#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#ifdef WINDOWS_OS
	#include <Windows.h>
void print_err(DWORD);
extern FILETIME filetime;
#elif LINUX_OS
    #include <limits.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <unistd.h>
    #define SEC 1000000000L
    #define PERMS 0776
    #define TEMP_NAME "__replaced"
int set_timestamp(char *, time_t);
#elif MAC_OS
int set_timestamp(const char *filename, const char *date);
#endif
