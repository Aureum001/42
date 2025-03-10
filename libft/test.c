#include "libft.h"
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

static char simpler_toupper(unsigned int i, char c) {
    (void)i;
    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    return c;
}

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
    test_ft_strlen();
    test_ft_strdup();
    test_ft_strchr();
    test_ft_strlcat();
    test_ft_strncmp();
    test_ft_strtrim();
    test_ft_strnstr();
    test_ft_strjoin();
    test_ft_strmapi();
    test_ft_strrchr();
    test_ft_substr();
    test_ft_strlcpy();
    // test_ft_memchr();
    // test_ft_memmove();
    // test_ft_putendl_fd();
    // test_ft_bzero();
    // test_ft_itoa();
    // test_ft_memcmp();
    // test_ft_memset();
    // test_ft_putnbr_fd();
    // test_ft_memccpy();
    // test_ft_memcpy();
    // test_ft_putchar_fd();
    // test_ft_putstr_fd();
    // test_ft_calloc();
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

void test_ft_strlen(void) {
    assert(ft_strlen("") == 0);
    assert(ft_strlen("hello") == 5);
    assert(ft_strlen("hello\0world") == 5);
    printf("test_ft_strlen passed\n");
}

void test_ft_strchr(void) {
    char str[] = "hello";
    assert(ft_strchr(str, 'l') == strchr(str, 'l'));
    assert(ft_strchr(str, 'z') == NULL);
    assert(ft_strchr(str, '\0') == strchr(str, '\0'));
    printf("test_ft_strchr passed\n");
}

void test_ft_strdup(void){
    char *str = "Hello World";
    char *dup = ft_strdup(str);
    assert(strcmp(str, dup) == 0);
    free(dup);
    assert(ft_strdup("") != NULL);
    assert(ft_strdup(NULL) == NULL);
    printf("test_ft_strdup passed\n");
}

void test_ft_strlcpy(void) {
    char dest1[10];
    char dest2[10];
    assert(ft_strlcpy(dest1, "hello", sizeof(dest1)) == strlen("hello"));
    assert(strcmp(dest1, "hello") == 0);

    assert(ft_strlcpy(dest2, "toolongstring", sizeof(dest2)) == strlen("toolongstring"));
    assert(strncmp(dest2, "toolongs", 8) == 0);

    assert(ft_strlcpy(dest1, "", sizeof(dest1)) == 0);
    assert(dest1[0] == '\0');

    assert(ft_strlcpy(NULL, "test", 0) == strlen("test"));

    printf("test_ft_strlcpy passed\n");
}

void test_ft_strlcat(void) {
    char dest1[20] = "hello";
    char dest2[20] = "hello";
    assert(ft_strlcat(dest1, " world", sizeof(dest1)) == strlen("hello world"));
    assert(strcmp(dest1, "hello world") == 0);

    assert(ft_strlcat(dest2, " very long string", sizeof(dest2)) == strlen("hello very long string"));
    ft_strlcat(dest2, " very long string", sizeof(dest2));
    assert(strncmp(dest2, "hello very long", 15) == 0);

    char dest3[5] = "abc";
    assert(ft_strlcat(dest3, "defg", sizeof(dest3)) == strlen("abcdefg"));
    assert(strncmp(dest3, "abcd", sizeof(dest3)) == 0);

    char dest4[10] = "";
    assert(ft_strlcat(dest4, "test", sizeof(dest4)) == strlen("test"));

    printf("test_ft_strlcat passed\n");
}

void test_ft_strrchr(void) {
    char str[] = "hello world";
    assert(ft_strrchr(str, 'l') == strrchr(str, 'l'));
    assert(ft_strrchr(str, 'z') == NULL);
    assert(ft_strrchr(str, '\0') == strrchr(str, '\0'));
    printf("test_ft_strrchr passed\n");
}

void test_ft_strnstr(void) {
    char haystack[] = "hello world";
    assert(ft_strnstr(haystack, "world", sizeof(haystack)) == strstr(haystack, "world"));
    assert(ft_strnstr(haystack, "worl", 4) == NULL);
    assert(ft_strnstr(haystack, "", sizeof(haystack)) == haystack);
    assert(ft_strnstr(haystack, "z", sizeof(haystack)) == NULL);
    printf("test_ft_strnstr passed\n");
}

void test_ft_strncmp(void) {
    assert(ft_strncmp("hello", "hello", 5) == 0);
    assert(ft_strncmp("hello", "hell", 4) == 0);
    assert(ft_strncmp("hello", "world", 5) < 0);
    assert(ft_strncmp("world", "hello", 5) > 0);
    assert(ft_strncmp("abc", "abcd", 4) < 0);
    assert(ft_strncmp("abcd", "abc", 4) > 0);
    assert(ft_strncmp("", "", 0) == 0);
    printf("test_ft_strncmp passed\n");
}

void test_ft_strjoin(void) {
    char *result = ft_strjoin("hello", " world");
    assert(strcmp(result, "hello world") == 0);
    free(result);

    result = ft_strjoin("", "world");
    assert(strcmp(result, "world") == 0);
    free(result);

    result = ft_strjoin("hello", "");
    assert(strcmp(result, "hello") == 0);
    free(result);

    result = ft_strjoin("", "");
    assert(strcmp(result, "") == 0);
    free(result);

    assert(ft_strjoin(NULL, NULL) == NULL);
    assert(ft_strjoin("test", NULL) == NULL);
    assert(ft_strjoin(NULL, "test") == NULL);

    printf("test_ft_strjoin passed\n");
}

void test_ft_strtrim(void) {
    char *result = ft_strtrim("   hello world   ", " ");
    assert(strcmp(result, "hello world") == 0);
    free(result);

    result = ft_strtrim("...hello world...", ".");
    assert(strcmp(result, "hello world") == 0);
    free(result);

    result = ft_strtrim(" \t\nhello\t\n ", " \t\n");
    assert(strcmp(result, "hello") == 0);
    free(result);

    result = ft_strtrim("hello", " ");
    assert(strcmp(result, "hello") == 0);
    free(result);

    result = ft_strtrim("", " ");
    assert(strcmp(result, "") == 0);
    free(result);

    result = ft_strtrim("aaaa", "a");
    assert(strcmp(result, "") == 0);
    free(result);

    printf("test_ft_strtrim passed\n");
}

void test_ft_substr(void) {
    char str[] = "hello world";
    char *result = ft_substr(str, 6, 5);
    assert(strcmp(result, "world") == 0);
    free(result);

    result = ft_substr(str, 0, 5);
    assert(strcmp(result, "hello") == 0);
    free(result);

    result = ft_substr(str, 11, 5);
    assert(strcmp(result, "") == 0);
    free(result);

    result = ft_substr(str, 6, 100);
    assert(strcmp(result, "world") == 0);
    free(result);

    result = ft_substr("", 0, 10);
    assert(strcmp(result, "") == 0);
    free(result);

    assert(ft_substr(NULL, 0, 10) == NULL);

    printf("test_ft_substr passed\n");
}

void test_ft_strmapi(void){
    char *str = ft_strmapi("hello", (char (*)(unsigned int, char))simpler_toupper);
    assert(strcmp(str, "HELLO") == 0);
    free(str);

    str = ft_strmapi("", (char (*)(unsigned int, char))simpler_toupper);
    assert(strcmp(str, "") == 0);
    free(str);

    assert(ft_strmapi("test", NULL) == NULL);

    printf("test_ft_strmapi passed\n");
}
