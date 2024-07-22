#include <stdio.h>
#include <stdlib.h>

#define TAPE_SIZE 30000
#define ARG_MAX 2097152 

char* get_input() {
  static char command_buffer[ARG_MAX];
  fgets(command_buffer, ARG_MAX, stdin);
  return command_buffer;
}

int* interpret_code(char* code) {
  char* data_tape = (char*)malloc(TAPE_SIZE * sizeof(char));
  int data_pointer = 0;
  char* code_ptr = code;
  char* loop_start = NULL;

  while (*code_ptr) {
    switch (*code_ptr) {
      case '>':
        if (data_pointer < TAPE_SIZE - 1) {
          data_pointer++;
        }
        break;
      case '<':
        if (data_pointer > 0) {
          data_pointer--;
        }
        break;
      case '+':
        data_tape[data_pointer]++;
        break;
      case '-':
        data_tape[data_pointer]--;
        break;
      case '[':
        if (data_tape[data_pointer] == 0) {
          int open_brackets = 1;
          while (open_brackets > 0) {
            code_ptr++;
            if (*code_ptr == '[') open_brackets++;
            if (*code_ptr == ']') open_brackets--;
          }
        } else {
          loop_start = code_ptr;
        }
        break;
      case ']':
        if (data_tape[data_pointer] != 0) {
          code_ptr = loop_start;
        }
        break;
        }
        code_ptr++;
    }

  return data_tape; 
}

void run_shell(char* data_tape) {
  system(data_tape);
  free(data_tape);
}

int main() {
  while (1) {
    char command_buffer[ARG_MAX] = get_input();
    char* data_tape = interpret_code(command_buffer);
    run_shell(data_tape);
  }
  return 0;
}
