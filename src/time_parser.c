#ifdef LINUX_OS
    #define _XOPEN_SOURCE
#endif
#include "includes.h"

enum DST {IN_EFFECT = 1, NO_EFFECT = 0, AUTO = -1 };
// supposed time format "1970/01/01 00:00:00"
//                      "CCYY/MM/DD hh:mm:ss"
time_t str_to_timestamp(char *str){

#ifdef LINUX_OS
    struct tm time_in;
    if (*strptime(str, "%Y/%m/%d %H:%M:%S", &time_in) != '\0') {
        fprintf(stderr, "Date hasn't been parsed.");
        return -1;
    }
    time_in.tm_isdst = AUTO;

    return mktime(&time_in);
#elif defined WINDOWS_OS
    SYSTEMTIME time_in;
    int parse_result = sscanf(str, "%hd/%hd/%hd %hd:%hd:%hd",
        &time_in.wYear, &time_in.wMonth, &time_in.wDay,
        &time_in.wHour, &time_in.wMinute, &time_in.wSecond); // Day of week is ignored in convertion to FILETIME

    if (parse_result == EOF || parse_result < 6) {
        perror("Arguments passed incorectly");
        return -1;
    }

    SYSTEMTIME st;
    GetSystemTime(&st);
    time_in.wMilliseconds = st.wMilliseconds;

    TIME_ZONE_INFORMATION tz_info;
    GetTimeZoneInformation(&tz_info);
    SYSTEMTIME time_tmp = time_in;
    TzSpecificLocalTimeToSystemTime(&tz_info, &time_tmp, &time_in);

    SetLastError(0);
    if (!SystemTimeToFileTime(&time_in, &filetime)) {
        print_err(GetLastError());
        return -1;
    }
    return 0;
#endif
}
