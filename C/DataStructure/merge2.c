#include "merge.h"
#include <stdlib.h>
#include <stdbool.h>
Node *merge(Node *list[], int K) {
    bool *flag = calloc(K, sizeof(bool));
    int n = 0, level = 1, remain = K;
#ifdef BOTTOMUP
    n = K - 1;
#endif
    bool first = true;
    Node *pre = NULL, *cur = list[n], *head = cur; 
    while (1) {
        if (remain == 1) {
           if (pre != NULL) pre->next = cur;
           break;
        }
        if (cur == NULL) {
            flag[n] = true;
            remain--;
        } else {
           if (first) {
                 head = cur;
                 first = false;
           }
           if (pre != NULL) pre->next = cur;
           list[n] = list[n]->next;
           pre = cur;
        }
        do {
#ifdef ZIGZAG
          if ((level) % 2) {
            n++;
            if (n == K)
              n = K - 1, (level)++;
          } else {
            n--;
            if (n < 0)
              n = 0, (level)++;
          }
#endif
#ifdef TOPDOWN 
          n = (n + 1) % K;
#endif
#ifdef BOTTOMUP
          n = (n - 1 + K) % K; 
#endif          
        } while (flag[n]);  
        cur = list[n];      
    }
    return head;
}
