#include <stdio.h>
#include <stdbool.h>

#define OUTPUT_LENGTH 10
#define BUFFER_SIZE 4096

int main(int argc, char* argv[])
{
    // buffer stdin
    char inputbuffer[BUFFER_SIZE];
    setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

    // create output buffer
    char outputbuffer[OUTPUT_LENGTH];

    while (true) {
        int c = fgetc(stdin);
        if (c == EOF) break;

        // initialize iteration variables
        int n = 0;
        int m = 0;

        while (true) {
            // read first number
            if (c == ' ') break;    // finished reading first number
            n = n*10 + ( c - '0');
            c = fgetc(stdin);
        }

        while (true) {
            // read last number
            c = fgetc(stdin);

            if (c == '\n') {        // finished reading last number


                // calculate result
                long operations = n * (long) m - 1;
                if (operations < 0) {
                    operations = 0;
                }




                // output result
                if (operations == 0) {
                    putc('0', stdout);
                } else {
                    char pos = OUTPUT_LENGTH - 1;
                    while (operations != 0) {
                        char rem = operations % 10;
                        operations = operations/10;
                        outputbuffer[pos--] = rem + '0';
                    }
                    for (char p = pos; p < OUTPUT_LENGTH; p++ ) {
                        putc(outputbuffer[p], stdout);
                    }
                }

                // end line output
                putc('\n', stdout);
                break;
            }

            m = m*10 + (c -'0');
        }
    }

    return 0;
}
