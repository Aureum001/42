#include "libft.h"
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>

// Function declarations for tests
void test_ft_atoi(void);
void test_ft_isalpha(void);
void test_ft_isprint(void);
void test_ft_memchr(void);
void test_ft_memmove(void);
void test_ft_putendl_fd(void);
void test_ft_strchr(void);
void test_ft_strlcat(void);
void test_ft_strncmp(void);
void test_ft_strtrim(void);
void test_ft_bzero(void);
void test_ft_isascii(void);
void test_ft_itoa(void);
void test_ft_memcmp(void);
void test_ft_memset(void);
void test_ft_putnbr_fd(void);
void test_ft_strdup(void);
void test_ft_strlen(void);
void test_ft_strnstr(void);
void test_ft_tolower(void);
void test_ft_isalnum(void);
void test_ft_isdigit(void);
void test_ft_memccpy(void);
void test_ft_memcpy(void);
void test_ft_putchar_fd(void);
void test_ft_putstr_fd(void);
void test_ft_strjoin(void);
void test_ft_strmapi(void);
void test_ft_strrchr(void);
void test_ft_toupper(void);
void test_ft_substr(void);
void test_ft_calloc(void);
void test_ft_strlcpy(void);
void test_ft_split(void);
void test_ft_lstadd_back(void);
void test_ft_lstadd_front(void);
void test_ft_lstclear(void);
void test_ft_lstdelone(void);
void test_ft_lstiter(void);
void test_ft_lstlast(void);
void test_ft_lstmap(void);
void test_ft_lstnew(void);
void test_ft_lstsize(void);

int main(void) {
    test_ft_atoi();
	test_ft_isalpha();
    test_ft_isprint();
    test_ft_tolower();
    test_ft_isalnum();
    test_ft_isdigit();
    test_ft_toupper();
    test_ft_isascii();
    // test_ft_memchr();
    // test_ft_memmove();
    // test_ft_putendl_fd();
    // test_ft_strchr();
    // test_ft_strlcat();
    // test_ft_strncmp();
    // test_ft_strtrim();
    // test_ft_bzero();
    // test_ft_itoa();
    // test_ft_memcmp();
    // test_ft_memset();
    // test_ft_putnbr_fd();
    // test_ft_strdup();
    // test_ft_strlen();
    // test_ft_strnstr();
    // test_ft_memccpy();
    // test_ft_memcpy();
    // test_ft_putchar_fd();
    // test_ft_putstr_fd();
    // test_ft_strjoin();
    // test_ft_strmapi();
    // test_ft_strrchr();
    // test_ft_substr();
    // test_ft_calloc();
    // test_ft_strlcpy();
    // test_ft_split();
    // test_ft_lstadd_back();
    // test_ft_lstadd_front();
    // test_ft_lstclear();
    // test_ft_lstdelone();
    // test_ft_lstiter();
    // test_ft_lstlast();
    // test_ft_lstmap();
    // test_ft_lstnew();
    // test_ft_lstsize();
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

void test_ft_isalpha(void) {
    for (int i = -1; i <= 255; i++) {  
        assert((ft_isalpha(i) != 0) == (isalpha(i) != 0));  
    }
    printf("test_ft_isalpha passed\n");
}

void test_ft_isdigit(void) {
    for (int i = -1; i <= 256; i++) {
        assert(ft_isdigit(i) == isdigit(i));
    }
    printf("test_ft_isdigit passed\n");
}

void test_ft_isalnum(void) {
    for (int i = -1; i <= 256; i++) {
        assert((ft_isalnum(i) != 0) == (isalnum(i) != 0));
    }
    printf("test_ft_isalnum passed\n");
}

void test_ft_isascii(void) {
    for (int i = -1; i <= 256; i++) {
        assert(ft_isascii(i) == isascii(i));
    }
    printf("test_ft_isascii passed\n");
}

void test_ft_isprint(void) {
    for (int i = -1; i <= 256; i++) {
        assert((ft_isprint(i) != 0) == (isprint(i) != 0));
    }
    printf("test_ft_isprint passed\n");
}

void test_ft_tolower(void) {
    for (int i = -1; i <= 256; i++) {
        assert(ft_tolower(i) == tolower(i));
    }
    printf("test_ft_tolower passed\n");
}

void test_ft_toupper(void) {
    for (int i = -1; i <= 256; i++) {
        assert(ft_toupper(i) == toupper(i));
    }
    printf("test_ft_toupper passed\n");
}