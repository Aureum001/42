/* 
 * ft_popen - Step by step explanation
 * 
 * GOAL: Create a function that launches a process and connects to its input/output
 * 
 * KEY CONCEPTS:
 * 1. PIPE: Creates two connected file descriptors
 *    - fd[0] = read end
 *    - fd[1] = write end
 *    - What you write to fd[1], you can read from fd[0]
 * 
 * 2. FORK: Creates a child process
 *    - Returns 0 in child process
 *    - Returns child's PID in parent process
 * 
 * 3. DUP2: Duplicates a file descriptor
 *    - dup2(oldfd, newfd) makes newfd point to same place as oldfd
 * 
 * 4. EXECVP: Replaces current process with a new program
 *    - Never returns on success (process is replaced!)
 */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

/* STEP 1: Understand what we're building
 * 
 * A PIPE has TWO ends and connects TWO processes!
 * Think of it like a literal pipe: water flows from one end to the other.
 * 
 * Type 'r' (read from command output):
 *   [Child WRITES] → fd[1] (write end) → [pipe] → fd[0] (read end) → [Parent READS]
 *   - Child uses WRITE end because command outputs data
 *   - Parent uses READ end to receive that data
 *   - Parent gets fd to READ the command's output
 * 
 * Type 'w' (write to command input):
 *   [Parent WRITES] → fd[1] (write end) → [pipe] → fd[0] (read end) → [Child READS]
 *   - Parent uses WRITE end to send data
 *   - Child uses READ end because command needs input
 *   - Parent gets fd to WRITE to the command's input
 * 
 * KEY INSIGHT: The 'type' describes what the PARENT does, but the child does the OPPOSITE!
 *   - If parent READs ('r'), child must WRITE
 *   - If parent WRITEs ('w'), child must READ
 */

int ft_popen(const char *file, char *const argv[], char type)
{
	int fd[2];      // fd[0] = read end, fd[1] = write end
	pid_t pid;

	/* STEP 2: Validate parameters */
	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	
	/* STEP 3: Create the pipe
	 * This creates two file descriptors that are connected:
	 * - Anything written to fd[1] can be read from fd[0]
	 */
	if (pipe(fd) == -1)
		return (-1);

	/* STEP 4: Fork the process
	 * After fork(), we have TWO processes running the same code:
	 * - Child process: pid == 0
	 * - Parent process: pid == child's process ID
	 */
	pid = fork();
	if (pid == -1)
	{
		// Fork failed - clean up and return error
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}

	/* STEP 5a: CHILD PROCESS (pid == 0) */
	if (!pid)
	{
		/* Child will execute the command.
		 * We need to redirect stdin or stdout to the pipe.
		 */
		
		if (type == 'r')
		{
			/* Type 'r': Parent wants to READ the command's output
			 * 
			 * Commands like 'ls', 'cat', etc. write their output to stdout by default.
			 * We redirect the command's stdout to the pipe's write end to capture it.
			 * So: command writes to stdout → fd[1] (pipe write) → fd[0] (pipe read) → parent reads
			 * 
			 * STDOUT_FILENO (1) now points to fd[1]
			 */
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit(1);
		}
		else  // type == 'w'
		{
			/* Type 'w': Parent wants to WRITE to the command's input
			 * 
			 * We need to redirect the command's stdin to the pipe's read end
			 * So: parent → fd[1] (pipe write) → fd[0] (pipe read) → command input
			 * 
			 * STDIN_FILENO (0) now points to fd[0]
			 */
			if (dup2(fd[0], STDIN_FILENO) == -1)
				exit(1);
		}
		
		/* IMPORTANT: Close both pipe ends in child!
		 * After dup2, stdin/stdout already point to the pipe.
		 * We don't need the original fd[0] and fd[1] anymore.
		 * If we don't close them, we leak file descriptors!
		 */
		close(fd[0]);
		close(fd[1]);
		
		/* Execute the command - this REPLACES the child process
		 * If execvp succeeds, this code never continues!
		 * If it fails (command not found, etc.), we exit with error.
		 */
		execvp(file, argv);
		exit(1);  // Only reached if execvp fails
	}
	
	/* STEP 5b: PARENT PROCESS (pid > 0) */
	else
	{
		/* Parent needs to return the correct end of the pipe
		 * and close the end it won't use.
		 * 
		 * WHY RETURN THE FD?
		 * The whole point of ft_popen is to give the caller a way to 
		 * communicate with the child process!
		 * 
		 * - If type 'r': caller can read(fd, ...) to get command output
		 * - If type 'w': caller can write(fd, ...) to send data to command
		 * 
		 * Example after calling ft_popen:
		 *   int fd = ft_popen("ls", {"ls", NULL}, 'r');
		 *   char buf[1024];
		 *   read(fd, buf, 1024);  // ← This reads the 'ls' output!
		 */
		
		if (type == 'r')
		{
			/* Type 'r': Parent wants to READ from the command
			 * 
			 * - Close write end (child is writing, parent is reading)
			 * - Return read end to parent
			 */
			close(fd[1]);
			return (fd[0]);
		}
		else  // type == 'w'
		{
			/* Type 'w': Parent wants to WRITE to the command
			 * 
			 * - Close read end (child is reading, parent is writing)
			 * - Return write end to parent
			 */
			close(fd[0]);
			return (fd[1]);
		}
	}
}

/* 
 * EXAMPLE USAGE:
 * 
 * // Type 'r' - Read from command output
 * int fd = ft_popen("ls", (char *const []){"ls", "-l", NULL}, 'r');
 * // Now you can read(fd, buffer, size) to get the ls output
 * 
 * // Type 'w' - Write to command input
 * int fd = ft_popen("grep", (char *const []){"grep", "pattern", NULL}, 'w');
 * // Now you can write(fd, data, size) to send input to grep
 * 
 * IMPORTANT - CHOOSING THE RIGHT MODE:
 * - Use 'r' for commands that OUTPUT data: ls, cat file.txt, echo, etc.
 * - Use 'w' for commands that READ stdin: grep, wc, sort, cat (no args), etc.
 * 
 * DON'T DO THIS - it makes no sense!
 *   ft_popen("ls", {"ls", NULL}, 'w');  // ❌ ls doesn't read stdin!
 *   ft_popen("grep", {"grep", "word", NULL}, 'r');  // ❌ grep needs input!
 * 
 * MEMORY/FD MANAGEMENT:
 * - Each unused pipe end MUST be closed to avoid fd leaks
 * - Child closes both fd[0] and fd[1] after dup2 (they're duplicated to stdin/stdout)
 * - Parent closes the pipe end it doesn't use
 */

/*
 * CONCRETE EXAMPLE: Let's trace what happens step by step
 * 
 * int fd = ft_popen("ls", (char *const []){"ls", "-la", NULL}, 'r');
 * 
 * WHAT EXECVP RECEIVES:
 * - file = "ls"                           (the program to execute)
 * - argv = {"ls", "-la", NULL}            (array of arguments)
 *   argv[0] = "ls"      (program name, by convention)
 *   argv[1] = "-la"     (first argument)
 *   argv[2] = NULL      (marks end of array, REQUIRED!)
 * 
 * EXECUTION FLOW:
 * 
 * 1. pipe(fd) creates:
 *    fd[0] = 3 (read end)
 *    fd[1] = 4 (write end)
 * 
 * 2. fork() creates two processes:
 *    Parent: pid = 12345 (child's process ID)
 *    Child:  pid = 0
 * 
 * 3. CHILD PROCESS (pid = 0):
 *    - dup2(fd[1], STDOUT_FILENO) → stdout now points to fd 4 (pipe write end)
 *    - close(fd[0]) and close(fd[1]) → original pipe fds closed
 *    - execvp("ls", {"ls", "-la", NULL}) → child becomes 'ls -la' process
 *    - 'ls' program runs and writes output to stdout (which is the pipe!)
 * 
 * 4. PARENT PROCESS (pid = 12345):
 *    - close(fd[1]) → closes write end (not needed)
 *    - return fd[0] → returns fd 3 (read end)
 * 
 * 5. Now in main:
 *    char buffer[1024];
 *    read(fd, buffer, 1024);  // Reads 'ls -la' output from the pipe!
 * 
 * WHY ARGV[0] IS THE PROGRAM NAME:
 * This is a Unix convention. When you run a program, argv[0] is traditionally
 * the name of the program itself. The actual arguments start at argv[1].
 * This allows programs to know how they were invoked (useful for programs
 * with different behaviors based on their name).
 */

