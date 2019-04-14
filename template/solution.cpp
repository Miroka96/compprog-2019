#include <bits/stdc++.h>

#define BASE 10
#define OUTPUT_LENGTH 10
#define BUFFER_SIZE 4096

// buffer stdin
char inputbuffer[BUFFER_SIZE];

#define read(var, c, delimeter) while (true) { \
    if (c == delimeter) break; \
    var = var * 10 + (c - '0'); \
    c = fgetc(stdin);\
}

// create output buffer
char outputbuffer[OUTPUT_LENGTH];

#define write(var) if (var == 0) { \
    putc('0', stdout); \
    }else{ \
    char pos = OUTPUT_LENGTH; \
    while (var != 0) { \
        char rem = var % BASE; \
        var = var/BASE; \
        outputbuffer[--pos] = rem + '0'; \
    } \
    for (char p = pos; p < OUTPUT_LENGTH; p++ ) { \
        putc(outputbuffer[p], stdout); \
    } \
}   \
putc('\n', stdout);



int main(int argc, char* argv[]) {
    setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

    while (true) {
        int c = fgetc(stdin);
        if (c == EOF) break;

        // initialize iteration variables
        int n = 0;
        int m = 0;

        read(n, c, ' ');    // read first number
        c = fgetc(stdin);
        read(m, c, '\n');    // read second number

        // calculate result
        long operations = n * (long) m - 1;
        if (operations < 0) {
            operations = 0;
        }

        write(operations);
    }

    return 0;
}
