#include <stdio.h>
#include <stdlib.h>
#include "disemvowel.h"

int main() {
    char buffer[1024];

    // Read from standard input line by line
    while (fgets(buffer, sizeof(buffer), stdin)) {
        char *dis = disemvowel(buffer);
        if (dis) {
            fputs(dis, stdout);  // write to standard output
            free(dis);
        }
    }

    return 0;
}