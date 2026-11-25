/*
https://cses.fi/problemset/task/3227
Sliding Window Advertisement
*/
#include <stdio.h>
#include <string.h>
 
#define N   200000
 
typedef __int128_t L;
 
long long max(long long a, long long b) { return a > b ? a : b; }
 
long long ft[N];
 
void ft_update(int i, int n, long long x) {
    while (i < n) {
        ft[i] = max(ft[i], x);
        i |= i + 1;
    }
}
 
long long ft_query(int i) {
    long long x = 0;
 
    while (i >= 0) {
        x = max(x, ft[i]);
        i &= i + 1, i--;
    }
    return x;
}
 
int xx[N]; long long yy[N]; int pp[N], pp_[N]; char rank[N];
 
int qu[N], head, cnt, h_;
 
L cross(int i, int j, int k) {
    return (L) (xx[j] - xx[i]) * (yy[k] - yy[i]) - (L) (xx[k] - xx[i]) * (yy[j] - yy[i]);
}
 
void add(int h) {
    int i, p;
 
    i = qu[h];
    yy[i] = (long long) -xx[i] * qu[h - 1];
    p = h < h_ ? (h + 1 == h_ ? -1 : qu[h + 1]) : (h == h_ ? -1 : qu[h - 1]);
    if (p == -1)
        pp[i] = -1, pp_[i] = -1, rank[i] = 0;
    else {
        while (pp[p] != -1)
            if (pp[pp_[p]] != -1 && cross(pp[pp_[p]], pp_[p], i) * (h < h_ ? -1 : 1) >= 0)
                p = pp_[p];
            else if (cross(pp[p], p, i) * (h < h_ ? -1 : 1) >= 0)
                p = pp[p];
            else
                break;
        pp[i] = p;
        if (pp_[p] == -1 || rank[p] != rank[pp_[p]])
            pp_[i] = p, rank[i] = 1;
        else
            pp_[i] = pp_[pp_[p]], rank[i] = rank[p] + 1;
    }
}
 
long long eval(int i, int j) {
    return (long long) xx[i] * j + yy[i];
}
 
long long query(int j) {
    int i;
    long long z;
 
    z = 0;
    if (head + 1 < h_) {
        i = qu[head + 1];
        while (pp[i] != -1)
            if (pp[pp_[i]] != -1 && eval(pp[pp_[i]], j) > eval(pp_[i], j))
                i = pp_[i];
            else if (eval(pp[i], j) > eval(i, j))
                i = pp[i];
            else
                break;
        z = max(z, eval(i, j));
    }
    if (h_ < head + cnt) {
        i = qu[head + cnt - 1];
        while (pp[i] != -1)
            if (pp[pp_[i]] != -1 && eval(pp[pp_[i]], j) > eval(pp_[i], j))
                i = pp_[i];
            else if (eval(pp[i], j) > eval(i, j))
                i = pp[i];
            else
                break;
        z = max(z, eval(i, j));
    }
    return z;
}
 
int main() {
    static long long ans[N];
    int n, k, h, i, j, r;
    long long tmp;
 
    scanf("%d%d", &n, &k);
    for (i = 0; i < n; i++)
        scanf("%d", &xx[i]);
    for (r = 0; r < 2; r++) {
        memset(ft, 0, n * sizeof *ft);
        head = cnt = 0, h_ = 0;
        for (j = 0; j < n; j++) {
            while (cnt && xx[i = qu[head + cnt - 1]] >= xx[j]) {
                if (cnt >= 2)
                    ft_update(n - 1 - i, n, (long long) xx[i] * (j - qu[head + cnt - 2] - 1));
                cnt--;
                if (cnt >= 2 && h_ > head + cnt) {
                    h_ = (head + 1 + head + cnt) / 2;
                    for (h = h_; h < head + cnt; h++)
                        add(h);
                    for (h = h_ - 1; h > head; h--)
                        add(h);
                }
            }
            qu[head + cnt++] = j;
            if (cnt == 2)
                h_ = head + 1;
            if (cnt >= 2)
                add(head + cnt - 1);
            if (j >= k - 1) {
                ans[j - k + 1] = max(ans[j - k + 1], max(max(ft_query(n - 2 - qu[head]), cnt < 2 ? 0 : query(j)), (long long) xx[qu[head]] * k));
                if (cnt && qu[head] == j - k + 1) {
                    head++, cnt--;
                    if (cnt >= 2 && h_ < head + 1) {
                        h_ = (head + 1 + head + cnt) / 2;
                        for (h = h_; h < head + cnt; h++)
                            add(h);
                        for (h = h_ - 1; h > head; h--)
                            add(h);
                    }
                }
            }
        }
        for (i = 0, j = n - 1; i < j; i++, j--)
            tmp = xx[i], xx[i] = xx[j], xx[j] = tmp;
        for (i = 0, j = n - k; i < j; i++, j--)
            tmp = ans[i], ans[i] = ans[j], ans[j] = tmp;
    }
    for (i = 0; i <= n - k; i++)
        printf("%lld ", ans[i]);
    printf("\n");
    return 0;
}
