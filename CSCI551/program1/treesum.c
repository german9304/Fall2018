
#include <stdio.h>
#define PROCESSORS 8

int main(int argc, const char * argv[]) {
  int divide = 2;
  int coredifference = 1;
  int dif = 0;
  int res = coredifference;
  for(int i = 0;divide <= PROCESSORS;i++){
    printf("timestamp: %d\n",i);
    for(int in = 0;in< PROCESSORS/divide; in++){
      printf("%d %d\n",dif,res);
      dif+=divide;
      res = dif + coredifference;
    }
    dif = 0;
    res = coredifference*=2;
    divide*=2;
  }
  return 0;
}
