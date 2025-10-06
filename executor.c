#include "executor.h"

/**
 * Execute a command using the fork-exec-wait pattern
 *
 * This function demonstrates the fundamental process management pattern
 * used by all Unix shells:
 * 1. Fork a child process
 * 2. Child calls exec to transform into the target command
 * 3. Parent waits for child to complete
 *
 * @param command The command to execute (e.g., "ls", "pwd", "echo")
 * @param args Array of arguments: [command, arg1, arg2, ..., NULL]
 *             Example: {"ls", "-l", NULL} or {"echo", "Hello", NULL}
 * @return Exit status of the command (0=success, non-zero=failure, -1=error)
 */
int execute_command(char *command, char **args) {
    pid_t pid;
    int status;

    // TODO 1: Fork a child process
    pid = fork(); 
    if (pid < 0) { 
    	perror("fork"); 
    	return -1; 
    }
    // TODO 2: Child process - Execute the command
    if (pid == 0) { 
    	execvp(command, args);
    	perror("execvp");
    	_exit(1);
    }
    
    // TODO 3: Parent process - Wait for child to complete
    status = 0;
    if (waitpid(pid, &status, 0) < 0) { 
    	perror("waitpid");
    	return -1;
    }
    if (WIFEXITED(status)) { 
    	return WEXITSTATUS(status);
    }
    return -1; 
    }
    
    

  
