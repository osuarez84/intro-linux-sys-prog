/*****************************************************************************
* Build with: gcc -Wall -g -I ../include/ -L ../lib/ -o spl_date1 \
* spl_date1.c -lspl
*****************************************************************************/
#include "common_hdrs.h"

int main(int argc, char* argv[]) {
    time_t current_time_seconds;
    struct tm* broken_down_current_time;
    char formatted_time[STRING_MAX];

    // get the current time
    // sys call
    current_time_seconds = time(NULL);
    
    // convert current time into broken-down time
    // function call
    broken_down_current_time = localtime(&current_time_seconds);
    if (broken_down_current_time == NULL) {
        fatal_error(EOVERFLOW, "localtime");
    }

    // print string to stdout
    // function call
    if (strftime(formatted_time, STRING_MAX, "%c", broken_down_current_time) == 0 ) {
        fatal_error(EXIT_FAILURE, "Conversion to a date-time string failed or produced an empty string\n");
    }

    printf("Result string is %s\n", formatted_time);
    return 0;
}