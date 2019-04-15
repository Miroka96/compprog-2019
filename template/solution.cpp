#include <bits/stdc++.h>

////////////////////////////// Helper //////////////////////

// disable debugging for submission
#define debug(x)    x
// print value of debug variable
//#define debug(x)    clog << #x << " = " << x << endl

// print a debug string
#define debugs(str) //clog << str << endl
#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define repd(a, b)   for(int a = 0; a < (b); debug(++a))
#define all(a)      (a).begin(),(a).end()

using namespace std;

////////////////////////////// I/O /////////////////////////
#define BASE 10
#define OUTPUT_LENGTH 10
#define BUFFER_SIZE 1024

// buffer stdin
char inputbuffer[BUFFER_SIZE];

int c;
bool negative_input;
// read a number from stdin into var
#define readn(var)  var = 0;                                \
                    c = getchar_unlocked();                 \
                    if (c == '-') {                         \
                        negative_input = true;              \
                        c = getchar_unlocked();             \
                    } else negative_input = false;          \
                    while (true) {                          \
                        if (c < '0') break;                 \
                        var = var * 10 + (c - '0');         \
                        c = getchar_unlocked();             \
                    }                                       \
                    if (negative_input) var = -var;         \
                    debug(var);

// create output buffer
char outputbuffer[OUTPUT_LENGTH];

// write var as number to stdout
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

////////////////////////////// Task ////////////////////////

int main(int argc, char* argv[]) {
    setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

    

    return 0;
}
