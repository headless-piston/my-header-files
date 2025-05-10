//some templates
#ifndef MY_ALGORITHM
#define MY_ALGORITHM
#include<cmath>
const double PI=4*atan(1);
template<typename T>
T Max(const T &a,const T &b){
    return a<b?b:a;
}
template<typename T>
T Min(const T &a,const T &b){
    return a<b?a:b;
}
template<typename T>
void Swap(T &a,T &b){
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
typedef long long ll;
typedef unsigned long long ull;
#endif