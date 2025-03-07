/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <antonioayr.94@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:37:39 by ancanale          #+#    #+#             */
/*   Updated: 2025/03/03 19:37:39 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	if (!*s2)
		return ((char *)s1);
	while (*s1 && n)
	{
		if (*s1 == *s2)
		{
			i = 0;
			while (s2[i]
					&& s1[i] == s2[i]
					&& i < n)
				i++;
			if (!s2[i])
				return ((char *)s1);
		}
		n--;
		s1++;
	}
	return (NULL);
}

/*
int main(void)
{
    const char *s1 = "Hello, World!";
    const char *s2 = "World";
    const char *s3 = "Hello";
    const char *s4 = "!";
    const char *s5 = "";
    const char *s6 = "Foo";
    const char *s7 = "Hello, World! This is a test.";
    const char *s8 = "test";
    const char *s9 = "Hello, World!";
    const char *s10 = "Hello, World!";

    // Test cases
    printf("Test 1: %s\n", ft_strnstr(s1, s2, 13) ? ft_strnstr(s1, s2, 13) : "NULL"); // Expected: "World!"
    printf("Test 2: %s\n", ft_strnstr(s1, s3, 13) ? ft_strnstr(s1, s3, 13) : "NULL"); // Expected: "Hello, World!"
    printf("Test 3: %s\n", ft_strnstr(s1, s4, 13) ? ft_strnstr(s1, s4, 13) : "NULL"); // Expected: "!"
    printf("Test 4: %s\n", ft_strnstr(s1, s5, 13) ? ft_strnstr(s1, s5, 13) : "NULL"); // Expected: "Hello, World!"
    printf("Test 5: %s\n", ft_strnstr(s1, s6, 13) ? ft_strnstr(s1, s6, 13) : "NULL"); // Expected: "NULL"
    printf("Test 6: %s\n", ft_strnstr(s7, s8, 30) ? ft_strnstr(s7, s8, 30) : "NULL"); // Expected: "test."
    printf("Test 7: %s\n", ft_strnstr(s9, s10, 5) ? ft_strnstr(s9, s10, 5) : "NULL"); // Expected: "NULL" (n too small)
    printf("Test 8: %s\n", ft_strnstr(NULL, s2, 13) ? ft_strnstr(NULL, s2, 13) : "NULL"); // Expected: "NULL"
    printf("Test 9: %s\n", ft_strnstr(s1, NULL, 13) ? ft_strnstr(s1, NULL, 13) : "NULL"); // Expected: "NULL"
    printf("Test 10: %s\n", ft_strnstr(s1, s2, 0) ? ft_strnstr(s1, s2, 0) : "NULL"); // Expected: "NULL" (n is 0)

    return 0;
}
*/