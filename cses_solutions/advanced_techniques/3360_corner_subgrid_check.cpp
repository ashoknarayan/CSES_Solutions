#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;
 
bool rows[3000];
 
char input_buf[10000000];
int input_idx = 0;
#define read_char() (input_buf[input_idx++])
 
short n = 0, K = 0;
char grid[3000][3000];
short mem[9000000];
short *row[26][3001];
short row_cnt[26][3000];
short matches[3000][3000];
short match_cnt[3000];
 
int main()
{
    read(0, input_buf, 10000000);
    char c = read_char();
    while ('0' <= c && c <= '9') {
        n = 10 * n + c - '0';
        c = read_char();
    }
    c = read_char();
    while ('0' <= c && c <= '9') {
        K = 10 * K + c - '0';
        c = read_char();
    }
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = read_char() - 'A';
            row_cnt[grid[i][j]][i]++;
        }
        input_idx++;
    }
 
    row[0][0] = &mem[0];
    for (int l = 0; l < K; l++) {
        for (int i = 1; i <= n; i++)
            row[l][i] = row[l][i-1] + row_cnt[l][i-1];
        if (l + 1 < K)
            row[l+1][0] = row[l][n-1] + row_cnt[l][n-1];
    }
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            row[grid[i][j]][i][--row_cnt[grid[i][j]][i]] = j;
        }
    }
 
    for (int l = 0; l < K; l++) {
        bool has = 0;
        for (int i = 0; i < n; i++) {
            for (short *x = row[l][i]; x < row[l][i+1]; x++) {
                for (int k = 0, y; k < match_cnt[*x]; k++)
                {
                    y = matches[*x][k];
                    if (rows[y])
                    {
                        has = 1;
                        goto end;
                    }
                    rows[y] = 1;
                }
                matches[*x][match_cnt[*x]++] = i;
            }
            memset(rows, 0, sizeof(rows));
        }
    end:
        cout << ((has) ? "YES" : "NO") << '\n';
        for (int i = 0; i < n; i++)
            match_cnt[i] = 0;
    }
}
