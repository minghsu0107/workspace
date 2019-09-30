#define MAXN 1000005
int parent[MAXN];//每個點紀錄其父母節點
int size[MAXN];//每個點紀錄以它為根的子樹的大小
void MAKE_SET(int x){
    parent[x]=x;
    size[x]=1;
}
void init(int n){
    for(int i=0;i<n;++i){
        MAKE_SET(i);
    }
}
bool UNION(int x,int y){
    x=FIND_SET(x);
    y=FIND_SET(y);
    if(x==y)return false;
    if(size[x]<size[y]){
        std::swap(x,y);
    }
    parent[y]=x;
    size[x]+=size[y];
    return true;
}
int FIND_SET(int x){
    if(parent[x]==x)return x;
    parent[x]=FIND_SET(parent[x]);
    return parent[x];
}