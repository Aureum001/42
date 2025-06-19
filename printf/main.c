#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int main(void)
{
    int ret1, ret2;
    
    printf("=== BASIC TESTS ===\n");
    
    // Character tests
    printf("Character tests:\n");
    ret1 = printf("printf: [%c]\n", 'A');
    ret2 = ft_printf("ft_printf: [%c]\n", 'A');
    printf("Return values: printf=%d, ft_printf=%d\n\n", ret1, ret2);
    
    // String tests
    printf("String tests:\n");
    ret1 = printf("printf: [%s]\n", "Hello World");
    ret2 = ft_printf("ft_printf: [%s]\n", "Hello World");
    printf("Return values: printf=%d, ft_printf=%d\n", ret1, ret2);
    
    // NULL string test (commented out the problematic line)
    printf("NULL string test:\n");
    ret1 = printf("printf: [%s]\n", (char *)NULL);  // This causes the error
    ret2 = ft_printf("ft_printf: [%s]\n", (char *)NULL);
    printf("ft_printf with NULL returned: %d\n\n", ret2);
    
    // Integer tests
    printf("Integer tests:\n");
    ret1 = printf("printf: [%d] [%i]\n", 42, -42);
    ret2 = ft_printf("ft_printf: [%d] [%i]\n", 42, -42);
    printf("Return values: printf=%d, ft_printf=%d\n", ret1, ret2);
    
    ret1 = printf("printf: [%d] [%d]\n", INT_MAX, INT_MIN);
    ret2 = ft_printf("ft_printf: [%d] [%d]\n", INT_MAX, INT_MIN);
    printf("Return values: printf=%d, ft_printf=%d\n\n", ret1, ret2);
    
    // Unsigned tests
    printf("Unsigned tests:\n");
    ret1 = printf("printf: [%u]\n", 42U);
    ret2 = ft_printf("ft_printf: [%u]\n", 42U);
    printf("Return values: printf=%d, ft_printf=%d\n", ret1, ret2);
    
    ret1 = printf("printf: [%u]\n", UINT_MAX);
    ret2 = ft_printf("ft_printf: [%u]\n", UINT_MAX);
    printf("Return values: printf=%d, ft_printf=%d\n\n", ret1, ret2);
    
    // Hex tests
    printf("Hex tests:\n");
    ret1 = printf("printf: [%x] [%X]\n", 255, 255);
    ret2 = ft_printf("ft_printf: [%x] [%X]\n", 255, 255);
    printf("Return values: printf=%d, ft_printf=%d\n", ret1, ret2);
    
    // Pointer tests
    printf("Pointer tests:\n");
    int x = 42;
    ret1 = printf("printf: [%p]\n", &x);
    ret2 = ft_printf("ft_printf: [%p]\n", &x);
    printf("Return values: printf=%d, ft_printf=%d\n", ret1, ret2);
    
    ret1 = printf("printf: [%p]\n", (void *)NULL);
    ret2 = ft_printf("ft_printf: [%p]\n", (void *)NULL);
    printf("Return values: printf=%d, ft_printf=%d\n\n", ret1, ret2);
    
    // Percent tests
    printf("Percent tests:\n");
    ret1 = printf("printf: [%%]\n");
    ret2 = ft_printf("ft_printf: [%%]\n");
    printf("Return values: printf=%d, ft_printf=%d\n\n", ret1, ret2);
    
    printf("=== BONUS TESTS (if implemented) ===\n");
    
    // Width tests
    printf("Width tests:\n");
    ret1 = printf("printf: [%10s]\n", "test");
    ret2 = ft_printf("ft_printf: [%10s]\n", "test");
    printf("Return values: printf=%d, ft_printf=%d\n", ret1, ret2);
    
    // Left align tests
    printf("Left align tests:\n");
    ret1 = printf("printf: [%-10s]\n", "test");
    ret2 = ft_printf("ft_printf: [%-10s]\n", "test");
    printf("Return values: printf=%d, ft_printf=%d\n", ret1, ret2);
    
    // Zero padding tests
    printf("Zero padding tests:\n");
    ret1 = printf("printf: [%010d]\n", 42);
    ret2 = ft_printf("ft_printf: [%010d]\n", 42);
    printf("Return values: printf=%d, ft_printf=%d\n", ret1, ret2);
    
    // Precision tests
    printf("Precision tests:\n");
    ret1 = printf("printf: [%.5d]\n", 42);
    ret2 = ft_printf("ft_printf: [%.5d]\n", 42);
    printf("Return values: printf=%d, ft_printf=%d\n", ret1, ret2);
    
    ret1 = printf("printf: [%.3s]\n", "Hello");
    ret2 = ft_printf("ft_printf: [%.3s]\n", "Hello");
    printf("Return values: printf=%d, ft_printf=%d\n", ret1, ret2);
    
    // Plus flag tests
    printf("Plus flag tests:\n");
    ret1 = printf("printf: [%+d]\n", 42);
    ret2 = ft_printf("ft_printf: [%+d]\n", 42);
    printf("Return values: printf=%d, ft_printf=%d\n", ret1, ret2);
    
    // Space flag tests
    printf("Space flag tests:\n");
    ret1 = printf("printf: [% d]\n", 42);
    ret2 = ft_printf("ft_printf: [% d]\n", 42);
    printf("Return values: printf=%d, ft_printf=%d\n", ret1, ret2);
    
    // Hash flag tests
    printf("Hash flag tests:\n");
    ret1 = printf("printf: [%#x] [%#X]\n", 42, 42);
    ret2 = ft_printf("ft_printf: [%#x] [%#X]\n", 42, 42);
    printf("Return values: printf=%d, ft_printf=%d\n", ret1, ret2);
    
    // Complex combinations
    printf("Complex combinations:\n");
    ret1 = printf("printf: [%#010x]\n", 42);
    ret2 = ft_printf("ft_printf: [%#010x]\n", 42);
    printf("Return values: printf=%d, ft_printf=%d\n", ret1, ret2);

	int result = ft_printf("A");
    printf("\nResult: %d\n", result);

	int result1 = ft_printf("ABC");
    printf("\nResult1 (ABC): %d\n", result1);  // Should be 3
    
    int result2 = ft_printf("A%cC", 'B');
    printf("Result2 (A%%cC): %d\n", result2);  // Should be 3

	int result3 = ft_printf("12345678901234567890");  // 20 chars
    printf("\nResult3 (20 chars): %d\n", result3);  // Should be 20
    
    int result4 = ft_printf("1234567890%c1234567890", 'X');  // 21 chars
    printf("Result4 (21 chars): %d\n", result4);  // Should be 21
    printf("\n");
	
    printf("=== DETAILED COMPARISON ===\n");
	printf("Standard printf:\n");
	ret1 = printf("[%0199.116d%-10.132i%-184.98x%-186.60u]", -1501266571,225545851,491710007u,1838412370u);
	printf("\nLength: %d\n", ret1);

	printf("\nYour ft_printf:\n");
	ret2 = ft_printf("[%0199.116d%-10.132i%-184.98x%-186.60u]", -1501266571,225545851,491710007u,1838412370u);
	printf("\nLength: %d\n", ret2);

	printf("\nLength comparison: printf=%d, ft_printf=%d, Match: %s\n", 
		ret1, ret2, (ret1 == ret2) ? "YES" : "NO");

	// Test each specifier individually
	printf("\n=== INDIVIDUAL SPECIFIER TESTS ===\n");

	printf("Test 1 - %%0199.116d:\n");
	ret1 = printf("printf:    [%0199.116d]\n", -1501266571);
	ret2 = ft_printf("ft_printf: [%0199.116d]\n", -1501266571);
	printf("Lengths: %d vs %d\n\n", ret1, ret2);

	printf("Test 2 - %%-10.132i:\n");
	ret1 = printf("printf:    [%-10.132i]\n", 225545851);
	ret2 = ft_printf("ft_printf: [%-10.132i]\n", 225545851);
	printf("Lengths: %d vs %d\n\n", ret1, ret2);

	printf("Test 3 - %%-184.98x:\n");
	ret1 = printf("printf:    [%-184.98x]\n", 491710007u);
	ret2 = ft_printf("ft_printf: [%-184.98x]\n", 491710007u);
	printf("Lengths: %d vs %d\n\n", ret1, ret2);

	printf("Test 4 - %%-186.60u:\n");
	ret1 = printf("printf:    [%-186.60u]\n", 1838412370u);
	ret2 = ft_printf("ft_printf: [%-186.60u]\n", 1838412370u);
	printf("Lengths: %d vs %d\n\n", ret1, ret2);

    return 0;
}