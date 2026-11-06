#include "../include/libasm.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <assert.h>

size_t memsize(void) { 
    if (234) { 
        return SIZE_MAX - 1;
    }
    return SIZE_MAX - 1;
}

int main(void) {
    const char str0[] = "";
    const char str1[] = "abcdefghijklmnopqrstuvwxyz";
    const char str2[] = "abcdefghijklmnopqrstuvwxyza";
    const char str3[] = "hello";
    const char str4[] = {0xFF, 0x00};
    const char str5[] = {0x01, 0x00};
    const char str6[] = "hello";
    const char str7[] = "";

    char dest1[2];
    bzero(dest1, sizeof(dest1));
    char dest2[27];
    bzero(dest2, sizeof(dest2));
    char dest3[2];
    bzero(dest3, sizeof(dest3));
    char dest4[27];
    bzero(dest4, sizeof(dest4));

    printf("--- len ---\n");
    printf("\"%s\" = %zu | %zu\n", str0, strlen(str0), ft_strlen(str0));
    printf("\"%s\" = %zu | %zu\n", str1, strlen(str1), ft_strlen(str1));
    printf("\"%s\" = %zu | %zu\n", str2, strlen(str2), ft_strlen(str2));
    printf("\"%s\" = %zu | %zu\n", str3, strlen(str3), ft_strlen(str3));
    printf("\"%s\" = %zu | %zu\n", str4, strlen(str4), ft_strlen(str4));
    printf("\"%s\" = %zu | %zu\n", str5, strlen(str5), ft_strlen(str5));
    printf("\n");
    

    printf("--- cpy ---\n");
    printf("return value %p = %p | %p\n", &dest1, strcpy(dest1, ""), ft_strcpy(dest1, ""));
    printf("\"%s\" = \"%s\" | \"%s\" \n", str1, strcpy(dest2, str1), ft_strcpy(dest4, str1));
    printf("\"%s\" = \"%s\" | \"%s\" \n", str5, strcpy(dest1, str5), ft_strcpy(dest3, str5));
    printf("\n");

    
    printf("--- cmp ---\n");
    printf("\"%s\" and \"%s\" = %d | %d\n", str1, str2, strcmp(str1, str2), ft_strcmp(str1, str2));
    printf("\"%s\" and \"%s\" = %d | %d\n", str2, str1, strcmp(str2, str1), ft_strcmp(str2, str1));
    printf("\"%s\" and \"%s\" = %d | %d\n", str4, str5, strcmp(str4, str5), ft_strcmp(str4, str5));
    printf("\"%s\" and \"%s\" = %d | %d\n", str5, str4, strcmp(str5, str4), ft_strcmp(str5, str4));
    printf("\"%s\" and \"%s\" = %d | %d\n", str3, str6, strcmp(str3, str6), ft_strcmp(str3, str6));
    printf("\"%s\" and \"%s\" = %d | %d\n", str0, str7, strcmp(str0, str7), ft_strcmp(str0, str7));
    printf("\n");


    int fd;
    ssize_t res;

    printf("--- write ---\n");
    fd = 3;
    errno = 777;
    res = write(fd, "hi\n", 3);
    printf("write = %zu    | errno = %d: %s\n", res, errno, strerror(errno));
    errno = 777;
    res = ft_write(fd, "hi\n", 3);
    printf("ft_write = %zu | errno = %d: %s\n", res, errno, strerror(errno));

    fd = STDOUT_FILENO;
    errno = 777;
    res = write(fd, "hi\n", 3);
    printf("write = %zu    | errno expected 777 got %d\n", res, errno);
    errno = 777;
    res = ft_write(fd, "hi\n", 3);
    printf("ft_write = %zu | errno expected 777 got %d\n", res, errno); 
    printf("\n");


    char buf[100];
    bzero(buf, sizeof(buf));

    printf("--- read ---\n");
    fd = -1;
    fd = open(".gitignore", O_RDONLY, 0);
    assert(fd > STDERR_FILENO);
    errno = 777;
    res = read(fd, &buf, 3);
    printf("read = %zu    | errno expected 777 got %d\n", res, errno);
    errno = 777;
    res = read(fd, &buf, 3);
    printf("ft_read = %zu | errno expected 777 got %d\n", res, errno);

    fd = 5;
    errno = 777;
    res = read(fd, &buf, 3);
    printf("read = %zu    | errno = %d: %s\n", res, errno, strerror(errno));
    errno = 777;
    res = ft_read(fd, &buf, 3);
    printf("ft_read = %zu | errno = %d: %s\n", res, errno, strerror(errno)); 
    printf("\n");

    
    char *libc;
    char *ft;

    printf("--- strdup ---\n");

	libc = strdup(str6);
	ft = ft_strdup(str6);
	printf("\"%s\" = \"%s\" | \"%s\"\n", str6, ft, libc);
	printf("New pointer: %s\n", ft != str6 ? "yes" : "no");
	printf("Same content: %s\n", strcmp(ft, libc) == 0 ? "yes" : "no");
	free(ft);
	free(libc);

	libc = strdup(str0);
	ft = ft_strdup(str0);
	printf("\"%s\" = \"%s\" | \"%s\"\n", str0, ft, libc);
	free(ft);
	free(libc);
    printf("\n");


	int		*mine;
	int		*original;
	size_t	i;

	printf("--- calloc ---\n");

	mine = ft_calloc(5, sizeof(int));
	original = calloc(5, sizeof(int));

	printf("mine:     ");
	i = 0;
	while (i < 5)
	{
		printf("%d ", mine[i]);
		i++;
	}
	printf("\noriginal: ");
	i = 0;
	while (i < 5)
	{
		printf("%d ", original[i]);
		i++;
	}
	printf("\n");

	free(mine);
	free(original);


    void	*ptr;

	printf("--- calloc edge cases ---\n");

	ptr = ft_calloc(0, sizeof(int));
	printf("calloc(0, sizeof(int)): %s\n",
		ptr ? "allocated" : "NULL");
	free(ptr);

	ptr = ft_calloc(5, 0);
	printf("calloc(5, 0): %s\n",
		ptr ? "allocated" : "NULL");
	free(ptr);

	ptr = ft_calloc(SIZE_MAX - 1, 2);
	printf("calloc(SIZE_MAX, 2): %s\n",
		ptr ? "allocated (ERROR)" : "NULL (OK)");
    free(ptr);

    return 0;
}