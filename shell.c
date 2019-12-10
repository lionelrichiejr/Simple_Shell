#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "shell > ";
char delimiters[] = " \t\r\n";
char **environ;
//Added code begins here
char *token;
pid_t ret_val;

void  ChildProcess(void);
void  ParentProcess(void);


int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];

    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    
    while (true) {
        // Print the shell prompt.
        printf("%s", prompt);
        fflush(stdout);
        
        // Read input from stdin and store it in command_line. If there's an
        // error, exit immediately. (If you want to learn more about this line,
        // you can Google "man fgets")
        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "fgets error");
            exit(0);
        }
        
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }
        
        //Added code begins here
        // Tokenize the command line input (split it on whitespace)
        token = strtok(command_line, delimiters);
      
        //Create a child process which will execute the command line input'
        //The parent process should wait for the child to complete
        ret_val = fork();
        if (ret_val == 0) 
          ChildProcess();
        else
          ParentProcess();
      
        // man fork
        // man execve
        // man wait
        // man strtok
    }
    
    // This should never be reached.
    return -1;
}

void ChildProcess(void) {
  execve(token);
  return;
}

void ParentProcess(void) {
  wait();
  return;
}
