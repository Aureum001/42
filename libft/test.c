#include "libft.h"
#include <stdio.h>
#include <assert.h>
#include <limits.h>

// Function declarations for tests
void test_ft_atoi(void);

int main(void) {
    test_ft_atoi();
    printf("All tests passed!\n");
    return 0;
}

// Test functions
void test_ft_atoi(void) {
     // Normal cases
	 assert(ft_atoi("123") == 123);
	 assert(ft_atoi("-456") == -456);
	 assert(ft_atoi("0") == 0);
	 assert(ft_atoi("+0") == 0);
	 assert(ft_atoi("   123") == 123);
	 assert(ft_atoi("   -123") == -123);
	 assert(ft_atoi("   +123") == 123);
	 assert(ft_atoi("\t\r\n\v\f 123") == 123);
	 // Edge cases
	 assert(ft_atoi("2147483647") == 2147483647);
	 assert(ft_atoi("-2147483648") == -2147483648);
	 // Overflow cases.
	 assert(ft_atoi("2147483648") == 0);
	 assert(ft_atoi("-2147483649") == 0);
	 // Invalid input
	 assert(ft_atoi("abc") == 0);
	 assert(ft_atoi("123abc456") == 123);
	 assert(ft_atoi("") == 0);
	 //assert(ft_atoi(NULL) == 0);
	 printf("test_ft_atoi passed\n");
}