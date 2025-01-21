#include<stdio.h>
using namespace std;
namespace FastIO{
    char buffer[100005],*p1=buffer,*p2=buffer;
    #define getchar() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,100000,stdin),p1==p2)?EOF:*p1++)
    inline void read(int &x){
        char c=getchar();x=0;
        while(c<'0'||c>'9')c=getchar();
        while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+c-'0',c=getchar();
    }
    inline void read(long long &x){
        char c=getchar();x=0;
        while(c<'0'||c>'9')c=getchar();
        while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+c-'0',c=getchar();
    }
    template<typename T,typename...Args>
    inline void read(T &x,Args&...args){
        read(x);
        read(args...);
    }
}
using FastIO::read;