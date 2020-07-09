#include <stdio.h>
#include "converter.h"

int main(int argc, const char **argv) {
    FILE *fin, *fout;
    fin = stdin;
    fout = stdout;
    if (argc >= 2) {
        fin = fopen(argv[1], "r");
        if (!fin) {
            puts("Read error");
            return 1;
        }
    }
    if (argc >= 3) {
        fout = fopen(argv[2], "w");
        if (!fout) {
            fclose(fin);
            puts("Write error");
            return 1;
        }
    }
    if (convert(fin, fout)) {
        if (argc >= 2) {
            fclose(fin);
        }
        if (argc >= 3) {
            fclose(fout);
        }
        puts("Syntax error");
        return 1;
    }
    if (argc >= 2) {
        fclose(fin);
    }
    if (argc >= 3) {
        fclose(fout);
    }
    return 0;
}
