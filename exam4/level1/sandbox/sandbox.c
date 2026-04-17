/*
 * sandbox - Step by step explanation
 * 
 * GOAL: Test if a function is "safe" (nice) or "dangerous" (bad)
 * 
 * A function is BAD if:
 * - It crashes (segfault, abort, etc.)
 * - It exits with non-zero code
 * - It runs too long (timeout)
 * 
 * KEY CONCEPTS:
 * 
 * 1. FORK: Run the function in a child process
 *    - Isolates the dangerous function from our process
 *    - If it crashes, only the child dies, not the parent
 * 
 * 2. ALARM: Set a timer that sends SIGALRM after timeout seconds
 *    - alarm(5) → SIGALRM sent after 5 seconds
 *    - Interrupts blocking system calls like waitpid()
 * 
 * 3. SIGNALS: Handle asynchronous events
 *    - SIGALRM: Timer expired
 *    - SIGSEGV: Segmentation fault
 *    - SIGABRT: Abort signal
 *    - etc.
 * 
 * 4. WAITPID: Wait for child and get exit status
 *    - Blocks until child finishes or signal arrives
 *    - Returns status that tells us HOW the child died
 * 
 * 5. STATUS MACROS: Decode how child process terminated
 *    - WIFEXITED: true if child exited normally (exit/return)
 *    - WEXITSTATUS: get the exit code (0-255)
 *    - WIFSIGNALED: true if child killed by signal
 *    - WTERMSIG: get the signal number that killed it
 */
#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

/* STEP 1: Signal handler for SIGALRM
 * 
 * WHY DO WE NEED THIS?
 * When alarm() triggers, it sends SIGALRM to our process.
 * By default, SIGALRM terminates the process!
 * 
 * We install a custom handler that does nothing.
 * The important part is that it INTERRUPTS waitpid().
 * 
 * When a signal interrupts waitpid(), waitpid() returns -1 
 * and sets errno = EINTR (interrupted by signal).
 * This is how we detect the timeout!
 */
void alarm_handler(int sig)
{
	(void)sig;  // Do nothing, just catch the signal
}

/* STEP 2: The main sandbox function */
int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	struct sigaction sa;  // Signal action structure
	pid_t pid;            // Process ID
	int status;           // Exit status from waitpid

	/* STEP 2.1: Install signal handler for SIGALRM
	 * 
	 * We need to catch SIGALRM so it doesn't kill our process.
	 * Instead, it will interrupt waitpid() and we can detect timeout.
	 * 
	 * struct sigaction components:
	 * - sa_handler: Function to call when signal arrives
	 * - sa_flags: Behavior flags (0 = default)
	 * - sa_mask: Signals to block while handler runs (empty = block none)
	 */
	sa.sa_handler = alarm_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);  // Initialize empty signal set
	sigaction(SIGALRM, &sa, NULL);  // Install handler for SIGALRM

	/* STEP 2.2: Fork to run the function in isolation
	 * 
	 * WHY FORK?
	 * The function f() might crash, segfault, or do dangerous things.
	 * If we run it directly in our process, it could kill us!
	 * By running in a child, only the child can die.
	 */
	pid = fork();
	if (pid == -1)
		return (-1);  // Fork failed

	/* STEP 2.3: CHILD PROCESS - Execute the function */
	if (!pid)
	{
		/* Run the function
		 * This might:
		 * - Return normally → we reach exit(0)
		 * - Crash (segfault) → child killed by signal
		 * - Call exit(n) → child exits with code n
		 * - Infinite loop → child never finishes
		 */
		f();
		
		/* If we reach here, function returned normally
		 * Exit with 0 to indicate success
		 */
		exit(0);
	}

	/* STEP 2.4: PARENT PROCESS - Monitor the child */
	
	/* Start the timer
	 * 
	 * alarm(timeout) schedules SIGALRM to be sent in 'timeout' seconds.
	 * If the child finishes before timeout, we can cancel it.
	 * If timeout expires, SIGALRM interrupts waitpid().
	 */
	alarm(timeout);

	/* Wait for child to finish
	 * 
	 * waitpid(pid, &status, 0):
	 * - Blocks until child 'pid' terminates
	 * - Stores exit status in 'status'
	 * - Returns -1 if interrupted by signal (errno = EINTR)
	 * 
	 * CASES:
	 * 1. Child finishes before timeout → waitpid returns normally
	 * 2. Timeout expires → SIGALRM interrupts → waitpid returns -1
	 */
	if (waitpid(pid, &status, 0) == -1)
	{
		/* waitpid failed - check why */
		
		if (errno == EINTR)
		{
			/* Interrupted by signal (our SIGALRM)
			 * This means TIMEOUT!
			 * 
			 * The child is still running. We need to:
			 * 1. Kill the child (can't let it keep running)
			 * 2. Wait for it to clean up (avoid zombie)
			 */
			kill(pid, SIGKILL);      // Kill the child forcefully
			waitpid(pid, NULL, 0);   // Reap the child (prevent zombie)
			
			if (verbose)
				printf("Bad function: timed out after %u seconds\n", timeout);
			return (0);  // Bad function (timeout)
		}
		
		/* Some other error in waitpid */
		return (-1);
	}

	/* STEP 2.5: Child finished - analyze HOW it finished
	 * 
	 * The 'status' variable contains encoded information about
	 * how the child terminated. We use macros to decode it.
	 */

	/* Check if child exited normally (via exit() or return)
	 * 
	 * WIFEXITED(status) returns true if:
	 * - Child called exit(n)
	 * - Child's main() returned
	 * 
	 * Returns false if killed by signal
	 */
	if (WIFEXITED(status))
	{
		/* Child exited - get the exit code
		 * 
		 * WEXITSTATUS(status) extracts the exit code (0-255)
		 * This is the value passed to exit(n) or returned from main()
		 */
		if (WEXITSTATUS(status) == 0)
		{
			/* Exited with 0 - SUCCESS!
			 * Function ran and completed without errors
			 */
			if (verbose)
				printf("Nice function!\n");
			return (1);  // Nice function
		}
		else
		{
			/* Exited with non-zero code - ERROR!
			 * Function called exit(n) where n != 0
			 */
			if (verbose)
				printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
			return (0);  // Bad function
		}
	}

	/* Check if child was terminated by a signal
	 * 
	 * WIFSIGNALED(status) returns true if:
	 * - Child killed by signal (SIGSEGV, SIGABRT, etc.)
	 */
	if (WIFSIGNALED(status))
	{
		/* Child was killed by signal - get which one
		 * 
		 * WTERMSIG(status) returns the signal number
		 * strsignal() converts signal number to human-readable string
		 * 
		 * Examples:
		 * - SIGSEGV (11) → "Segmentation fault"
		 * - SIGABRT (6) → "Aborted"
		 * - SIGFPE (8) → "Floating point exception"
		 */
		if (verbose)
			printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
		return (0);  // Bad function (crashed)
	}

	/* If we get here, something unexpected happened
	 * (should not happen in normal cases)
	 */
	return (-1);
}

/*
 * CONCRETE EXAMPLES:
 * 
 * Example 1: Nice function
 * 
 * void good(void) {
 *     int x = 1 + 1;
 * }
 * 
 * sandbox(good, 5, true);
 * 
 * Flow:
 * 1. Fork → child runs good()
 * 2. alarm(5) → timer set for 5 seconds
 * 3. good() completes quickly, returns
 * 4. Child reaches exit(0)
 * 5. waitpid() returns, status shows exit(0)
 * 6. WIFEXITED(status) = true, WEXITSTATUS(status) = 0
 * 7. Output: "Nice function!"
 * 8. Return: 1
 * 
 * 
 * Example 2: Segfault
 * 
 * void bad_segfault(void) {
 *     int *ptr = NULL;
 *     *ptr = 42;  // Crash!
 * }
 * 
 * sandbox(bad_segfault, 5, true);
 * 
 * Flow:
 * 1. Fork → child runs bad_segfault()
 * 2. alarm(5) → timer set
 * 3. Child crashes (SIGSEGV) before timeout
 * 4. waitpid() returns, status shows killed by signal
 * 5. WIFSIGNALED(status) = true, WTERMSIG(status) = SIGSEGV
 * 6. Output: "Bad function: Segmentation fault"
 * 7. Return: 0
 * 
 * 
 * Example 3: Timeout
 * 
 * void bad_infinite(void) {
 *     while (1);  // Infinite loop
 * }
 * 
 * sandbox(bad_infinite, 2, true);
 * 
 * Flow:
 * 1. Fork → child runs bad_infinite()
 * 2. alarm(2) → timer set for 2 seconds
 * 3. Child loops forever...
 * 4. After 2 seconds, SIGALRM sent to parent
 * 5. alarm_handler() called, then returns
 * 6. waitpid() interrupted, returns -1, errno = EINTR
 * 7. kill(pid, SIGKILL) → terminate child
 * 8. waitpid(pid, NULL, 0) → clean up zombie
 * 9. Output: "Bad function: timed out after 2 seconds"
 * 10. Return: 0
 * 
 * 
 * Example 4: Exit with error
 * 
 * void bad_exit(void) {
 *     exit(42);
 * }
 * 
 * sandbox(bad_exit, 5, true);
 * 
 * Flow:
 * 1. Fork → child runs bad_exit()
 * 2. alarm(5) → timer set
 * 3. Child calls exit(42)
 * 4. waitpid() returns, status shows exit(42)
 * 5. WIFEXITED(status) = true, WEXITSTATUS(status) = 42
 * 6. Output: "Bad function: exited with code 42"
 * 7. Return: 0
 */

/*
 * KEY INSIGHTS:
 * 
 * 1. WHY USE SIGNALS FOR TIMEOUT?
 *    - We can't just check time in a loop (wasteful)
 *    - alarm() is efficient - kernel handles timing
 *    - SIGALRM interrupts waitpid() automatically
 * 
 * 2. WHY INSTALL A SIGNAL HANDLER?
 *    - Default SIGALRM action is to terminate the process
 *    - We need to catch it to prevent our death
 *    - Handler can be empty - interruption is what matters
 * 
 * 3. WHY KILL THEN WAITPID ON TIMEOUT?
 *    - kill(pid, SIGKILL): Stop the runaway child
 *    - waitpid(pid, NULL, 0): Clean up zombie process
 *    - If we don't wait, child becomes zombie forever!
 * 
 * 4. STATUS DECODING ORDER:
 *    - Check WIFEXITED first (normal exit)
 *    - Then check WIFSIGNALED (killed by signal)
 *    - These are mutually exclusive (only one can be true)
 * 
 * 5. ERRNO AND EINTR:
 *    - errno is a global variable set by system calls on error
 *    - EINTR means "interrupted by signal"
 *    - Always check errno when syscall returns -1
 * 
 * 6. SECURITY:
 *    - Running untrusted code directly is DANGEROUS
 *    - Fork isolation protects parent process
 *    - Timeout prevents resource exhaustion
 *    - This is a simple sandbox (real ones use more protection)
 */
