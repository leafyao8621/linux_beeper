#include <stdio.h>

static const char *lookup[] = {
    "NOTE_B0",
    "NOTE_C1",
    "NOTE_CS1",
    "NOTE_D1",
    "NOTE_DS",
    "NOTE_E1",
    "NOTE_F1",
    "NOTE_FS1",
    "NOTE_G1",
    "NOTE_GS1",
    "NOTE_A1",
    "NOTE_AS1",
    "NOTE_B1",
    "NOTE_C2",
    "NOTE_CS2",
    "NOTE_D2",
    "NOTE_DS2",
    "NOTE_E2",
    "NOTE_F2",
    "NOTE_FS2",
    "NOTE_G2",
    "NOTE_GS2",
    "NOTE_A2",
    "NOTE_AS2",
    "NOTE_B2",
    "NOTE_C3",
    "NOTE_CS3",
    "NOTE_D3",
    "NOTE_DS3",
    "NOTE_E3",
    "NOTE_F3",
    "NOTE_FS3",
    "NOTE_G3",
    "NOTE_GS3",
    "NOTE_A3",
    "NOTE_AS3",
    "NOTE_B3",
    "NOTE_C4",
    "NOTE_CS4",
    "NOTE_D4",
    "NOTE_DS4",
    "NOTE_E4",
    "NOTE_F4",
    "NOTE_FS4",
    "NOTE_G4",
    "NOTE_GS4",
    "NOTE_A4",
    "NOTE_AS4",
    "NOTE_B4",
    "NOTE_C5",
    "NOTE_CS5",
    "NOTE_D5",
    "NOTE_DS5",
    "NOTE_E5",
    "NOTE_F5",
    "NOTE_FS5",
    "NOTE_G5",
    "NOTE_GS5",
    "NOTE_A5",
    "NOTE_AS5",
    "NOTE_B5",
    "NOTE_C6",
    "NOTE_CS6",
    "NOTE_D6",
    "NOTE_DS6",
    "NOTE_E6",
    "NOTE_F6",
    "NOTE_FS6",
    "NOTE_G6",
    "NOTE_GS6",
    "NOTE_A6",
    "NOTE_AS6",
    "NOTE_B6",
    "NOTE_C7",
    "NOTE_CS7",
    "NOTE_D7",
    "NOTE_DS7",
    "NOTE_E7",
    "NOTE_F7",
    "NOTE_FS7",
    "NOTE_G7",
    "NOTE_GS7",
    "NOTE_A7",
    "NOTE_AS7",
    "NOTE_B7",
    "NOTE_C8",
    "NOTE_CS8",
    "NOTE_D8",
    "NOTE_DS8"
};

static const char **base;
unsigned short base_time;

int set_base(char c) {
    switch (c) {
    case 'C':
    case 'c':
        base = lookup + 37;
        return 0;
    case 'D':
    case 'd':
        base = lookup + 39;
        return 0;
    case 'E':
    case 'e':
        base = lookup + 41;
        return 0;
    case 'F':
    case 'f':
        base = lookup + 42;
        return 0;
    case 'G':
    case 'g':
        base = lookup + 44;
        return 0;
    case 'A':
    case 'a':
        base = lookup + 46;
        return 0;
    case 'B':
    case 'b':
        base = lookup + 48;
        return 0;
    default:
        return 1;
    }
}

int set_base_time(unsigned bpm) {
    base_time = 60.0 / bpm * 1000;
    return 0;
}

static int offset(const char *in, int *out) {
    static int offset_lookup[] = {
        0,
        2,
        4,
        5,
        7,
        9,
        11
    };
    int idx = *in - '0' - 1;
    if (idx > 6 || idx < 0) {
        return 1;
    }
    switch (in[1]) {
    case 0:
    case '^':
    case '_':
        *out = offset_lookup[idx];
        return 0;
    case 'S':
    case 's':
        *out = offset_lookup[idx] + 1;
        return 0;
    default:
        return 2;
    }
}

static int octave(const char *in, int *out) {
    int temp = 0;
    switch (*in) {
    case '_':
        temp = -(in[1] - '0') * 12;
        break;
    case '^':
        temp = (in[1] - '0') * 12;
        break;
    default:
        return 1;
    }
    *out = temp;
    return 0;
}

int translate(char *in, const char **out) {
    if (*in == '0') {
        *out = "NOTE_REST";
        return 0;
    }
    int of, oc;
    const char *oc_start;
    of = oc = 0;
    for (oc_start = in; *oc_start && *oc_start != '_' && *oc_start != '^';
         ++oc_start);
    if (offset(in, &of)) {
        return 2;
    }
    if (*oc_start) {
        if (octave(oc_start, &oc)) {
            return 3;
        }
    }
    *out = base[of + oc];
    return 0;
}
