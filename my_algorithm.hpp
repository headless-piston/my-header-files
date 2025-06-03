//some templates
#ifndef MY_ALGORITHM
#define MY_ALGORITHM
#include<cmath>
template<typename T>
inline T Max(const T &a,const T &b){
    return a<b?b:a;
}
template<typename T>
inline T Min(const T &a,const T &b){
    return a<b?a:b;
}
template<typename T>
inline void Swap(T &a,T &b){
    T c=a;
    a=b;
    b=c;
    return;
}
template<typename T>
inline T gcd(T m,T n){
    while(n!=0){
        int t=m%n;
        m=n;
        n=t;
    }
    return m;
}
template<typename T,typename...Args>
T gcd(T m,T n,Args...args){
    return gcd(gcd(m,n),args...);
}
template<typename T>
inline T lcm(T m,T n){
    return m/gcd(m,n)*n;
}
template<typename T,typename...Args>
T lcm(T m,T n,Args...args){
    return lcm(lcm(m,n),args...);
}
template<typename T>
T exgcd(T a,T b,T &x,T &y){
    if(b==0){
        x=1,y=0;
        return a;
    }
    T d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
template<typename T>
inline T phi(T n){
    T res=n;
    for(T i=2;i*i<=n;i++)
        if(n%i==0){
            res=res/i*(i-1);
            while(n%i==0)
                n/=i;
        }
    if(n>1)
        res=res/n*(n-1);
    return res;
}
template<typename Size,typename T>
inline T crt(Size n,T *a,T *p){
    T P=1;
    for(Size i=0;i<n;i++)
        P*=p[i];
    T x=0;
    for(Size i=0;i<n;i++){
        T Pi=P/p[i];
        T xi,yi;
        exgcd(Pi,p[i],xi,yi);
        x+=a[i]*Pi*xi;
    }
    return x%P;
}
template<typename Size,typename T>
inline T excrt(Size n,T *a,T *p){
    T a1=a[0],p1=p[0];
    for(Size i=1;i<n;i++){
        T a2=a[i],p2=p[i],xi,yi;
        T g=exgcd(p1,p2,xi,yi);
        if((a2-a1)%g!=0)
            return -1;
        T lcm=p1/g*p2,diff=(a2-a1)/g;
        a1=a1+xi*diff%(p2/g)*p1;
        p1=lcm;
    }
    return (a1+p1)%p1;
}
typedef long long ll;
typedef unsigned long long ull;
#endif
