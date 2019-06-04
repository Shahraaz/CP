#include <cstdio>
#include <cassert>

using namespace std;

int mod = 1000000009;

int tr[1<<18 + 10];
int sz, off;

void initIt(int s) {
    sz = s;
    off = 0;
    for(int i=0;i<sz;i++) tr[i]=0;
}

void rotate(int by) {
    off -= by;
    while(off < 0) off += sz;
}

void _addIt(int v, int idx) {
    if(idx == 0) {
        tr[0] += v;
        tr[0] %= mod;
        return;
    }
    while(idx < sz) {
        tr[idx] += v;
        tr[idx] %= mod;
        idx += (idx&-idx);
    }
}

void addIt(int v, int idx) {
    int tidx = (idx + off) % sz;
    _addIt(v,tidx);
}

int _getIt(int idx) {
    int ret = tr[0];
    while(idx) {
        ret += tr[idx];
        ret %= mod;
        idx -= (idx&-idx);
    }
    return ret;
}

int getIt(int idx) {
    assert(idx < sz);
    if(off + idx < sz) {
        int ret = _getIt(off+idx);
        if(off) {
            ret -= _getIt(off-1);
            ret += mod;
            ret %= mod;
        }
        return ret;
    }
    assert(off);
    int ret = _getIt(sz-1);
    ret -= _getIt(off-1);
    ret += mod;
    ret %= mod;
    int t = (off + idx) % sz;
    ret += _getIt(t);
    ret %= mod;
    return ret;
}

int getRange(int st, int en) {
    int ret = getIt(en);
    if(st) {
        ret -= getIt(st-1);
        ret += mod;
        ret %= mod;
    }
    return ret;
}

int A[1<<18];

int main() {
    int T;
    scanf("%d",&T);
    assert(1 <= T && 10 >= T);
    while(T--) {
        int N, M;
        scanf("%d %d",&N,&M);
        for(int i=0;i<N;i++) {
            scanf("%d",&A[i]);
            assert(0 <= A[i] && (1<<M) > A[i]);
        }
        int ulim = (1<<M);
        int lim = (1<<(M-1)) - 1;
        initIt(ulim);
        addIt(1,A[0]);
        //for(int l=0;l<ulim;l++) { printf("%d ",getRange(l,l)); } printf("\n");
        for(int i=1;i<N;i++) {
            int su = getIt(lim);
            rotate(A[i]);
            addIt(su,A[i]);
            //for(int l=0;l<ulim;l++) { printf("%d ",getRange(l,l)); } printf("\n");
        }
        printf("%d\n",getIt(lim));
    }
    return 0;
}

