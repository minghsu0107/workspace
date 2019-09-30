#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
typedef struct MapPair {
    int key;
    char val[128];    // 最大長度為 127
} MapPair;
typedef struct Map {
    MapPair dat[1024];    // 記錄儲存的對應情況
    int sz;        // 非常重要的額外變數，記錄有多少元素
} Map;
void init(Map *map) {
    map->sz = 0;
}
int map(Map *map, const int key, const char *value) {
    for (int i = 0; i < map->sz; i++) {
        if (map->dat[i].key == key) {
            strcpy(map->dat[i].val, value);
            return 0;
        }
    }
    int n = map->sz;
    map->dat[n].key = key;
    strcpy(map->dat[n].val, value);
    map->sz++;
    return 1;
}
int numPairs(Map *map) {
    return map->sz;
}
static int intcmp(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}
static int paircmp(const void *a, const void *b) {
    return intcmp(&((*(MapPair**)a)->key), &((*(MapPair**)b)->key));
}
void print(Map *map) {
    static MapPair *A[1024];
    for (int i = 0; i < map->sz; i++)
        A[i] = &(map->dat[i]);
    qsort(A, map->sz, sizeof(MapPair*), paircmp);
    printf("----- map begin -----\n");
    for (int i = 0; i < map->sz; i++) {
        printf("%d %s\n", A[i]->key, A[i]->val);
    }
    printf("----- end       -----\n");
}
const char *getValue(Map *map, const int key) {
    for (int i = 0; i < map->sz; i++) {
        if (map->dat[i].key == key)
            return map->dat[i].val;
    }
    return NULL;
}
int unmap(Map *map, int key) {
    for (int i = 0; i < map->sz; i++) {
        if (map->dat[i].key == key) {
            for (int j = i+1; j < map->sz; j++)
                map->dat[j-1] = map->dat[j];
            map->sz--;
            return 1;
        }
    }
    return 0;
}
int reverseMap(Map *map, const char *value, int keys[]) {
    int n = 0;
    for (int i = 0; i < map->sz; i++) {
        if (!strcmp(map->dat[i].val, value))
            keys[n++] = map->dat[i].key;
    }
    qsort(keys, n, sizeof(int), intcmp);
    return n;
}
void test_all(Map *maps, int map_n) {
    for (int i = 0; i < map_n; i++)
        init(&maps[i]);
    int cmds, mid, cmd, key;
    char val[128];
    int keylist[1024];
    scanf("%d", &cmds);
    for (int i = 0; i < cmds; i++) {
        scanf("%d", &cmd);
        if (cmd == 1) {
            scanf("%d", &mid);
            print(&maps[mid]);
        } else if (cmd == 2) {    
            scanf("%d %d %s", &mid, &key, val);
            int f = map(&maps[mid], key, val);
            printf("mf %d\n", f);
        } else if (cmd == 3) {
            scanf("%d %d", &mid, &key);
            int f = unmap(&maps[mid], key);
            printf("uf %d\n", f);
        } else if (cmd == 4) {
            scanf("%d %s", &mid, val);
            int keylist_n = reverseMap(&maps[mid], val, keylist);
            assert(keylist_n <= 1024);
            printf("list ");
            for (int i = 0; i < keylist_n; i++)
                printf("%d%c", keylist[i], " \n"[i == keylist_n-1]);
        } else if (cmd == 5) {
            scanf("%d", &mid);
            int ret = numPairs(&maps[mid]);
            assert(ret <= 1024);
            printf("size %d\n", ret);
        } else {
            assert(false);
        }
    }
}
int main() {
    int spec;
    int map_n = 1;
    Map *maps = (Map *) malloc(sizeof(Map) * map_n);
    test_all(maps, map_n);
    free(maps);
    return 0;
}