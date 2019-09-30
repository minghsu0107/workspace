#include<stdio.h>
#include<string.h> // for memcpy and memmove
#define MAXSIZE 1048576

//移動array 中的element 時，若一次只移動一個element，將因為運算量太多造成TLE。
//正確的作法為一次將移動(T/64)modN 個element，並且需要一塊額外記憶體儲存這些element:
//此額外記憶體因為容量過大，若直接宣告在function 內將造成RE，合適的作法為宣告在global 或者在function 內宣告為static。
//可以使用<string.h> 中的memcpy 及memmove function 一次移動整塊記憶體記憶體內容。

void shiftWord(long long belt[],int N,int nWord){
    static long long buffer[MAXSIZE];
    memcpy(buffer,belt,sizeof(long long)*nWord);
    memmove(belt,belt+nWord,sizeof(long long)*(N-nWord));
    memcpy(belt+N-nWord,buffer,sizeof(long long)*nWord);
}
void shiftOffset(long long belt[],int N,int nOffset){
    if(nOffset==0)
        return;
    long long shiftLeft=(long long)nOffset;
    long long shiftRight=64LL-shiftLeft; // 64LL makes compiler consider constant 64 as a long long value
    long long leftmost=(unsigned long long)belt[0]>>shiftRight;
    for(int i=0;i<N-1;i++){
        belt[i]<<=shiftLeft;
        belt[i]|=(unsigned long long)belt[i+1]>>shiftRight; // cast 成 unsigned long long 避免對負數作right shift operation
    }                                                       // since elements in array belt may be negative
    belt[N-1]<<=shiftLeft;
    belt[N-1]|=leftmost;
}
// 若T為64的倍數則只需要移動整數陣列元素而不需移動位元 且每移N個元素即循環回原位置
void transmission(long long belt[],int N,int T){
    shiftWord(belt,N,(T>>6)%N); // (T/64)%N
    shiftOffset(belt,N,T&63); // T&63 equivalent to T%64, since 63 == 00000000 00000000 00000000 11111111
}
long long int belt[MAXSIZE];
int main(){
    int N,T;
    scanf("%d%d",&N,&T);
    for(int i=0;i<N;i++)
        scanf("%lld",&belt[i]);
    transmission(belt,N,T);
    for(int i=0;i<N;i++)
        printf("%lld%s",belt[i],i==N-1?"":" ");
    return 0;
}