/*
 * picoshell - Step by step explanation
 * 
 * GOAL: Execute a pipeline of commands (like shell's cmd1 | cmd2 | cmd3)
 * 
 * KEY CONCEPTS:
 * 1. PIPELINE: Chain of commands where each output feeds the next input
 *    Example: ls | grep file | wc -l
 *    - 'ls' output → 'grep' input
 *    - 'grep' output → 'wc' input
 * 
 * 2. Multiple PIPES: One pipe between each pair of commands
 *    For 3 commands: [cmd1] --pipe1-- [cmd2] --pipe2-- [cmd3]
 * 
 * 3. TRACKING: Need to remember previous pipe's read end for next command
 */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/* STEP 1: Understand the input format
 * 
 * cmds is an array of command arrays (char **cmds[])
 * 
 * Example: ls | grep file
 * 
 * cmds[0] = {"ls", NULL}
 * cmds[1] = {"grep", "file", NULL}
 * cmds[2] = NULL  (marks end of commands)
 * 
 * Each cmds[i] is ready for execvp(cmds[i][0], cmds[i])
 */

/* STEP 2: Understand the pipeline structure
 * 
 * For: cmd1 | cmd2 | cmd3
 * 
 * Visual representation:
 * 
 *   [cmd1] --stdout--> [pipe1] --stdin--> [cmd2] --stdout--> [pipe2] --stdin--> [cmd3]
 *    child0    writes   fd[0,1]    reads    child1   writes   fd[0,1]    reads    child2
 * 
 * Each command runs in its own child process
 * Pipes connect stdout of one to stdin of the next
 * 
 * UNDERSTANDING PIPE ENDS:
 * 
 * Think of a pipe like a tube:
 * 
 * [WRITE END - fd[1]] ===pipe=== [READ END - fd[0]]
 *    ↑ PUT DATA IN                  ↑ TAKE DATA OUT
 * 
 * - WRITE END (fd[1]): For INPUTTING data into the pipe
 *   Example: cmd1 writes its output → fd[1] (puts data IN the pipe)
 * 
 * - READ END (fd[0]): For OUTPUTTING/EXTRACTING data from the pipe
 *   Example: cmd2 reads its input ← fd[0] (takes data OUT of the pipe)
 * 
 * So in a pipeline:
 *   - A command's STDOUT connects to pipe's WRITE end (fd[1]) - puts data in
 *   - Next command's STDIN connects to pipe's READ end (fd[0]) - takes data out
 */

int picoshell(char **cmds[])
{
	pid_t pid;         // For fork
	int fd[2];         // Current pipe: fd[0] = read, fd[1] = write
	int last_fd = -1;  // Previous pipe's READ end (input for current command)
	int i = 0;         // Command index

	/* STEP 3: Loop through each command */
	while (cmds[i])
	{
		/* STEP 3.1: Create a pipe for the NEXT command (if not last)
		 * 
		 * We only create a pipe if there's a command after this one
		 * because we need somewhere to send THIS command's output.
		 * 
		 * If this is the LAST command, no pipe needed (output goes to terminal)
		 */
		if (cmds[i + 1] && pipe(fd) == -1)
			return 1;

		/* STEP 3.2: Fork to create child for current command */
		pid = fork();
		if (pid == -1)
		{
			// Fork failed - clean up the pipe we just created (if any)
			if (cmds[i + 1])
			{
				close(fd[0]);
				close(fd[1]);
			}
			return 1;
		}

		/* STEP 3.3: CHILD PROCESS - Execute current command */
		if (!pid)
		{
			/* Set up INPUT: Connect stdin to previous pipe (if not first command)
			 * 
			 * CRITICAL: last_fd is the READ end of the PREVIOUS pipe!
			 * 
			 * Data flow: [prev_cmd] --writes--> [pipe] --last_fd(READ)--> [current_cmd reads]
			 * 
			 * dup2(last_fd, STDIN_FILENO) means:
			 * "Make stdin READ from last_fd"
			 * 
			 * So the current command RECEIVES data from the previous command.
			 * The chain moves FORWARD: prev_cmd → pipe → current_cmd
			 * 
			 * For cmd1: No previous pipe, read from terminal stdin
			 * For cmd2: Read from pipe1 (what cmd1 wrote)
			 * For cmd3: Read from pipe2 (what cmd2 wrote)
			 */
			if (last_fd != -1)
			{
				/* Redirect stdin to read from previous pipe
				 * Now when this command reads from stdin, it gets previous command's output
				 */
				if (dup2(last_fd, STDIN_FILENO) == -1)
					exit(1);
				close(last_fd);  // Close after duplicating
			}

			/* Set up OUTPUT: Connect stdout to current pipe (if not last command)
			 * 
			 * For cmd1: Write to pipe1 (fd[1])
			 * For cmd2: Write to pipe2 (fd[1])
			 * For cmd3: No next command, write to terminal stdout
			 */
			if (cmds[i + 1])
			{
				/* Close read end - we only write to the pipe */
				close(fd[0]);
				
				/* Redirect stdout to write to current pipe
				 * Now when this command writes to stdout, it goes to the pipe
				 */
				if (dup2(fd[1], STDOUT_FILENO) == -1)
					exit(1);
				close(fd[1]);  // Close after duplicating
			}

			/* Execute the command
			 * stdin and stdout are now properly connected to pipes
			 */
			execvp(cmds[i][0], cmds[i]);
			exit(1);  // Only reached if execvp fails
		}

		/* STEP 3.4: PARENT PROCESS - Clean up and prepare for next iteration */
		
		/* Close the previous pipe's read end (if exists)
		 * 
		 * We stored it in last_fd for the child, but parent doesn't need it anymore.
		 * The child has already dup2'd it or this is the first command.
		 */
		if (last_fd != -1)
			close(last_fd);

		/* If there's a next command, manage the current pipe */
		if (cmds[i + 1])
		{
			/* Close write end - parent doesn't write to the pipe
			 * Only the child writes to it
			 */
			close(fd[1]);
			
			/* Save the read end for the NEXT command
			 * The next iteration will use this as last_fd
			 * 
			 * COMPLETE FLOW EXAMPLE (iteration i, next is i+1):
			 * 
			 * 1. Current child (i): dup2(fd[1], STDOUT_FILENO)
			 *    → Child writes output to fd[1] (write end)
			 * 
			 * 2. Data flows through pipe buffer
			 * 
			 * 3. Parent saves: last_fd = fd[0] (read end)
			 * 
			 * 4. Next iteration, next child (i+1): dup2(last_fd, STDIN_FILENO)
			 *    → Next child reads from fd[0] (last_fd)
			 *    → Gets the output from child (i)!
			 * 
			 * So: child(i) stdout → fd[1] → [pipe] → fd[0](last_fd) → child(i+1) stdin
			 */
			last_fd = fd[0];
		}

		i++;  // Move to next command
	}

	/* STEP 4: Wait for all children to finish
	 * 
	 * All commands are now running in parallel, connected by pipes.
	 * Wait for them all to complete before returning.
	 */
	while (wait(NULL) > 0)
		;

	return 0;
}

/*
 * CONCRETE EXAMPLE: Let's trace "ls | grep file"
 * 
 * INPUT:
 * cmds[0] = {"ls", NULL}
 * cmds[1] = {"grep", "file", NULL}
 * cmds[2] = NULL
 * 
 * EXECUTION TRACE:
 * 
 * === ITERATION 1: Process "ls" (i=0) ===
 * 
 * 1. last_fd = -1 (no previous pipe)
 * 2. cmds[1] exists → create pipe: fd[0]=3, fd[1]=4
 * 3. fork() → creates child1 (pid=0)
 * 
 * CHILD1 (ls):
 *   - last_fd == -1 → skip stdin setup (read from terminal)
 *   - cmds[1] exists → redirect stdout to fd[1] (pipe write)
 *     dup2(4, STDOUT_FILENO) → stdout = pipe write end
 *     close(3) and close(4)
 *   - execvp("ls", {"ls", NULL}) → becomes ls process
 *   - ls runs, outputs to stdout (which is the pipe!)
 * 
 * PARENT:
 *   - last_fd == -1 → skip closing
 *   - cmds[1] exists → close(fd[1]) = close(4), last_fd = fd[0] = 3
 *   - i++ → i = 1
 * 
 * === ITERATION 2: Process "grep file" (i=1) ===
 * 
 * 1. last_fd = 3 (read end from first pipe)
 * 2. cmds[2] == NULL → no new pipe created
 * 3. fork() → creates child2 (pid=0)
 * 
 * CHILD2 (grep):
 *   - last_fd == 3 → redirect stdin from fd 3 (previous pipe's read end)
 *     dup2(3, STDIN_FILENO) → stdin = previous pipe read end
 *     close(3)
 *   - cmds[2] == NULL → skip stdout setup (write to terminal)
 *   - execvp("grep", {"grep", "file", NULL}) → becomes grep process
 *   - grep reads from stdin (which is ls's output from pipe!)
 *   - grep outputs to stdout (terminal)
 * 
 * PARENT:
 *   - last_fd == 3 → close(3) (no longer needed)
 *   - cmds[2] == NULL → skip pipe management
 *   - i++ → i = 2
 * 
 * === ITERATION 3: Exit loop (cmds[2] == NULL) ===
 * 
 * 4. Wait for both children to finish
 * 5. Return 0
 * 
 * RESULT: ls output flows through pipe to grep, grep outputs to terminal
 */

/*
 * KEY INSIGHTS:
 * 
 * 1. WHY LAST_FD?
 *    - Each command needs to read from the PREVIOUS pipe
 *    - We can't access the previous fd[0] directly in the next iteration
 *    - So we save it in last_fd to use in the next iteration
 * 
 * 2. PIPE CREATION TIMING:
 *    - We create the pipe BEFORE forking the current command
 *    - This pipe will be used for THIS command's output
 *    - The NEXT command will use last_fd to read from this pipe
 * 
 * 3. FD CLOSING SEQUENCE (for middle command in 3-cmd pipeline):
 *    - Child closes old last_fd after dup2 to stdin
 *    - Child closes fd[0] (won't read from current pipe)
 *    - Child closes fd[1] after dup2 to stdout
 *    - Parent closes old last_fd (child inherited it)
 *    - Parent closes fd[1] (only child writes to it)
 *    - Parent saves fd[0] as new last_fd
 * 
 * 4. FIRST COMMAND (no previous pipe):
 *    - last_fd = -1, skip stdin setup
 *    - Reads from terminal stdin
 *    - Writes to pipe (unless it's also the last command)
 * 
 * 5. LAST COMMAND (no next pipe):
 *    - Reads from last_fd (previous pipe)
 *    - Writes to terminal stdout
 *    - No new pipe created
 */
