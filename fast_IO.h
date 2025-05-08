//fast_IO
//Valid only for integers,supports negative integers
#ifndef FAST_IO
#define FAST_IO
#include<cstdio>
template<typename T>
void read(T &x){
    bool f=0;
    x=0;
    char ch=getchar();//in Linux,getchar()=>getchar_unlocked() is faster
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    if(f)
        x=~x+1;
    return;
}
template<typename T,typename...Args>
void read(T &x,Args &...args){
    read(x);
    read(args...);
    return;
}
template<typename T>
void write(T x){
    if(x<0){
        x=~x+1;
        putchar('-');//putchar()=>putchar_unlocked()
    }
    if(x<10)
        putchar(x+48);
    else{
        write(x/10);
        putchar(x%10+48);
    }
    return;
}
#endif