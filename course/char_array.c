#include <stdio.h>

int main(){
  char str_a[20];
  
  str_a[0] = 'H';
  str_a[1] = 'e';
  str_a[2] = 'l';
  str_a[3] = 'l';
  str_a[4] = 'o';
  str_a[5] = ',';
  str_a[6] = ' ';
  str_a[7] = 'w';
  str_a[8] = 'o';
  str_a[9] = 'r';
  str_a[10] = 'l';
  str_a[11] = 'd';
  str_a[12] = '!';
  str_a[13] = '\n';

  // The character 0 is called null byte, that hints printf that any remaining bytes are not relevant to the current string
  // Marking the termination of string through 0 prevents the printf from printing any more garbage bytes from our 20 char long array

  str_a[14] = 0;
  
  // Using str_a directly as a parameter to printf will raise warning: format not a string literal and no format arguments
  // This is because variable strings referenced through char arrays are common attack vector, therefore, not recommended

  printf("%s", str_a);
  return 0;
}