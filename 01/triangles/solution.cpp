#include <bits/stdc++.h>

////////////////////////////// Helper //////////////////////

// disable debugging for submission
#define debug(x)    x
// print value of debug variable
//#define debug(x)    clog << #x << " = " << x << endl

// print a debug string
#define debugs(str) clog << str << endl
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
                    while (true) {                          \
                        if (c < '0') break;                 \
                        var = var * 10 + (c - '0');         \
                        c = getchar_unlocked();             \
                    }                                       \
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

//                      k =  2 3 4 5  6  7  8  9  10 11 12 13 14 15  16  17  18  19
constexpr unsigned char TwoOutOf[] = {1,3,6,10,15,21,28,36,45,55,66,78,92,107,123,140,158,177};

int main(int argc, char* argv[]) {
    setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

    short triplesc;
    readn(triplesc);

    unordered_map<unsigned long, short> numberCounts;
    numberCounts.reserve(triplesc);

    rep(in, triplesc){
        unsigned long input;
        readn(input);

        short &stored_val = numberCounts[input];
        stored_val++;
    }

    unsigned long resultCount = 0;

    for (auto ifirst = numberCounts.begin(); ifirst != numberCounts.end(); ifirst++) {
        auto firstc = ifirst->second;
        debug(firstc);
        auto first = ifirst->first;
        debug(first);

        if (firstc >= 2) {
            auto third = numberCounts.find(first * 2);
            if (third != numberCounts.end()) {
                int twoOutOf;
                if (firstc <= 19) {
                    twoOutOf = TwoOutOf[firstc - 2];
                } else {
                    twoOutOf = firstc * (firstc - 1) / 2;
                }
                resultCount += twoOutOf * third->second;
            }
            debug(firstc);
        }

        for (auto isecond = ifirst; ++isecond != numberCounts.end();) {
            auto secondc = isecond->second;
            debug(secondc);
            unsigned long sum = first + isecond->first;
            debug(sum);
            auto third = numberCounts.find(sum);
            if (third != numberCounts.end()) {
                resultCount += firstc * secondc * third->second;
                debug(resultCount);
            }
        }
    }

    write(resultCount);

    return 0;
}
