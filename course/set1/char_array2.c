#include <stdio.h>
#include <string.h>

int main(){
  char str_a[20];

  // Since manually typing each character into char array is cumbersome, strcpy function can be utilized to accomplish just that
  // It iterates over each character in the source string, and copies these byte-sized char into corresponding place in the destination array/ptr
  // It stops on encountering the null byte '0'

  strcpy(str_a, "Hello, World!\n");
  printf("%s", str_a);
  return 0;
}