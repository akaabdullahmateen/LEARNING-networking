// To use the printf or puts function requires functions from the standard library which are available in UNIX based systems
// Since C language only requires function prototypes before using the function (and not necessarily the complete function definition)
// The header files are provided in the location /usr/include/stdio.h which contains several other constants and function prototypes
// The GNU Compiler Collection, GCC, handles the linking of our compiled code with the shared libraries provided in UNIX

#include <stdio.h>

// We can study the internal states of the registers through the GNU Debugger, GDB: gdb -q ./a.out
// This assumes that the executable is named a.out, however, it can be named anything during compilation: gcc firstprog.c -o something.out/bin/<null>
// Also note that the -q flag is optional, and is used to prevent GDB from printing version string and other irrelevant information

int main(){
  int i;
  for(i = 0; i < 10; i++){
    puts("Hello, world!");
  }
  return 0;
}

// The disassembly of the main function:
//
// 1) endbr64 
// 2) push rbp
// 3) mov  rbp, rsp
// 4) sub  rsp, 0x10
// These four lines are function prologue that sets the system up for running the program on modern x86-64 architecture
//
// 1) endbr64
// Protects against Return-oriented Programming and Jump/Call-oriented Programming attacks by creating a shadow stack for tracking return addresses
//
// 2) push rbp
// Register rbp is the frame pointer, and contains the previous stack frame
// This operation pushes the value stored in the rbp register on stack, so rbp can return to its initial value after program execution
//
// 3) mov rbp, rsp
// Moves the address of current stack frame from rsp into rbp
// This allows rbp to point to the top of the stack (highest memory address for the current frame since Linux uses System V ABI)
//
// 4) sub rsp. $0x10
// Linux uses System V ABI for x86-64 (AMD64), the stack grows down, i.e., smaller addresses are higher up the stack
// The amount of memory reserved for local variables is always a multiple of 16 bytes, to keep the stack aligned to 16 bytes
// If no stack space is needed for local variables, this operation is not performed, and not included in the produced disassembly
// While rbp points to the current stack frame, rsp points to the top of the stack
// Because compiler knows the difference between rbp and rsp, it is free to use either one as the base for local variables
// This operation grows the stack by 16 bytes to reserve space for local variables
//
// 5) mov DWORD PTR [rbp - 0x4], 0x0
// Reserve one integer width space (int has 4 byte size in C), and initialize it with the value 0
// Thus, the top of stack (for the current stack frame) contains the value 0, representing the iterator 'i' in the for loop
//
// 6) jmp 0x55555555516e <main+37>
// 7) cmp DWORD PTR [rbp - 0x4], 0x9 # 0x55555555516e <main+37>
// At the start of for loop, the program jumps immediately to the compare condition to make sure that the loop runs only if the condition is met
// Even at the start of the program. This prevents the loop from running in case the condition was never met
//
// 8) jle 0x55555555515e <main+21>
// 9) lea rdi,[rip + 0xe9f] # 0x555555556004 <main+21>
// 11) call 0x555555555050 <puts@plt>
// If the condition: i < 10; equivalent to: i <= 9 is met, the program jumps to the code where it prepares for calling the printf/puts function
// Loading the effective address 0x555555556004 into rdi, makes rdi point to the memory address where our string: "Hello, World!" was written
// Therfore, when the printf/puts function is called, they can grab the string to output to stdout by grabbing characters pointed to by rdi
// Note to remember is that each C string is terminated when the null ASCII character 0x00 is encountered
//
// 11) add DWORD PTR [rbp - 0x4], 0x1
// Add 1 to the iterator 'i'. After this operation, the compare follows, thus, the loop runs again if the condition still meets.
// Once, the incremented iterator has a value '10', the condition is not met, thus, the loop ends, and the function epilogue follows
//
// 12) leave
// 13) ret
// This is the function epilogue, whereby, the programs to exit the called function
// mov rsp, rbp \
//               | equivalent to 'leave' instruction
// popq rbp     /
