#include "libft.h"
#include <stdio.h>
#include <assert.h>
#include <limits.h>

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
	// test_ft_isalpha();
    // test_ft_isprint();
    // test_ft_memchr();
    // test_ft_memmove();
    // test_ft_putendl_fd();
    // test_ft_strchr();
    // test_ft_strlcat();
    // test_ft_strncmp();
    // test_ft_strtrim();
    // test_ft_bzero();
    // test_ft_isascii();
    // test_ft_itoa();
    // test_ft_memcmp();
    // test_ft_memset();
    // test_ft_putnbr_fd();
    // test_ft_strdup();
    // test_ft_strlen();
    // test_ft_strnstr();
    // test_ft_tolower();
    // test_ft_isalnum();
    // test_ft_isdigit();
    // test_ft_memccpy();
    // test_ft_memcpy();
    // test_ft_putchar_fd();
    // test_ft_putstr_fd();
    // test_ft_strjoin();
    // test_ft_strmapi();
    // test_ft_strrchr();
    // test_ft_toupper();
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
    // Tests for ft_isalpha go here
    printf("test_ft_isalpha passed\n");
}

void test_ft_isprint(void) {
    // Tests for ft_isprint go here
    printf("test_ft_isprint passed\n");
}

void test_ft_memchr(void) {
    // Tests for ft_memchr go here
    printf("test_ft_memchr passed\n");
}

void test_ft_memmove(void) {
    // Tests for ft_memmove go here
    printf("test_ft_memmove passed\n");
}

void test_ft_putendl_fd(void) {
    // Tests for ft_putendl_fd go here
    printf("test_ft_putendl_fd passed\n");
}

void test_ft_strchr(void) {
    // Tests for ft_strchr go here
    printf("test_ft_strchr passed\n");
}

void test_ft_strlcat(void) {
    // Tests for ft_strlcat go here
    printf("test_ft_strlcat passed\n");
}

void test_ft_strncmp(void) {
    // Tests for ft_strncmp go here
    printf("test_ft_strncmp passed\n");
}

void test_ft_strtrim(void) {
    // Tests for ft_strtrim go here
    printf("test_ft_strtrim passed\n");
}

void test_ft_bzero(void) {
    // Tests for ft_bzero go here
    printf("test_ft_bzero passed\n");
}

void test_ft_isascii(void) {
    // Tests for ft_isascii go here
    printf("test_ft_isascii passed\n");
}

void test_ft_itoa(void) {
    // Tests for ft_itoa go here
    printf("test_ft_itoa passed\n");
}

void test_ft_memcmp(void) {
    // Tests for ft_memcmp go here
    printf("test_ft_memcmp passed\n");
}

void test_ft_memset(void) {
    // Tests for ft_memset go here
    printf("test_ft_memset passed\n");
}

void test_ft_putnbr_fd(void) {
    // Tests for ft_putnbr_fd go here
    printf("test_ft_putnbr_fd passed\n");
}

void test_ft_strdup(void) {
    // Tests for ft_strdup go here
    printf("test_ft_strdup passed\n");
}

void test_ft_strlen(void) {
    // Tests for ft_strlen go here
    printf("test_ft_strlen passed\n");
}

void test_ft_strnstr(void) {
    // Tests for ft_strnstr go here
    printf("test_ft_strnstr passed\n");
}

void test_ft_tolower(void) {
    // Tests for ft_tolower go here
    printf("test_ft_tolower passed\n");
}

void test_ft_isalnum(void) {
    // Tests for ft_isalnum go here
    printf("test_ft_isalnum passed\n");
}

void test_ft_isdigit(void) {
    // Tests for ft_isdigit go here
    printf("test_ft_isdigit passed\n");
}

void test_ft_memccpy(void) {
    // Tests for ft_memccpy go here
    printf("test_ft_memccpy passed\n");
}

void test_ft_memcpy(void) {
    // Tests for ft_memcpy go here
    printf("test_ft_memcpy passed\n");
}

void test_ft_putchar_fd(void) {
    // Tests for ft_putchar_fd go here
    printf("test_ft_putchar_fd passed\n");
}

void test_ft_putstr_fd(void) {
    // Tests for ft_putstr_fd go here
    printf("test_ft_putstr_fd passed\n");
}

void test_ft_strjoin(void) {
    // Tests for ft_strjoin go here
    printf("test_ft_strjoin passed\n");
}

void test_ft_strmapi(void) {
    // Tests for ft_strmapi go here
    printf("test_ft_strmapi passed\n");
}

void test_ft_strrchr(void) {
    // Tests for ft_strrchr go here
    printf("test_ft_strrchr passed\n");
}

void test_ft_toupper(void) {
    // Tests for ft_toupper go here
    printf("test_ft_toupper passed\n");
}

void test_ft_substr(void) {
    // Tests for ft_substr go here
    printf("test_ft_substr passed\n");
}

void test_ft_calloc(void) {
    // Tests for ft_calloc go here
    printf("test_ft_calloc passed\n");
}

void test_ft_strlcpy(void) {
    // Tests for ft_strlcpy go here
    printf("test_ft_strlcpy passed\n");
}

void test_ft_split(void) {
    // Tests for ft_split go here
    printf("test_ft_split passed\n");
}

void test_ft_lstadd_back(void) {
    // Tests for ft_lstadd_back go here
    printf("test_ft_lstadd_back passed\n");
}

void test_ft_lstadd_front(void) {
    // Tests for ft_lstadd_front go here
    printf("test_ft_lstadd_front passed\n");
}

void test_ft_lstclear(void) {
    // Tests for ft_lstclear go here
    printf("test_ft_lstclear passed\n");
}

void test_ft_lstdelone(void) {
    // Tests for ft_lstdelone go here
    printf("test_ft_lstdelone passed\n");
}

void test_ft_lstiter(void) {
    // Tests for ft_lstiter go here
    printf("test_ft_lstiter passed\n");
}

void test_ft_lstlast(void) {
    // Tests for ft_lstlast go here
    printf("test_ft_lstlast passed\n");
}

void test_ft_lstmap(void) {
    // Tests for ft_lstmap go here
    printf("test_ft_lstmap passed\n");
}

void test_ft_lstnew(void) {
    // Tests for ft_lstnew go here
    printf("test_ft_lstnew passed\n");
}

void test_ft_lstsize(void) {
    // Tests for ft_lstsize go here
    printf("test_ft_lstsize passed\n");
}