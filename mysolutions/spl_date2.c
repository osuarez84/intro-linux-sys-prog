/*****************************************************************************
* Build with: gcc -Wall -g -I ../include/ -L ../lib/ -o spl_date2 \
* spl_date2.c -lspl
*****************************************************************************/

#define _GNU_SOURCE
#include "common_hdrs.h"

void getformat(int nargs, char* argvec[], char* format_str);

// get the format from arguments
void getformat(int nargs, char* argvec[], char* format_str) {
    char err_msg[MAXLEN];

    if (nargs < 2) {
        strcpy(format_str, "%c");
    } else {
        // check if the arg has the correct format
        if (argvec[1][0] != '+') {
            sprintf(err_msg, "%s: Format should be +\"format-string\"\n", basename(argvec[0]));
            fatal_error(BAD_FORMAT_ERROR, err_msg);
        }

        if (strlen(argvec[1]) >= MAXLEN) {
            sprintf(err_msg, "Format strig length is too long\n");
            fatal_error(BAD_FORMAT_ERROR, err_msg);
        }
        strcpy(format_str, argvec[1]);
    }
}



int main(int argc, char* argv[]) {
    time_t current_time_seconds;
    struct tm* broken_down_current_time;
    char formatted_time[STRING_MAX];
    char format_str[MAXLEN];

    getformat(argc, argv, format_str);

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
    if (strftime(formatted_time, STRING_MAX, format_str, broken_down_current_time) == 0 ) {
        fatal_error(EXIT_FAILURE, "Conversion to a date-time string failed or produced an empty string\n");
    }

    printf("Result string is %s\n", formatted_time);
    return 0;
}