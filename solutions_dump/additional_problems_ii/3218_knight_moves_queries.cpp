#include <stdio.h>
#include <algorithm>
#include <utility>
using namespace std;
typedef long long ll;
 
const int MDGTS = 10, PW10[MDGTS] = {0, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
const int IO_SZ = 2 << 20;
char _buf[IO_SZ], *_ii = _buf, *_oi = _buf;
template <typename T> void scan(T &x){for(x=*_ii++-'0'; *_ii++>='0'; x=x*10+_ii[-1]-'0');}
template <typename T> void print(T x){int dgts=0; for(; dgts<MDGTS && PW10[dgts]<=x; ++dgts); for(char *i=_oi+dgts-1; i>=_oi; i--) *i=x%10+'0', x/=10; _oi+=dgts;}
 
int solve(){
    int x, y;
    scan(x); scan(y);
    x--; y--;
    if(x+y == 1) return 3;
    if(x == 2 && y == 2) return 4;
    if(x == 1 && y == 1) return 4;
    if(x < y) swap(x, y);
 
    if(y*2 <= x){
        int v = (x+1)/2;
        v += (x^y^v) & 1;
        return v;
    }
    
    int v = (x+y+2)/3;
    v += (x+y) % 3 == 2;
    return v;
}
 
int main(){
    fread(_buf, 1, IO_SZ, stdin);
    int t; scan(t);
    while(t--) print(solve()), *_oi++ = '\n';
    fwrite(_buf, 1, _oi-_buf, stdout);
}
