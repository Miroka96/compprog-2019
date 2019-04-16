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

#define uint unsigned int
#define ulong unsigned long

using namespace std;

////////////////////////////// I/O /////////////////////////
#define BASE 10
#define OUTPUT_LENGTH 24
#define BUFFER_SIZE 1024

// buffer stdin
char inputbuffer[BUFFER_SIZE];

template<typename T> inline void readn(T &x) 
{ 
    x = 0; 
    bool neg = 0; 
    register T c = getchar_unlocked(); 
  
    if (c == '-') 
        neg = 1, c = getchar_unlocked(); 
  
    for ( ; c >= '0' && c <= '9'; c = getchar_unlocked() ) 
        x = (x << 3) + ( x << 1 ) + ( c & 15 ); 
  
    if (neg) x *= -1; 
} 

// create output buffer
char outputbuffer[OUTPUT_LENGTH];

template<typename T> inline void write(T n) 
{ 
    bool neg = 0; 
    if (n < 0) n *= -1, neg = 1; 
  
    int i = 0; 
    do { 
        outputbuffer[i++] = n % 10 + '0'; 
        n /= 10; 
    } while (n); 
    --i; 
  
    if (neg) putchar_unlocked('-'); 
  
    while (i >= 0) putchar_unlocked(outputbuffer[i--]); 
  
    putchar_unlocked('\n'); 
} 

////////////////////////////// Task ////////////////////////

//#define MAX_VALUE 1000000008

//bitset<MAX_VALUE> bloomfilter;

int main(int argc, char* argv[]) {
    setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

    short triplesc;
    readn(triplesc);

    unordered_map<ulong, short> numberCounts;
    numberCounts.reserve(triplesc);

    rep(in, triplesc){
        ulong input;
        readn(input);

        short &stored_val = numberCounts[input];
        stored_val++;
    }

    ulong resultCount = 0;

    for (auto ifirst = numberCounts.begin(); ifirst != numberCounts.end(); ifirst++) {
        auto firstc = ifirst->second;
        debug(firstc);
        auto first = ifirst->first;
        debug(first);

        if (firstc >= 2) {
            auto third = numberCounts.find(first * 2);
            if (third != numberCounts.end()) {
                resultCount += firstc * ((ulong) firstc - 1) / 2 * third->second;
            }
            debug(firstc);
        }

        for (auto isecond = ifirst; ++isecond != numberCounts.end();) {
            auto secondc = isecond->second;
            debug(secondc);
            ulong sum = first + isecond->first;
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
