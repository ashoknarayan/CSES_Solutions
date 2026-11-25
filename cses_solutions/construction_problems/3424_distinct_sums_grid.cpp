// fast.cpp
// Compile with:
// g++ -std=gnu++20 -O3 -march=native -Ofast -flto -funroll-loops -pipe -s -o fast fast.cpp

#include <bits/stdc++.h>
using namespace std;

static const int IN_BUF = 1 << 16;
static const int OUT_BUF = 1 << 20;
static char ibuf[IN_BUF];
static char obuf[OUT_BUF];
static int ip = 0, il = 0, op = 0;

inline void flush_out() {
    if (op) {
        fwrite(obuf, 1, op, stdout);
        op = 0;
    }
}

inline char next_char() {
    if (ip >= il) {
        il = fread(ibuf, 1, IN_BUF, stdin);
        ip = 0;
        if (!il) return 0;
    }
    return ibuf[ip++];
}

inline bool read_int(int &out) {
    char c;
    do { c = next_char(); if(!c) return false; } while (c <= ' ');
    int sign = 1, x = 0;
    if (c == '-') { sign = -1; c = next_char(); }
    for (; c > ' '; c = next_char()) x = x * 10 + (c - '0');
    out = x * sign;
    return true;
}

inline void write_char(char c) {
    if (op >= OUT_BUF) flush_out();
    obuf[op++] = c;
}

inline void write_int(int x) {
    if (x == 0) { write_char('0'); return; }
    if (x < 0) { write_char('-'); x = -x; }
    // write digits to temporary buffer in reverse
    char s[16]; int n = 0;
    while (x) { s[n++] = char('0' + x % 10); x /= 10; }
    for (int i = n - 1; i >= 0; --i) write_char(s[i]);
}

int main() {
    ios::sync_with_stdio(false); // harmless even if we use fread/fwrite
    cin.tie(nullptr);

    int n;
    if (!read_int(n)) return 0;

    if (n <= 3) {
        const char *t = "IMPOSSIBLE\n";
        for (const char *p = t; *p; ++p) write_char(*p);
        flush_out();
        return 0;
    }
    if (n == 4) {
        const char *t =
            "1 1 3 2\n"
            "2 1 2 4\n"
            "3 3 3 4\n"
            "2 1 4 4\n";
        for (const char *p = t; *p; ++p) write_char(*p);
        flush_out();
        return 0;
    }

    // main block: produce lines
    for (int i = 0; i < n - 2; ++i) {
        for (int j = 0; j < n - i - 2; ++j) {
            write_int(i + 2 + j); write_char(' ');
        }
        for (int j = 0; j < i; ++j) {
            write_int(j + 2); write_char(' ');
        }
        write_int(1); write_char(' ');
        write_int(i + 1); write_char('\n');
    }
    for (int j = 0; j < n - 1; ++j) {
        write_int(n - j - 1); write_char(' ');
    }
    write_int(n - 1); write_char('\n');
    for (int j = 0; j < n; ++j) {
        write_int(n); write_char(' ');
    }
    write_char('\n');

    flush_out();
    return 0;
}
