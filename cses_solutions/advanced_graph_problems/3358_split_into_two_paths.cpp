#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define N   200000
 
int *ej[N], eo[N], fo[N];
 
void append(int i, int j) {
    int o = eo[i]++;
 
    if (o >= 2 && (o & o - 1) == 0)
        ej[i] = (int *) realloc(ej[i], o * 2 * sizeof *ej[i]);
    ej[i][o] = j, fo[j]++;
}
 
int main() {
    static int qu[N], hh[N], kk[N], pp[N], cc[N];
    int n, m, cnt, h, h_, i, j, o, c, k1, k2;
 
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++)
        ej[i] = (int *) malloc(2 * sizeof *ej[i]);
    for (h = 0; h < m; h++) {
        scanf("%d%d", &i, &j), i--, j--;
        append(i, j);
    }
    cnt = 0;
    for (i = 0; i < n; i++)
        if (fo[i] == 0)
            qu[hh[i] = cnt++] = i;
    for (h = 0; h < cnt; h++) {
        i = qu[h];
        for (o = eo[i]; o--; ) {
            j = ej[i][o];
            if (--fo[j] == 0)
                qu[hh[j] = cnt++] = j;
        }
    }
    for (h = 0; h + 1 < n; h++) {
        i = qu[h];
        kk[h + 1] = 1;
        for (o = eo[i]; o--; ) {
            j = ej[i][o];
            if (j == qu[h + 1]) {
                kk[h + 1] = 0;
                break;
            }
        }
    }
    for (h = 1; h < n; h++)
        kk[h] += kk[h - 1];
    memset(pp, -1, n * sizeof *pp), pp[0] = -2;
    for (h = 0; h < n; h++)
        if (pp[h] != -1) {
            if (h == 0) {
                for (h_ = 1; h_ < n; h_++)
                    if (kk[h_ - 1] == 0)
                        pp[h_] = h;
            } else {
                i = qu[h - 1];
                for (o = eo[i]; o--; ) {
                    j = ej[i][o], h_ = hh[j];
                    if (h < h_ && kk[h_ - 1] - kk[h] == 0)
                        pp[h_] = h;
                }
            }
            if (kk[n - 1] - kk[h] == 0) {
                c = 1;
                for (h_ = h + 1; h_ < n; h_++)
                    cc[h_] = 1;
                while (h > 0) {
                    cc[h] = c;
                    for (h_ = pp[h] + 1; h_ < h; h_++)
                        cc[h_] = c ^ 3;
                    h = pp[h], c ^= 3;
                }
                cc[0] = c;
                printf("YES\n");
                k1 = k2 = 0;
                for (h = 0; h < n; h++)
                    if (cc[h] == 1)
                        k1++;
                    else
                        k2++;
                printf("%d", k1);
                for (h = 0; h < n; h++)
                    if (cc[h] == 1)
                        printf(" %d", qu[h] + 1);
                printf("\n");
                printf("%d", k2);
                for (h = 0; h < n; h++)
                    if (cc[h] == 2)
                        printf(" %d", qu[h] + 1);
                printf("\n");
                return 0;
            }
        }
    printf("NO\n");
    return 0;
}
