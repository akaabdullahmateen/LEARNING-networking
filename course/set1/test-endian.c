#include <stdio.h>

// Get the pointer to the variable: n
// Convert it to a char pointer
// Get the value referenced by this char pointer
// If the value achieved is the same value as the one initialized to the variable 'n'
// We conclude that the system architecture is little-endian

// If the system is little-endian, the integer (4 byte size) will be stored in memory as:
// ---------------------
// | 01 | 00 | 00 | 00 |
// ---------------------
// The memory address will point to the first byte of this 4-byte word
// Since, C char is only one byte, the value of the char pointer (achieved by *(char *)) will reference the value: 01
// ------
// | 01 |
// ------
// A logical AND of this value ('01' in case of little-endian, and '00' in case of big-endian)
// With the value itself (this works because regardless of endiness, processors perform the calculations in the correct way)
// Will result in '1' in case of little-endian, and '0' in case of big-endian

int main(){
  int n = 1;
  if(*(char *)&n==1){
    printf("Little endian\n");
  }
  else{
    printf("Big endian\n");
  }
  return 0;
}