#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>
#include <assert.h>
#include "base64.c"

char *base64_encode(const unsigned char *data,
                    size_t input_length,
                    size_t *output_length);
unsigned char *base64_decode(const char *data,
                             size_t input_length,
                             size_t *output_length);

void  aLARMhandler(int sig) {
    exit(1);
}

int main(int argc, char *argv[]) {
    char *value, buf[409600];
    int len;
    size_t olen = 0;

    signal(SIGALRM, SIG_IGN);          /* ignore this signal       */
    alarm(2);
    signal(SIGALRM, aLARMhandler);     /* reinstall the handler    */

    len = fread(buf, 1, sizeof(buf), stdin);
    if(len <= 0) {
        return -1;
    }

    buf[len] = '\0';
    if(NULL != strstr(argv[0], "dec")) {
        value = base64_decode(buf, (size_t)len, &olen);
    } else {
        value = base64_encode(buf, (size_t)len, &olen);
    }
    if(NULL == value) {
        return -1;
    }
    value[olen] = '\0';

    fwrite(value, 1, olen, stdout);
    fflush(stdout);

    return 0;
}

