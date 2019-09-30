#include <stdio.h>
#include <assert.h>
// Union是一種將不同data types儲存在同一個記憶體空間的特殊自訂型別，union一次只會儲存一個變數資料
// 所有在union宣告的變數會共享同一個記憶體空間，而且以宣告的變數型態size最大的變數空間作為記憶體空間
struct T0 {
  int i;
};
struct T1 {
  char c[4];
};
typedef struct Inst {
  int type;
  union {
    struct T0 t0;
    struct T1 t1;
  } para;
} Inst;
int main() {
  char s[16];
  assert(scanf("%s", s) == 1);
  FILE *fin = fopen(s, "rb");
  assert(fin != NULL);
  
  for (Inst cmd;;) {
    int stat = fread(&cmd, sizeof(Inst), 1, fin);
    if (stat != 1)
      break;
    switch (cmd.type) {
      case 0: 
        printf("%d", cmd.para.t0.i);
        break;
      case 1:
        putchar(cmd.para.t1.c[0]);
        putchar(cmd.para.t1.c[1]);
        putchar(cmd.para.t1.c[2]);
        putchar(cmd.para.t1.c[3]);
        break;
      case 2:
        {
          char c;
          while (fread(&c, sizeof(char), 1, fin) && c) {
            putchar(c);
          }
        }
        break;
      case 3:
        // If the type is 3
        // use the position of the first byte of this instruction as a base 
        // and the parameter (as an integer) as an offset, to seek within the file 
        fseek(fin, cmd.para.t0.i-sizeof(Inst), SEEK_CUR); 
        // -sizeof(Inst) to go back to first byte
        break;
      case 4:
        fseek(fin, cmd.para.t0.i, SEEK_SET);
        break;
      case 5:
        fseek(fin, cmd.para.t0.i, SEEK_END);
        break;
      default:
        printf("Seek end");
        return 0;
    }
  }
  printf("Seek end");
  return 0;
}

