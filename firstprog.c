// To use the printf or puts function requires functions from the standard library which are available in UNIX based systems
// Since C language only requires function prototypes before using the function (and not necessarily the complete function definition)
// The header files are provided in the location /usr/include/stdio.h which contains several other constants and function prototypes
// The GNU Compiler Collection, GCC, handles the linking of our compiled code with the shared libraries provided in UNIX
#include <stdio.h>

// We can study the internal states of the registers through the GNU Debugger, GDB: gdb -q ./a.out
// This assumes that the executable is named a.out, however, it can be named anything during compilation: gcc firstprog.c -o something.out/bin/<null> 
int main(){
  int i;
  for(i = 0; i < 10; i++){
    puts("Hello, world!");
  }
  return 0;
}