//some templates
#ifndef MY_ALGORITHM
#define MY_ALGORITHM
#include<cmath>
const double PI=4*atan(1);
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
struct comp{
    double real,imag;
    comp operator+(const comp &x)const{
        return {real+x.real,imag+x.imag};
    }
    comp operator-(const comp &x)const{
        return {real-x.real,imag-x.imag};
    }
    comp operator*(const comp &x)const{
        return {real*x.real-imag*x.imag,real*x.imag+x.real*imag};
    }
    comp operator/(const unsigned &x)const{
        return {real/(double)x,imag/(double)x};
    }
};
void fft(comp *f,unsigned n,int rev){
    for(unsigned i=1,j=n>>1,k;i<n-1;i++){
        if(i<j)
            Swap(f[i],f[j]);
        k=n>>1;
        while(j>=k){
            j-=k;
            k>>=1;
        }
        j+=k;
    }
    for(unsigned l=2;l<=n;l<<=1){
        double arg=2*PI*rev/l;
        comp wn={cos(arg),sin(arg)};
        for(unsigned i=0;i<n;i+=l){
            comp w={1,0};
            for(unsigned j=0;j<(l>>1);j++){
                comp f1=f[i+j];
                comp f2=f[i+j+(l>>1)];
                f[i+j]=f1+w*f2;
                f[i+j+(l>>1)]=f1-w*f2;
                w=w*wn;
            }
        }
    }
    if(!~rev)
        for(unsigned i=0;i<n;i++)
            f[i]=f[i]/n;
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
template<typename T>
inline T lcm(T m,T n){
    return m/gcd(m,n)*n;
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
