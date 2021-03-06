#include <cstdint>

namespace detail
{

uint32_t fast_utoa ( uint32_t value, char *buffer )
{
    // Copyright(c) 2014-2016 Milo Yip (https://github.com/miloyip/itoa-benchmark)
    uint32_t digits =
        value < 10          ? 1
      : value < 100         ? 2
      : value < 1000        ? 3
      : value < 10000       ? 4
      : value < 100000UL    ? 5
      : value < 1000000UL   ? 6
      : value < 10000000UL  ? 7
      : value < 100000000UL ? 8
      : value < 1000000000UL? 9
                            : 10;
    buffer += digits;
    *buffer = '\0';

    do {
        *--buffer = char(value % 10) + '0';
        value /= 10;
    } while (value > 0);

    return digits;
}

} // namespace detail

#ifndef _MSC_VER

#include <strings.h>

int stricmp( const char *s1, const char *s2 ) {
    return strcasecmp(s1, s2);
}

int strnicmp( const char *s1, const char *s2, size_t maxlen ) {
    return strncasecmp(s1, s2, maxlen);
}

#include <cctype>

char *strupr(char *s) {
    char* p = s;
    while ((*p = toupper(*p)))
        p++;
    return s;
}

// Quick and dirty implementation of itoa, ltoa, ultoa radixd on sprintf.
// It won't provide the expected results in some cases, but at least will not
// crash. Support for arbitrary bases can be later added if needed.

#include <cstdio>

static char printfFmt(int radix) {
    switch (radix) {
        case 8: return 'o';
        case 16: return 'x';
        default: return 'd';
    }
}

char *itoa( int value, char *buffer, int radix ) {
    char format[] = {'%', printfFmt(radix), '\0'};
    sprintf(buffer, format, value);
    return buffer;
}

char *ltoa( long value, char *buffer, int radix ) {
    char format[] = {'%', 'l', printfFmt(radix), '\0'};
    sprintf(buffer, format, value);
    return buffer;
}

char *ultoa( unsigned long value, char *buffer, int radix ) {
    if (radix == 10) {
        char format[] = "%lu";
        sprintf(buffer, format, value);
        return buffer;
    }
    return ltoa(value, buffer, radix);
}

#endif // _MSC_VER
