#include <bits/stdc++.h>

////////////////////////////// Helper //////////////////////

// disable debugging for submission
//#define debug(x)    x
// print value of debug variable
#define debug(x)    clog << #x << " = " << x << endl

// print a debug string
#define debugs(str) //clog << str << endl
#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define repd(a, b)   for(int a = 0; a < (b); debug(++a))
#define all(a)      (a).begin(),(a).end()

using namespace std;

////////////////////////////// I/O /////////////////////////
#define BUFFER_SIZE 1024

// buffer stdin
char inputbuffer[BUFFER_SIZE];


////////////////////////////// Task ////////////////////////

// '0' = 48
// 'A' = 65
char translation[91] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 0, '1', 'S', 'E', 0, 'Z', 0, 0, '8', 0, ':', ';', '<', '=', '>', '?', '@', 'A', 0, 0, 0, '3', 0, 0, 'H', 'I', 'L', 0, 'J', 'M', 0, 'O', 0, 0, 0, '2', 'T', 'U', 'V', 'W', 'X', 'Y', '5'};

#define MAX_STRING_LENGTH 10000
char stringBuffer[MAX_STRING_LENGTH];
char translatedStringBuffer[MAX_STRING_LENGTH];

constexpr char notPalindrome[] = " -- is not a palindrome.";
constexpr char palindrome[] = " -- is a regular palindrome.";
constexpr char mirrored[] = " -- is a mirrored string.";
constexpr char mirroredPalindrome[] = " -- is a mirrored palindrome.";

inline void print(const char* str) {
    for (const char* c = str; *c; c++) {
        putchar_unlocked(*c);
    }
}

inline bool isPalindrome(short end) {
    for(short start = 0; start <= end; start++, end--) {
        if (stringBuffer[start] != stringBuffer[end]) return false;
    }
    return true;
}

inline bool isMirrored(short inputSize) {
    for(short start = 0, end = inputSize; end >= 0; start++, end--) {
        register char t = translation[stringBuffer[end]];
        if (t == 0 || stringBuffer[start] != t) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

    register char c = getchar_unlocked(); 
    register short i = 0;

    for ( ; c != '\n'; c = getchar_unlocked(), i++ ) {
        stringBuffer[i] = c;
        translatedStringBuffer[i] = translation[c];
        putchar_unlocked(c);
    }
    i--;

    if (isPalindrome(i)) {
        if (isMirrored(i)) {
            print(mirroredPalindrome);
        } else {
            print(palindrome);
        }
    } else {
        if (isMirrored(i)) {
            print(mirrored);
        } else {
            print(notPalindrome);
        }
    }
    putchar_unlocked('\n');

    return 0;
}
