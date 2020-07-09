#include "converter.h"
#include "util.h"

int convert(FILE *fin, FILE *fout) {
    static char buf[1000];
    unsigned buf_u;
    double buf_d;
    const char *out;
    fscanf(fin, "%s", buf);
    fprintf(fout, "const short %s[] = {\n", buf);
    fscanf(fin, "%s%u", buf, &buf_u);
    set_base(*buf);
    set_base_time(buf_u);
    
    fscanf(fin, "%s%lf", buf, &buf_d);
    for (; !feof(fin); fscanf(fin, "%s%lf", buf, &buf_d)) {
        if (translate(buf, &out)) {
            return 1;
        }
        fprintf(fout, "    %s, %u,\n", out, (unsigned)(base_time * buf_d));
    }
    fputs("    TONES_END\n};\n", fout);
    return 0;
}
