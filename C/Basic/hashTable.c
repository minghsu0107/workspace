#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
char *hashTable[1000][10000];//at most 1000 buckets and each bucket has 10000 strings
int hashFunc(char *a, int length, int size)
{
    int key = 0;
    for (int i = 0; i < length; ++i)
    {
        if(isdigit(a[i]))
            key += a[i] - '0';
        else
            key += a[i];
    }
    return key % size;
}
 
int main(int argc, char const *argv[])
{
 
    char elements[10000][101];//at most 10000 strings
    int count[1000] = {0};//counter of bucket
 
    int S, N, Q;
    scanf("%d %d %d", &S, &N, &Q);
//build a hash table
    for(int i = 0; i < N; i++){
        scanf("%s", elements[i]);
        int length = strlen(elements[i]);
        elements[i][length] = '\0';
 
        int index = hashFunc(elements[i], length, S);//use hash function to get hash index
        hashTable[index][count[index]++] = elements[i];//store input string to hash table by index
        // since hashTable stores the pointer of strings, we should store all the input strings or we will lose them
    }
 //query
    for (int i = 0; i < Q; ++i)
    {
        char query[101];
        scanf("%s", query);
        int state = 0, index = hashFunc(query, strlen(query), S);//use hash function to get hash index
        for (int j = 0; j < count[index]; ++j)
        {  
            if(strcmp(hashTable[index][j], query) == 0){
                printf("%d\n", index);//if find out the query at that bucket then output bucket index
                state = 1;
                break;
            }
        }
        if(!state)//query is not exist in hash table
            printf("-1\n");//output -1
    }
 
    return 0;
}
