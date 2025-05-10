//some templates
#ifndef MY_ALGORITHM
#define MY_ALGORITHM
template<typename T>
T Max(const T &a,const T &b){
    return a<b?b:a;
}
template<typename T>
T Min(const T &a,const T &b){
    return a<b?a:b;
}
template<typename T>
void Swap(const T &a,const T &b){
    T c=a;
    a=b;
    b=c;
    return;
}
typedef long long ll;
typedef unsigned long long ull;
#endif