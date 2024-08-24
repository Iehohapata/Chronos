#include "includes.h"
int str_to_timestamp(char *);

// Simplified usage: chronos <filename> "CCYY/MM/DD hh:mm:ss"
int main(int argc, char *argv[]) {
#if defined (WINDOWS_OS) || defined (LINUX_OS)
    time_t time_in;
    if ((time_in = str_to_timestamp(argv[2])) < 0) {
        exit(EXIT_FAILURE);
    }
    set_timestamp(argv[1], time_in);
    exit(EXIT_SUCCESS);
#elif defined (MAC_OS)
    return set_timestamp(argv[1], argv[2]);
#endif
}
