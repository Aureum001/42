#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

// Include the appropriate header based on whether we're testing bonus
#ifdef BONUS
    #include "get_next_line_bonus.h"
#else
    #include "get_next_line.h"
#endif

// Simple assertion macro
#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s\n", message); \
            return 0; \
        } else { \
            printf("PASS: %s\n", message); \
        } \
    } while(0)

// Test basic functionality
int test_basic_read(void)
{
    int fd;
    char *line;
    
    printf("\n--- Testing basic read functionality ---\n");
    
    // Create test file
    fd = open("test_file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    write(fd, "Line 1\nLine 2\nLine 3", 20);
    close(fd);
    
    // Test reading
    fd = open("test_file.txt", O_RDONLY);
    
    line = get_next_line(fd);
    TEST_ASSERT(line != NULL, "First line should not be NULL");
    TEST_ASSERT(strcmp(line, "Line 1\n") == 0, "First line content");
    free(line);
    
    line = get_next_line(fd);
    TEST_ASSERT(line != NULL, "Second line should not be NULL");
    TEST_ASSERT(strcmp(line, "Line 2\n") == 0, "Second line content");
    free(line);
    
    line = get_next_line(fd);
    TEST_ASSERT(line != NULL, "Third line should not be NULL");
    TEST_ASSERT(strcmp(line, "Line 3") == 0, "Third line content (no newline)");
    free(line);
    
    line = get_next_line(fd);
    TEST_ASSERT(line == NULL, "Fourth call should return NULL");
    
    close(fd);
    unlink("test_file.txt");
    return 1;
}

// Test empty file
int test_empty_file(void)
{
    int fd;
    char *line;
    
    printf("\n--- Testing empty file ---\n");
    
    fd = open("empty.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    close(fd);
    
    fd = open("empty.txt", O_RDONLY);
    line = get_next_line(fd);
    TEST_ASSERT(line == NULL, "Empty file should return NULL");
    
    close(fd);
    unlink("empty.txt");
    return 1;
}

// Test file with only newlines
int test_only_newlines(void)
{
    int fd;
    char *line;
    
    printf("\n--- Testing file with only newlines ---\n");
    
    fd = open("newlines.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    write(fd, "\n\n\n", 3);
    close(fd);
    
    fd = open("newlines.txt", O_RDONLY);
    
    line = get_next_line(fd);
    TEST_ASSERT(line != NULL && strcmp(line, "\n") == 0, "First newline");
    free(line);
    
    line = get_next_line(fd);
    TEST_ASSERT(line != NULL && strcmp(line, "\n") == 0, "Second newline");
    free(line);
    
    line = get_next_line(fd);
    TEST_ASSERT(line != NULL && strcmp(line, "\n") == 0, "Third newline");
    free(line);
    
    line = get_next_line(fd);
    TEST_ASSERT(line == NULL, "Should return NULL after all newlines");
    
    close(fd);
    unlink("newlines.txt");
    return 1;
}

// Test invalid file descriptor (safer version)
int test_invalid_fd(void)
{
    char *line;
    
    printf("\n--- Testing invalid file descriptors ---\n");
    
    printf("DEBUG: Testing fd -1...\n");
    line = get_next_line(-1);
    TEST_ASSERT(line == NULL, "Invalid fd (-1) should return NULL");
    
    printf("DEBUG: Invalid fd tests completed\n");
    return 1;
}

// Test multiple file descriptors (bonus feature)
int test_multiple_fds(void)
{
    int fd1, fd2;
    char *line1, *line2;
    
    printf("\n--- Testing multiple file descriptors ---\n");
    
    // Create first file
    fd1 = open("file1.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    write(fd1, "File1Line1\nFile1Line2\n", 22);
    close(fd1);
    
    // Create second file
    fd2 = open("file2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    write(fd2, "File2Line1\nFile2Line2\n", 22);
    close(fd2);
    
    // Open both files
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    
    printf("DEBUG: fd1=%d, fd2=%d\n", fd1, fd2);
    
    // Read from both files alternately
    line1 = get_next_line(fd1);
    printf("DEBUG: line1='%s'\n", line1 ? line1 : "NULL");
    TEST_ASSERT(line1 != NULL && strcmp(line1, "File1Line1\n") == 0, "File1 first line");
    
    line2 = get_next_line(fd2);
    printf("DEBUG: line2='%s'\n", line2 ? line2 : "NULL");
    if (line2 == NULL) {
        printf("DEBUG: File2 returned NULL - this suggests multiple FD support is not working\n");
        free(line1);
        close(fd1);
        close(fd2);
        unlink("file1.txt");
        unlink("file2.txt");
        return 0;
    }
    TEST_ASSERT(line2 != NULL && strcmp(line2, "File2Line1\n") == 0, "File2 first line");
    
    free(line1);
    free(line2);
    
    line1 = get_next_line(fd1);
    TEST_ASSERT(line1 != NULL && strcmp(line1, "File1Line2\n") == 0, "File1 second line");
    
    line2 = get_next_line(fd2);
    TEST_ASSERT(line2 != NULL && strcmp(line2, "File2Line2\n") == 0, "File2 second line");
    
    free(line1);
    free(line2);
    
    close(fd1);
    close(fd2);
    unlink("file1.txt");
    unlink("file2.txt");
    return 1;
}

int main(void)
{
    // int passed = 0;
    // int total = 0;
    
    // #ifdef BONUS
    //     printf("=== GET_NEXT_LINE BONUS TESTS ===\n");
    // #else
    //     printf("=== GET_NEXT_LINE TESTS ===\n");
    // #endif
    
    // total++; if (test_basic_read()) passed++;
    // total++; if (test_empty_file()) passed++;
    // total++; if (test_only_newlines()) passed++;
    // total++; if (test_invalid_fd()) passed++;
    
    // #ifdef BONUS
    //     total++; if (test_multiple_fds()) passed++;
    // #else
    //     printf("\n--- Skipping multiple FD test (not bonus) ---\n");
    // #endif
    
    // printf("\n=== TEST RESULTS ===\n");
    // printf("Passed: %d/%d\n", passed, total);
    
    // if (passed == total) {
    //     printf("All tests PASSED! 🎉\n");
    //     return 0;
    // } else {
    //     printf("Some tests FAILED! ❌\n");
    //     return 1;
    // }
	int fd;
	char *line;
	fd = open("texto.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}