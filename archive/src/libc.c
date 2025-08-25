#include "kernel.h"
#include "libc.h"

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char* strstr(const char* haystack, const char* needle) {
    if (!*needle) return (char*)haystack;
    char* p1 = (char*)haystack;
    while (*p1) {
        char* p1_begin = p1, * p2 = (char*)needle;
        while (*p1 && *p2 && *p1 == *p2) {
            p1++;
            p2++;
        }
        if (!*p2) return p1_begin;
        p1 = p1_begin + 1;
    }
    return 0;
}

void print_num(int n) {
    if (n < 0) {
        io_write_char('-');
        n = -n;
    }
    if (n / 10) {
        print_num(n / 10);
    }
    io_write_char((n % 10) + '0');
}
