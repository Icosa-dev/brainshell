#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAPE_SIZE 30000
#define ARG_MAX 2097152 

// check if a character is a brainfuck keychar (note that '.' and ',' arn't used in brainshell)
int is_brainfuck_char(char c) {
  return c == '>' || c == '<' || c == '+' || c == '-' || c == '[' || c == ']';
}

// reads a file and removes non-brainfuck characters
char* read_file(char* filepath) {
  FILE* file;
  static char command_buffer[ARG_MAX];

  // open file
  file = fopen(filepath, "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(1);
  }

  // read file
  size_t read_size = fread(command_buffer, 1, ARG_MAX - 1, file);
  if (read_size == 0 && ferror(file)) {
    perror("Error reading file");
    fclose(file);
    exit(1);
  }
  fclose(file);

  // null-terminate the buffer
  command_buffer[read_size] = '\0';

  // filter out non-brainfuck characters
  char* filtered_buffer = command_buffer;
  char* filtered_ptr = command_buffer;
  while (*filtered_buffer) {
    if (is_brainfuck_char(*filtered_buffer)) {
      *filtered_ptr++ = *filtered_buffer;
    }
    filtered_buffer++;
  }
  *filtered_ptr = '\0';

  return command_buffer;
}

char* get_input() {
  static char command_buffer[ARG_MAX];
  if (fgets(command_buffer, ARG_MAX, stdin) == NULL) {
    perror("fgets");
    exit(1);
  }

  // remove extra newline character
  size_t len = strlen(command_buffer);
  if (len > 0 && command_buffer[len - 1] == '\n') {
    command_buffer[len - 1] = '\0';
  }
  return command_buffer;
}

char* interpret_code(char* code) {
  static char data_tape[TAPE_SIZE] = {0};
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
      default:
        break;
      }
      code_ptr++;
    }
  
  // make sure the tape is null terminated
  static char result[TAPE_SIZE + 1];
  memcpy(result, data_tape, TAPE_SIZE);
  result[TAPE_SIZE] = '\0';
  return data_tape; 
}

void run_shell(char* data_tape) {
  if (strlen(data_tape) > ARG_MAX) {
    fprintf(stderr, "Command too long\n");
    return;
  }
  system(data_tape);
}

int main(int argc, char** argv) {
  if (argc < 2) {
    while (1) {
      char* command_buffer = get_input();
      char* data_tape = interpret_code(command_buffer);
      run_shell(data_tape);
    }
  }
  
  // if there is an argument passed then use it as a filepath
  char* command_buffer = read_file(argv[1]);
  char* data_tape = interpret_code(command_buffer);
  run_shell(data_tape);

  return 0;
}
