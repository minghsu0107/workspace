// top-down (array method)
#include<iostream>   
#include<string.h> 
using namespace std;   
  
#define MAXN 100   
#define MAXIND 405 //线段树节点个数   
  
//构建线段树,目的:得到M数组.   
void initialize(int node, int b, int e, int M[], int A[]) {   
    if (b == e)   
        M[node] = b; //只有一个元素,只有一个下标   
    else  {   
        //递归实现左孩子和右孩子   
        initialize(node<<1, b, (b + e) / 2, M, A);   
        initialize(node<<1 | 1, (b + e) / 2 + 1, e, M, A);   
        //search for the minimum value in the first and   
        //second half of the interval   
        if (A[M[node<<1]] <= A[M[node<<1 | 1]])   
            M[node] = M[node<<1];   
        else  
            M[node] = M[node<<1 | 1];   
    }   
} 

// A[x] = y  
void update(int node, int b, int e, int M[], int A[], int x, int y) {
    if (b == e) {
        A[x] = y;
        M[node] = x;
        return;
    }
    int mid = (b + e) >> 1;
    if(x <= mid) update(node<<1, b, mid, M, A, x, y);
    else update((node<<1) + 1, mid + 1, e, M, A, x, y);
    if (A[M[node<<1]] <= A[M[node<<1 | 1]])   
        M[node] = M[node<<1];   
    else  
        M[node] = M[node<<1 | 1]; 
}
//找出区间 [i, j] 上的最小值的索引   
int query(int node, int b, int e, int M[], int A[], int i, int j) {   
    //查询区间和要求的区间没有交集   
    if (i > e || j < b)   
        return -1;   
  
    //if the current interval is included in   
    //the query interval return M[node]   
    if (i <= b && j >= e)   
        return M[node];   
  
    //compute the minimum position in the   
    //left and right part of the interval 
    int mid = b + (e - b) / 2; 
    
    
    int p1 = query(node<<1, b, mid, M, A, i, j);
    int p2 = query(node<<1 | 1, mid + 1, e, M, A, i, j); 

    if (p1 == -1) return p2;
    if (p2 == -1) return p1;
    if (A[p1] <= A[p2]) return p1;
    return p2;
} 
int query2(int node, int b, int e, int M[], int A[], int i, int j) {    
    if (i <= b && j >= e)   
        return M[node];   

    int mid = (b + e) >> 1; 
    
    if (j <= mid)
        return query(node<<1, b, mid, M, A, i, j);
    if (i > mid)
        return query(node<<1 | 1, mid + 1, e, M, A, i, j);

    int p1 = query(node<<1, b, mid, M, A, i, mid);
    int p2 = query(node<<1 | 1, mid + 1, e, M, A, mid + 1, j); 
    if (A[p1] <= A[p2]) return p1;
    return p2;
}  
int query3(int node, int b, int e, int M[], int A[], int i, int j) {     
    if (i <= b && j >= e)   
        return M[node];   
  
    int mid = b + (e - b) / 2; 
    
    int p1, p2;
    p1 = p2 = -1;
    if (i <= mid)
        p1 = query(node<<1, b, mid, M, A, i, j);
    if (j > mid)
        p2 = query(node<<1 | 1, mid + 1, e, M, A, i, j); 

    if (p1 == -1) return p2;
    if (p2 == -1) return p1;
    if (A[p1] <= A[p2]) return p1;
    return p2;
}  
int main() {   
    int M[MAXIND]; //下标1起才有意义,保存下标编号节点对应区间最小值的下标.   
    memset(M,-1,sizeof(M));   
    int a[] = {5, 4, 7, 9, 1, 4, 3, 2, 5, 4, 3, 2, 8, 6, 7};   
    initialize(1, 0, sizeof(a) / sizeof(a[0]) - 1, M, a);
    // return the index of the min in the range (starts from 0)   
    cout << query(1, 0, sizeof(a) / sizeof(a[0]) - 1, M, a, 3, 7) << endl;
    cout << query2(1, 0, sizeof(a) / sizeof(a[0]) - 1, M, a, 3, 7) << endl; 
    cout << query3(1, 0, sizeof(a) / sizeof(a[0]) - 1, M, a, 3, 7) << endl;
    update(1, 0, sizeof(a) / sizeof(a[0]) - 1, M, a, 6, 0);
    cout << query(1, 0, sizeof(a) / sizeof(a[0]) - 1, M, a, 3, 7) << endl;
    cout << query2(1, 0, sizeof(a) / sizeof(a[0]) - 1, M, a, 3, 7) << endl; 
    cout << query3(1, 0, sizeof(a) / sizeof(a[0]) - 1, M, a, 3, 7) << endl; 
    return 0;   
}  
/*
线段树能在对数时间内在数组区间上进行更新与查询。
定义线段树在区间[i, j] 上如下：
第一个节点维护着区间 [i, j] 的信息。
if i<j , 那么左孩子维护着区间[i, (i+j)/2] 的信息，
右孩子维护着区间[(i+j)/2+1, j] 的信息。

n is the length of the array
the segment tree has (2n-1) nodes if n是2的幂 (N = 2n-1)
可知 N 个元素的线段树的高度h = [logN] = log(2n-1+1)-1
= log(2n) - 1(只有根节点的树高度为0)

线段树和堆有一样的结构, 因此如果一个节点编号为 x，
那么左孩子编号为2*x  右孩子编号为2*x+1.

使用线段树解决RMQ问题，关键维护一个数组M[num]，num=2^(线段树高度+1).
(number of segment tree nodes = 2^0 + 2^1 + 2^2 + 2^3 + ... + 2^h 
= 2^(h+1) - 1
but the index of the nodes starts from 1,
so we need (2^(h+1) - 1 + 1 = 2^(h+1) = 2n array spaces)

if n不是2的幂(不是满二叉树) then 我们找到比n大的最小的2的幂k
so we neek 2k array spaces at least
however, in worst case, k is almost equals to 2n
so we need at least 2*2n = 4n array spaces

M[i]:维护着被分配给该节点(编号=i)的区间的最小值元素的下标。(线段树根节点编号=1)
该数组初始状态为-1.

build: O(n)
query: O(logn)
*/