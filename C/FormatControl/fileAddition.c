#include <stdio.h>
 
int main(){
  char input1[32], input2[32], output[32];
  scanf("%s %s %s", input1, input2, output);
  FILE *pInput1 = fopen(input1, "rb");
  FILE *pInput2 = fopen(input2, "rb");
  FILE *pOutput = fopen(output, "wb");
  fseek(pInput1, 0, SEEK_END);
  fseek(pInput2, 0, SEEK_END);
  long size1 = ftell(pInput1);
  long size2 = ftell(pInput2);
  if( size1 < size2 ){
    long tmp = size1;
    size1 = size2;
    size2 = tmp;
    FILE *ptr = pInput1;
    pInput1 = pInput2;
    pInput2 = ptr;
  }
  int carry = 0, sum;
  for( int i = 0 ; i < size1 ; ++i ){
      unsigned char c1, c2;
      fseek(pInput1, size1 - i - 1, SEEK_SET);
      fread(&c1, sizeof(unsigned char), 1, pInput1);
      if( i < size2 ){
        fseek(pInput2, size2 - i - 1, SEEK_SET);
        fread(&c2, sizeof(unsigned char), 1, pInput2);
      }
      else
        c2 = 0;
      sum = carry + c1 + c2;
      if( sum > 255 )
        carry = 1;
      else
        carry = 0;
      fseek(pOutput, size1 - i - 1, SEEK_SET);
      fwrite(&sum, sizeof(unsigned char), 1, pOutput);
  }
  fclose(pInput1);
  fclose(pInput2);
  fclose(pOutput);
  return 0;
}