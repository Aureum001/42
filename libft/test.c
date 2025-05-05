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
void test_ft_striteri(void);

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
	test_ft_striteri();
    test_ft_strrchr();
    test_ft_substr();
    test_ft_strlcpy();
    test_ft_memchr();
    test_ft_memmove();
    // test_ft_putendl_fd();
    test_ft_bzero();
    test_ft_itoa();
    test_ft_memcmp();
    test_ft_memset();
    // test_ft_putnbr_fd();
    test_ft_memccpy();
    test_ft_memcpy();
    // test_ft_putchar_fd();
    // test_ft_putstr_fd();
    test_ft_calloc();
    test_ft_split();
    test_ft_lstadd_back();
    test_ft_lstadd_front();
    test_ft_lstclear();
    test_ft_lstdelone();
    test_ft_lstiter();
    test_ft_lstlast();
    test_ft_lstmap();
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
	 printf("✅ test_ft_atoi passed\n");
}

void test_ft_isalpha(void) {
     for (int i = -1; i <= 255; i++) {  
         assert((ft_isalpha(i) != 0) == (isalpha(i) != 0));  
     }
     printf("✅ test_ft_isalpha passed\n");
}

void test_ft_isdigit(void) {
    for (int i = -5; i <= 260; i++) { // Wider range for debugging
        if ((ft_isdigit(i) != 0) != (isdigit(i) != 0)) {
            printf("ft_isdigit(%d) failed: ft_isdigit returns %d, isdigit returns %d\n", i, ft_isdigit(i), isdigit(i));
            assert(0); // Force a failure to stop at the problematic value
        }
    }
    printf("✅ test_ft_isdigit passed\n");
}

// void test_ft_isdigit(void) {
//     for (int i = 0; i <= 256; i++) {
//         assert(ft_isdigit(i) == isdigit(i));
//     }
//     printf("test_ft_isdigit passed\n");
// }

void test_ft_isalnum(void) {
    for (int i = -1; i <= 256; i++) {
        assert((ft_isalnum(i) != 0) == (isalnum(i) != 0));
    }
    printf("✅ test_ft_isalnum passed\n");
}

void test_ft_isascii(void) {
    for (int i = -1; i <= 256; i++) {
        assert(ft_isascii(i) == isascii(i));
    }
    printf("✅ test_ft_isascii passed\n");
}

void test_ft_isprint(void) {
    for (int i = -1; i <= 256; i++) {
        assert((ft_isprint(i) != 0) == (isprint(i) != 0));
    }
    printf("✅ test_ft_isprint passed\n");
}

void test_ft_tolower(void) {
    for (int i = -1; i <= 256; i++) {
        assert(ft_tolower(i) == tolower(i));
    }
    printf("✅ test_ft_tolower passed\n");
}

void test_ft_toupper(void) {
    for (int i = -1; i <= 256; i++) {
        assert(ft_toupper(i) == toupper(i));
    }
    printf("✅ test_ft_toupper passed\n");
}

void test_ft_strlen(void) {
    assert(ft_strlen("") == 0);
    assert(ft_strlen("hello") == 5);
    assert(ft_strlen("hello\0world") == 5);
    printf("✅ test_ft_strlen passed\n");
}

void test_ft_strchr(void) {
    char str[] = "hello";
    assert(ft_strchr(str, 'l') == strchr(str, 'l'));
    assert(ft_strchr(str, 'z') == NULL);
    assert(ft_strchr(str, '\0') == strchr(str, '\0'));
    printf("✅ test_ft_strchr passed\n");
}

void test_ft_strdup(void){
    char *str = "Hello World";
    char *dup = ft_strdup(str);
    assert(strcmp(str, dup) == 0);
    free(dup);
    assert(ft_strdup("") != NULL);
    assert(ft_strdup(NULL) == NULL);
    printf("✅ test_ft_strdup passed\n");
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

    printf("✅ test_ft_strlcpy passed\n");
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

    printf("✅ test_ft_strlcat passed\n");
}

void test_ft_strrchr(void) {
    char str[] = "hello world";
    assert(ft_strrchr(str, 'l') == strrchr(str, 'l'));
    assert(ft_strrchr(str, 'z') == NULL);
    assert(ft_strrchr(str, '\0') == strrchr(str, '\0'));
    printf("✅ test_ft_strrchr passed\n");
}

void test_ft_strnstr(void) {
    char haystack[] = "hello world";
    assert(ft_strnstr(haystack, "world", sizeof(haystack)) == strstr(haystack, "world"));
    assert(ft_strnstr(haystack, "worl", 4) == NULL);
    assert(ft_strnstr(haystack, "", sizeof(haystack)) == haystack);
    assert(ft_strnstr(haystack, "z", sizeof(haystack)) == NULL);
    printf("✅ test_ft_strnstr passed\n");
}

void test_ft_strncmp(void) {
    assert(ft_strncmp("hello", "hello", 5) == 0);
    assert(ft_strncmp("hello", "hell", 4) == 0);
    assert(ft_strncmp("hello", "world", 5) < 0);
    assert(ft_strncmp("world", "hello", 5) > 0);
    assert(ft_strncmp("abc", "abcd", 4) < 0);
    assert(ft_strncmp("abcd", "abc", 4) > 0);
    assert(ft_strncmp("", "", 0) == 0);
    printf("✅ test_ft_strncmp passed\n");
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

    printf("✅ test_ft_strjoin passed\n");
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

    printf("✅ test_ft_strtrim passed\n");
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

    printf("✅ test_ft_substr passed\n");
}

void test_ft_strmapi(void){
    char *str = ft_strmapi("hello", (char (*)(unsigned int, char))simpler_toupper);
    assert(strcmp(str, "HELLO") == 0);
    free(str);

    str = ft_strmapi("", (char (*)(unsigned int, char))simpler_toupper);
    assert(strcmp(str, "") == 0);
    free(str);

    assert(ft_strmapi("test", NULL) == NULL);

    printf("✅ test_ft_strmapi passed\n");
}

void test_ft_bzero(void) {
    char buf[10];
    ft_bzero(buf, sizeof(buf));
    for (size_t i = 0; i < sizeof(buf); i++) {
        assert(buf[i] == 0);
    }
    printf("✅ test_ft_bzero passed\n");
}

void test_ft_memcpy(void) {
    char src[] = "hello";
    char dest[6];
    ft_memcpy(dest, src, 6);
    assert(strcmp(dest, src) == 0);

    int src_int[] = {1, 2, 3, 4, 5};
    int dest_int[5];
    ft_memcpy(dest_int, src_int, sizeof(src_int));
    assert(memcmp(dest_int, src_int, sizeof(src_int)) == 0);

    printf("✅ test_ft_memcpy passed\n");
}

void test_ft_memmove(void){
    char str[] = "example";
    ft_memmove(str, str + 2, 5);
    assert(memcmp(str, "ample", 5) == 0);

    char str2[] = "example";
    ft_memmove(str2 + 2, str2, 5);
    assert(memcmp(str2, "exexamp", 7) == 0);

    printf("✅ test_ft_memmove passed\n");
}

void test_ft_calloc(void){
    int *ptr = (int *)ft_calloc(5, sizeof(int));
    assert(ptr != NULL);
    for (int i = 0; i < 5; i++)
        assert(ptr[i] == 0);
    free(ptr);

    assert(ft_calloc(0, 0) != NULL);
    assert(ft_calloc(SIZE_MAX, SIZE_MAX) == NULL);

    printf("✅ test_ft_calloc passed\n");
}

void test_ft_memchr(void) {
    char str[] = "hello world";
    int char_to_find = 'o';
    size_t len = strlen(str);

    // Character found at the beginning
    assert(ft_memchr(str, 'h', len) == memchr(str, 'h', len));

    // Character found in the middle (first occurrence)
    assert(ft_memchr(str, char_to_find, len) == memchr(str, char_to_find, len));

    // Character found at the end
    assert(ft_memchr(str, 'd', len) == memchr(str, 'd', len));

    // Character not found
    assert(ft_memchr(str, 'z', len) == NULL);
    assert(ft_memchr(str, 'o', 2) == NULL); // Present but outside n

    // Empty memory area (n = 0)
    assert(ft_memchr(str, 'o', 0) == NULL);

    // Search for null byte
    assert(ft_memchr(str, '\0', len + 1) == memchr(str, '\0', len + 1));

    // Different data types (searching within an int array)
    int int_array[] = {1, 2, 3, 4, 2, 6};
    int int_to_find = 2;
    size_t int_len = sizeof(int_array);
    assert(ft_memchr(int_array, int_to_find, int_len) == memchr(int_array, int_to_find, int_len));

    // NULL pointer for s (implementation-defined, should not crash)
    // You might want to check if your ft_memchr handles NULL gracefully
    // (e.g., returns NULL, though the standard doesn't guarantee this).
    assert(ft_memchr(NULL, 'a', 5) == NULL); // A common safe implementation

    // Varying n
    assert(ft_memchr(str, 'o', 5) != NULL);
    assert(ft_memchr(str, 'o', 4) == NULL);

    printf("✅ test_ft_memchr passed\n");
}

void test_ft_itoa(void) {
    // Normal cases
    assert(strcmp(ft_itoa(0), "0") == 0);
    assert(strcmp(ft_itoa(123), "123") == 0);
    assert(strcmp(ft_itoa(-456), "-456") == 0);
    assert(strcmp(ft_itoa(9), "9") == 0);
    assert(strcmp(ft_itoa(-9), "-9") == 0);

    // Edge cases for int
    assert(strcmp(ft_itoa(INT_MAX), "2147483647") == 0);
    assert(strcmp(ft_itoa(INT_MIN), "-2147483648") == 0);

    // Single digit numbers
    assert(strcmp(ft_itoa(5), "5") == 0);
    assert(strcmp(ft_itoa(-3), "-3") == 0);
    // Larger numbers
    assert(strcmp(ft_itoa(987654321), "987654321") == 0);
    assert(strcmp(ft_itoa(-987654321), "-987654321") == 0);

    printf("✅ test_ft_itoa passed\n");
}

void test_ft_memcmp(void) {
    char s1_identical[] = "hello";
    char s2_identical[] = "hello";
    char s1_diff_first[] = "world";
    char s2_diff_first[] = "hello";
    char s1_diff_middle[] = "helxo";
    char s2_diff_middle[] = "hello";
    char s1_diff_last[] = "hellp";
    char s2_diff_last[] = "hello";
    char s1_prefix[] = "hell";
    char s2_longer[] = "hello";
    char s1_longer[] = "hello";
    char s2_prefix[] = "hell";
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 5, 5};

    // Identical memory areas
    assert(ft_memcmp(s1_identical, s2_identical, 5) == memcmp(s1_identical, s2_identical, 5));
    assert(ft_memcmp(s1_identical, s2_identical, 3) == memcmp(s1_identical, s2_identical, 3));
    assert(ft_memcmp(s1_identical, s2_identical, 0) == 0); // n = 0

    // Different memory areas (first byte differs)
    assert(ft_memcmp(s1_diff_first, s2_diff_first, 5) == memcmp(s1_diff_first, s2_diff_first, 5));

    // Different memory areas (middle byte differs)
    assert(ft_memcmp(s1_diff_middle, s2_diff_middle, 5) == memcmp(s1_diff_middle, s2_diff_middle, 5));

    // Different memory areas (last byte differs)
    assert(ft_memcmp(s1_diff_last, s2_diff_last, 5) == memcmp(s1_diff_last, s2_diff_last, 5));

    // One memory area is a prefix of the other
    assert(ft_memcmp(s1_prefix, s2_longer, 4) == memcmp(s1_prefix, s2_longer, 4));
    assert(ft_memcmp(s1_longer, s2_prefix, 4) == memcmp(s1_longer, s2_prefix, 4));
    assert(ft_memcmp(s1_prefix, s2_longer, 5) < 0); // 'l' vs 'o'
    assert(ft_memcmp(s1_longer, s2_prefix, 5) > 0); // 'o' vs '\0'

    // Comparison with null bytes
    char s3[] = "abc\0def";
    char s4[] = "abc\0ghi";
    assert(ft_memcmp(s3, s4, 7) == memcmp(s3, s4, 7));
    assert(ft_memcmp(s3, s4, 4) == 0); // Up to the null byte

    // Different data types (int arrays)
    assert(ft_memcmp(arr1, arr2, sizeof(arr1)) == memcmp(arr1, arr2, sizeof(arr1)));
    assert(ft_memcmp(arr1, arr2, sizeof(int) * 3) == 0);
    assert(ft_memcmp(arr1, arr2, sizeof(int) * 4) < 0);

    // Varying n (larger than size)
    assert(ft_memcmp(s1_identical, s2_identical, 10) == memcmp(s1_identical, s2_identical, 10));

    printf("✅ test_ft_memcmp passed\n");
}

void test_ft_memset(void) {
    char buf1[10];
    char expected1[10];
    int int_buf[5];
    int expected_int_buf[5];

    // Fill with 0
    ft_memset(buf1, 0, sizeof(buf1));
    memset(expected1, 0, sizeof(expected1));
    assert(memcmp(buf1, expected1, sizeof(buf1)) == 0);

    // Fill with a positive value
    ft_memset(buf1, 'a', sizeof(buf1));
    memset(expected1, 'a', sizeof(expected1));
    assert(memcmp(buf1, expected1, sizeof(buf1)) == 0);

    // Fill with -1 (should be 255 as unsigned char)
    ft_memset(buf1, -1, sizeof(buf1));
    memset(expected1, -1, sizeof(expected1));
    assert(memcmp(buf1, expected1, sizeof(buf1)) == 0);

    // Fill a portion of the buffer (beginning)
    char buf2[10] = "abcddefghi";
    char expected2[10] = "xxxxxefghi";
    ft_memset(buf2, 'x', 5);
    memset(expected2, 'x', 5);
    assert(memcmp(buf2, expected2, sizeof(buf2)) == 0);

    // Fill a portion of the buffer (middle)
    char buf3[10] = "abcddefghi";
    char expected3[10] = "abcXXXXghi";
    ft_memset(buf3 + 3, 'X', 4);
    memset(expected3 + 3, 'X', 4);
    assert(memcmp(buf3, expected3, sizeof(buf3)) == 0);

    // Fill a portion of the buffer (end)
    char buf4[10] = "abcdefghij";
    char expected4[10] = "abcdefgXXX";
    ft_memset(buf4 + 7, 'X', 3);
    memset(expected4 + 7, 'X', 3);
    assert(memcmp(buf4, expected4, sizeof(buf4)) == 0);

    // Fill with length 0
    char buf5[10] = "abcdefghij";
    char expected5[10] = "abcdefghij";
    assert(ft_memset(buf5, 'y', 0) == buf5); // Should return original pointer
    assert(memcmp(buf5, expected5, sizeof(buf5)) == 0); // Should not modify

    // Fill an int array
    ft_memset(int_buf, 1, sizeof(int_buf)); // Note: fills byte by byte
    memset(expected_int_buf, 1, sizeof(expected_int_buf));
    assert(memcmp(int_buf, expected_int_buf, sizeof(int_buf)) == 0);

    printf("✅ test_ft_memset passed\n");
}

void test_ft_memccpy(void) {
    char src[] = "hello world";
    char dst[20];
    char expected_dst[20];
    void *result;

    // Character found at the beginning
    memset(dst, 'x', sizeof(dst));
    memset(expected_dst, 'x', sizeof(expected_dst));
    result = ft_memccpy(dst, src, 'h', sizeof(src));
    assert(result == dst + 1);
    expected_dst[0] = 'h';
    assert(memcmp(dst, expected_dst, sizeof(dst)) == 0);

    // Character found in the middle
    memset(dst, 'x', sizeof(dst));
    memset(expected_dst, 'x', sizeof(expected_dst));
    result = ft_memccpy(dst, src, 'o', sizeof(src));
    assert(result == dst + 5);
    strncpy(expected_dst, "hell", 4);
    expected_dst[4] = 'o';
    assert(memcmp(dst, expected_dst, sizeof(dst)) == 0);

    // Character found at the end (within n)
    memset(dst, 'x', sizeof(dst));
    memset(expected_dst, 'x', sizeof(expected_dst));
    result = ft_memccpy(dst, src, 'd', sizeof(src));
    assert(result == dst + 11);
    strncpy(expected_dst, "hello worl", 10);
    expected_dst[10] = 'd';
    assert(memcmp(dst, expected_dst, sizeof(dst)) == 0);

    // Character not found (within n)
    memset(dst, 'x', sizeof(dst));
    memset(expected_dst, 'x', sizeof(expected_dst));
    result = ft_memccpy(dst, src, 'z', sizeof(src));
    assert(result == NULL);
    strncpy(expected_dst, src, sizeof(src));
    assert(memcmp(dst, expected_dst, sizeof(dst)) == 0);

    // n is smaller than src and c is present later
    memset(dst, 'x', sizeof(dst));
    memset(expected_dst, 'x', sizeof(expected_dst));
    result = ft_memccpy(dst, src, 'o', 4);
    assert(result == NULL);
    strncpy(expected_dst, src, 4);
    assert(memcmp(dst, expected_dst, sizeof(dst)) == 0);

    // n is 0
    memset(dst, 'x', sizeof(dst));
    result = ft_memccpy(dst, src, 'o', 0);
    assert(result == NULL);
    assert(memcmp(dst, "xxxxxxxxxxxxxxxxxxxx", sizeof(dst)) == 0); // No change

    // Different data types (int array)
    int src_int[] = {1, 2, 3, 4, 5};
    int dst_int[5];
    memset(dst_int, 0, sizeof(dst_int));
    result = ft_memccpy(dst_int, src_int, 3, sizeof(src_int));
    assert((char *)result == (char *)dst_int + 9);
    int expected_dst_int[] = {1, 2, 3, 0, 0};
    assert(memcmp(dst_int, expected_dst_int, sizeof(dst_int)) == 0);

    // NULL pointer for dst or src (implementation-defined)
    // assert(ft_memccpy(NULL, src, 'a', 5) == NULL);
    // assert(ft_memccpy(dst, NULL, 'a', 5) == NULL);

    printf("✅ test_ft_memccpy passed\n");
}

// Helper function to free the memory allocated by ft_split
void free_split_result(char **result) {
    if (result) {
        for (int i = 0; result[i] != NULL; i++) {
            free(result[i]);
        }
        free(result);
    }
}

void assert_split_result(char **result, char *expected[]) {
    int i = 0;
    if (!expected && !result)
        return;
    if (!expected || !result)
        assert(0); // One is NULL, the other isn't
    while (expected[i] != NULL && result[i] != NULL) {
        assert(strcmp(result[i], expected[i]) == 0);
        i++;
    }
    assert(expected[i] == NULL && result[i] == NULL); // Both should end with NULL
}

void test_ft_split(void) {
    char *s1 = "hello world";
    char *expected1[] = {"hello", "world", NULL};
    char **result1 = ft_split(s1, ' ');
    assert_split_result(result1, expected1);
    free_split_result(result1);

    char *s2 = "hello  world";
    char *expected2[] = {"hello", "world", NULL}; 
    char **result2 = ft_split(s2, ' ');
    assert_split_result(result2, expected2);
    free_split_result(result2);

    char *s3 = "      split       this for   me  !       ";
    char *expected3[] = {"split", "this", "for", "me", "!", NULL};
    char **result3 = ft_split(s3, ' ');
    assert_split_result(result3, expected3);
    free_split_result(result3);

    char *s4 = "no_delimiter";
    char *expected4[] = {"no_delimiter", NULL};
    char **result4 = ft_split(s4, ' ');
    assert_split_result(result4, expected4);
    free_split_result(result4);

    // char *s5 = "";
    // char *expected5[] = {"", NULL}; // Or an empty array {}, check your implementation
    // char **result5 = ft_split(s5, ' ');
    // assert_split_result(result5, expected5);
    // free_split_result(result5);

    // char *s6 = "|||";
    // char *expected6[] = {"", "", "", NULL};
    // char **result6 = ft_split(s6, '|');
    // assert_split_result(result6, expected6);
    // free_split_result(result6);

    char *s7 = NULL;
    assert(ft_split(s7, ' ') == NULL);

    printf("✅ test_ft_split passed\n");
}

// Helper function to compare two lists (content only for simplicity here)
int compare_lists(t_list *lst1, void *content1, t_list *lst2, void *content2) {
    if (!lst1 || !lst2)
        return (lst1 == lst2) && (content1 == content2);
    return (lst1->content == content1) && (lst2->content == content2);
}

void test_ft_lstadd_back()
{
	t_list *head = NULL;
    t_list *new_node1;
    t_list *new_node2;
    t_list *new_node3;

    // Test 1: Add to an empty list
    new_node1 = ft_lstnew("first");
    ft_lstadd_back(&head, new_node1);
    assert(head == new_node1);
    assert(head->next == NULL);
    assert(ft_lstsize(head) == 1);

    // Test 2: Add to a list with one element
    new_node2 = ft_lstnew("second");
    ft_lstadd_back(&head, new_node2);
    assert(head == new_node1);
    assert(head->next == new_node2);
    assert(new_node2->next == NULL);
    assert(ft_lstsize(head) == 2);

    // Test 3: Add to a list with multiple elements
    new_node3 = ft_lstnew("third");
    ft_lstadd_back(&head, new_node3);
    assert(head == new_node1);
    assert(head->next == new_node2);
    assert(new_node2->next == new_node3);
    assert(new_node3->next == NULL);
    assert(ft_lstsize(head) == 3);

    // Clean up memory
    t_list *current = head;
    t_list *next;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL; // Reset head for potential future tests
    printf("✅ test_ft_lstadd_back passed\n");
}

void test_ft_lstadd_front()
{
	t_list *head = NULL;
    t_list *new_node1;
    t_list *new_node2;
    t_list *new_node3;

    // Test 1: Add to an empty list
    new_node1 = ft_lstnew("first");
    ft_lstadd_front(&head, new_node1);
    assert(head == new_node1);
    assert(head->next == NULL);
    assert(ft_lstsize(head) == 1);

    // Test 2: Add to a list with one element
    new_node2 = ft_lstnew("second");
    ft_lstadd_front(&head, new_node2);
    assert(head == new_node2);
    assert(head->next == new_node1);
    assert(ft_lstsize(head) == 2);

    // Test 3: Add to a list with multiple elements
    new_node3 = ft_lstnew("third");
    ft_lstadd_front(&head, new_node3);
    assert(head == new_node3);
    assert(head->next == new_node2);
    assert(new_node2->next == new_node1);
    assert(ft_lstsize(head) == 3);

    // Clean up memory
    t_list *current = head;
    t_list *next;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL; // Reset head
    printf("✅ test_ft_lstadd_front passed\n");
}

// Global variable to track if the del function was called
int del_called = 0;
void *last_deleted_content = NULL;

// Custom del function for testing
void test_del(void *content) {
    del_called++;
    last_deleted_content = content;
}

void test_ft_lstclear() {
    t_list *head = NULL;
    char *content1 = "one";
    char *content2 = "two";
    char *content3 = "three";

    // Test 1: Clear an empty list
    ft_lstclear(&head, test_del);
    assert(head == NULL);
    assert(del_called == 0);

    // Test 2: Clear a list with one element
    head = ft_lstnew(content1);
    del_called = 0;
    last_deleted_content = NULL;
    ft_lstclear(&head, test_del);
    assert(head == NULL);
    assert(del_called == 1);
    assert(last_deleted_content == content1);

    // Test 3: Clear a list with multiple elements
    head = ft_lstnew(content1);
    head->next = ft_lstnew(content2);
    head->next->next = ft_lstnew(content3);
    del_called = 0;
    last_deleted_content = NULL;
    ft_lstclear(&head, test_del);
    assert(head == NULL);
    assert(del_called == 3);
    // The order of deletion isn't strictly defined, but the count should be correct
    

    printf("✅ test_ft_lstclear passed\n");
}

void test_ft_lstdelone() {
    t_list *node1 = ft_lstnew("one");
    t_list *node2 = ft_lstnew("two");
    node1->next = node2;

    // Test 1: Delete a non-NULL node with a non-NULL del function
    del_called = 0;
    last_deleted_content = NULL;
    ft_lstdelone(node1, test_del);
    assert(del_called == 1);
    assert(strcmp(last_deleted_content, "one") == 0);
    // We can't directly assert if node1 is freed as the pointer in the test remains
    // However, if we try to access it, it should be invalid.

    // Test 2: Delete a NULL node
    del_called = 0;
    ft_lstdelone(NULL, test_del);
    assert(del_called == 0);

    // Test 3: Delete a non-NULL node with a NULL del function
    t_list *node3 = ft_lstnew("three");
    del_called = 0;
    ft_lstdelone(node3, NULL);
    assert(del_called == 0);
    free(node3); // We need to free it manually as del wasn't called

    // Clean up remaining (node2)
    free(node2);

    printf("✅ test_ft_lstdelone passed\n");
}

// Helper function to print the content of a node (for testing)
void print_content(void *content) {
    if (content) {
        printf("%s\n", (char *)content);
    } else {
        printf("(null)\n");
    }
}

// Helper function to modify content (append "_modified")
void modify_content(void *content) {
    if (!content)
        return;
    
    char *old_str = (char *)content;  // Treat content as a direct string pointer
    size_t new_len = strlen(old_str) + strlen("_modified") + 1;
    char *new_str = malloc(new_len);
    
    if (!new_str)
        return;
    
    sprintf(new_str, "%s_modified", old_str);
    strcpy(old_str, new_str);  // Copy the modified string back to the original pointer
    free(new_str);  // Free the temporary string
}

void test_ft_lstiter() {
    t_list *head = NULL;

    // Test 1: Iterate over an empty list
    ft_lstiter(head, print_content); // Should not print anything

    // Test 2: Iterate over a list with one element
    head = ft_lstnew(strdup("one"));  // Use strdup here
    printf("Test 2: Original content:\n");
    ft_lstiter(head, print_content);
    printf("Test 2: After iteration (print_content):\n");
    ft_lstiter(head, print_content);
    ft_lstclear(&head, free);  // Use ft_lstclear instead of just free
    head = NULL;

    // Test 3: Iterate over a list with multiple elements
    head = ft_lstnew(strdup("one"));
    head->next = ft_lstnew(strdup("two"));
    head->next->next = ft_lstnew(strdup("three"));

    printf("Test 3: Original content:\n");
    ft_lstiter(head, print_content);
    ft_lstiter(head, modify_content);

    printf("Test 3: After iteration (modify_content):\n");
    ft_lstiter(head, print_content);

    // Cleanup - use ft_lstclear to properly free all nodes and their content
    ft_lstclear(&head, free);
    head = NULL;
    
    printf("✅ test_ft_lstiter passed\n");
}

// Helper function to create a simple list for testing
t_list *create_list(char *s1, char *s2, char *s3) {
    t_list *head = ft_lstnew(s1);
    if (s2) {
        ft_lstadd_back(&head, ft_lstnew(s2));
    }
    if (s3) {
        ft_lstadd_back(&head, ft_lstnew(s3));
    }
    return head;
}

// Helper function to free a list
void ft_lstfree(t_list *lst) {
    t_list *temp;
    while (lst) {
        temp = lst->next;
        free(lst);
        lst = temp;
    }
}

void test_ft_lstlast() {
    t_list *head;
    t_list *last;

    // Test 1: Empty list
    head = NULL;
    last = ft_lstlast(head);
    assert(last == NULL);

    // Test 2: Single-element list
    head = ft_lstnew("one");
    last = ft_lstlast(head);
    assert(last == head);
    assert(last->next == NULL);
    ft_lstfree(head);

    // Test 3: Multi-element list (two elements)
    head = create_list("one", "two", NULL);
    last = ft_lstlast(head);
    assert(last != NULL);
    assert(strcmp((char *)last->content, "two") == 0);
    assert(last->next == NULL);
    ft_lstfree(head);

    // Test 4: Multi-element list (three elements)
    head = create_list("one", "two", "three");
    last = ft_lstlast(head);
    assert(last != NULL);
    assert(strcmp((char *)last->content, "three") == 0);
    assert(last->next == NULL);
    ft_lstfree(head);

    printf("✅ test_ft_lstlast passed\n");
}

void *duplicate_string(void *str) {
    if (!str)
        return NULL;
    return strdup((char *)str);
}

// Helper function to free the duplicated string
void free_duplicated_string(void *str) {
    free(str);
}

void test_ft_lstmap() {
    t_list *head = NULL;
    t_list *mapped_list = NULL;

    // Test 1: Empty list
    printf("Test 1: Empty list\n");
    mapped_list = ft_lstmap(head, duplicate_string, free_duplicated_string);
    assert(mapped_list == NULL);

    // Test 2: Single-element list
    head = ft_lstnew("one");
    printf("\nTest 2: Single-element list\n");
    printf("Original list:\n");
    print_content(head->content);
    mapped_list = ft_lstmap(head, duplicate_string, free_duplicated_string);
    assert(mapped_list != NULL);
    printf("Mapped list:\n");
    print_content(mapped_list->content);
    assert(strcmp((char *)mapped_list->content, "one") == 0);
    ft_lstclear(&head, NULL); // Don't free the string literal
    ft_lstclear(&mapped_list, NULL);

    // Test 3: Multi-element list
    head = ft_lstnew("one");
    ft_lstadd_back(&head, ft_lstnew("two"));
    ft_lstadd_back(&head, ft_lstnew("three"));
    printf("\nTest 3: Multi-element list\n");
    printf("Original list:\n");
    t_list *current = head;
    while (current) {
        print_content(current->content);
        current = current->next;
    }

    mapped_list = ft_lstmap(head, duplicate_string, free_duplicated_string);
    assert(mapped_list != NULL);

    printf("Mapped list:\n");
    current = mapped_list;
    while (current) {
        print_content(current->content);
        current = current->next;
    }

    // Check content of mapped list
    assert(strcmp((char *)((t_list *)mapped_list)->content, "one") == 0);
    assert(strcmp((char *)((t_list *)mapped_list->next)->content, "two") == 0);
    assert(strcmp((char *)((t_list *)mapped_list->next->next)->content, "three") == 0);

    ft_lstclear(&head, NULL); // Don't free string literals
    ft_lstclear(&mapped_list, NULL);

    printf("✅ test_ft_lstmap passed\n");
}

void test_modifier(unsigned int i, char *c)
{
    if (c)
        *c = *c + i;  // Modify the character based on its position
}

void test_ft_striteri(void)
{
    // Test 1: Normal case with modifiable string
    char str[] = "hello";  // Note: using array, not string literal
    printf("Original string: %s\n", str);
    ft_striteri(str, test_modifier);
    printf("Modified string: %s\n", str);

    // Test 2: Empty string
    char empty[] = "";
    ft_striteri(empty, test_modifier);

    // Test 3: NULL string (should not crash)
    ft_striteri(NULL, test_modifier);

    // Test 4: NULL function (should not crash)
    ft_striteri(str, NULL);

    printf("✅ test_ft_striteri passed\n");
}
