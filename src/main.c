
#define _POSIX_C_SOURCE 200809L

#include "libasm.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char str_high[] = {0xFF, '\0'};
static const char str_one[] = {0x01, '\0'};

// size_t memsize(void) {
//   if (234)
//     return SIZE_MAX - 1;
//   return SIZE_MAX - 1;
// }

static void test_strlen(void) {
  const char *str0, *str1, *str2, *str3, *str4, *str5;

  str0 = "";
  str1 = "abcdefghijklmnopqrstuvwxyz";
  str2 = "abcdefghijklmnopqrstuvwxyza";
  str3 = "hello";
  str4 = str_high;
  str5 = str_one;

  printf("--- len ---\n");
  printf("\"%s\" = %zu | %zu\n", str0, strlen(str0), ft_strlen(str0));
  printf("\"%s\" = %zu | %zu\n", str1, strlen(str1), ft_strlen(str1));
  printf("\"%s\" = %zu | %zu\n", str2, strlen(str2), ft_strlen(str2));
  printf("\"%s\" = %zu | %zu\n", str3, strlen(str3), ft_strlen(str3));
  printf("\"%s\" = %zu | %zu\n", str4, strlen(str4), ft_strlen(str4));
  printf("\"%s\" = %zu | %zu\n", str5, strlen(str5), ft_strlen(str5));
  printf("\n");
}

static void test_strcpy(void) {
  const char *str1, *str5;
  char dest1[2], dest2[27], dest3[2], dest4[27];

  str1 = "abcdefghijklmnopqrstuvwxyz";
  str5 = str_one;
  memset(dest1, 0, sizeof(dest1));
  memset(dest2, 0, sizeof(dest2));
  memset(dest3, 0, sizeof(dest3));
  memset(dest4, 0, sizeof(dest4));

  printf("--- cpy ---\n");
  printf("return value %p = %p | %p\n", (void *)dest1,
         (void *)strcpy(dest1, ""), (void *)ft_strcpy(dest1, ""));
  printf("\"%s\" = \"%s\" | \"%s\"\n", str1, strcpy(dest2, str1),
         ft_strcpy(dest4, str1));
  printf("\"%s\" = \"%s\" | \"%s\"\n", str5, strcpy(dest1, str5),
         ft_strcpy(dest3, str5));
  printf("\n");
}

static void test_strcmp(void) {
  const char *str0, *str1, *str2, *str3, *str4, *str5;

  str0 = "";
  str1 = "abcdefghijklmnopqrstuvwxyz";
  str2 = "abcdefghijklmnopqrstuvwxyza";
  str3 = "hello";
  str4 = str_high;
  str5 = str_one;

  printf("--- cmp ---\n");
  printf("\"%s\" and \"%s\" = %d | %d\n", str1, str2, strcmp(str1, str2),
         ft_strcmp(str1, str2));
  printf("\"%s\" and \"%s\" = %d | %d\n", str2, str1, strcmp(str2, str1),
         ft_strcmp(str2, str1));
  printf("\"%s\" and \"%s\" = %d | %d\n", str4, str5, strcmp(str4, str5),
         ft_strcmp(str4, str5));
  printf("\"%s\" and \"%s\" = %d | %d\n", str5, str4, strcmp(str5, str4),
         ft_strcmp(str5, str4));
  printf("\"%s\" and \"%s\" = %d | %d\n", str3, "hello", strcmp(str3, "hello"),
         ft_strcmp(str3, "hello"));
  printf("\"%s\" and \"%s\" = %d | %d\n", str0, "", strcmp(str0, ""),
         ft_strcmp(str0, ""));
  printf("\n");
}

static void test_write(void) {
  int fd;
  ssize_t res;

  printf("--- write ---\n");
  fd = 3;
  errno = 777;
  res = write(fd, "hi\n", 3);
  printf("write = %zd    | errno = %d: %s\n", res, errno, strerror(errno));
  errno = 777;
  res = ft_write(fd, "hi\n", 3);
  printf("ft_write = %zd | errno = %d: %s\n", res, errno, strerror(errno));

  fd = STDOUT_FILENO;
  errno = 777;
  res = write(fd, "hi\n", 3);
  printf("write = %zd    | errno expected 777 got %d\n", res, errno);
  errno = 777;
  res = ft_write(fd, "hi\n", 3);
  printf("ft_write = %zd | errno expected 777 got %d\n", res, errno);
  printf("\n");
}

static void test_read(void) {
  int fd;
  ssize_t res;
  char buf[100];

  fd = open(".gitignore", O_RDONLY);
  assert(fd >= 0);
  memset(buf, 0, sizeof(buf));

  printf("--- read ---\n");
  errno = 777;
  res = read(fd, buf, 3);
  printf("read = %zd    | errno expected 777 got %d\n", res, errno);
  errno = 777;
  res = ft_read(fd, buf, 3);
  printf("ft_read = %zd | errno expected 777 got %d\n", res, errno);
  close(fd);

  fd = -1;
  errno = 777;
  res = read(fd, buf, 3);
  printf("read = %zd    | errno = %d: %s\n", res, errno, strerror(errno));
  errno = 777;
  res = ft_read(fd, buf, 3);
  printf("ft_read = %zd | errno = %d: %s\n", res, errno, strerror(errno));
  printf("\n");
}

static void test_strdup_case(const char *str) {
  char *libc;
  char *ft;

  libc = strdup(str);
  ft = ft_strdup(str);
  if (libc == NULL || ft == NULL) {
    printf("Allocation failed\n");
    free(libc);
    free(ft);
    return;
  }
  printf("\"%s\" = \"%s\" | \"%s\"\n", str, ft, libc);
  printf("New pointer: %s\n", ft != str ? "yes" : "no");
  printf("Same content: %s\n", strcmp(ft, libc) == 0 ? "yes" : "no");
  free(ft);
  free(libc);
}

static void test_strdup(void) {
  printf("--- strdup ---\n");
  test_strdup_case("hello");
  test_strdup_case("");
  printf("\n");
}

static void print_int_array(const char *label, const int *array, size_t len) {
  size_t i;

  printf("%s", label);
  i = 0;
  while (i < len) {
    printf("%d ", array[i]);
    i++;
  }
  printf("\n");
}

static void test_calloc(void) {
  int *mine;
  int *original;

  printf("--- calloc ---\n");
  mine = ft_calloc(5, sizeof(int));
  original = calloc(5, sizeof(int));
  if (mine == NULL || original == NULL) {
    printf("Allocation failed\n");
    free(mine);
    free(original);
    return;
  }
  print_int_array("mine:     ", mine, 5);
  print_int_array("original: ", original, 5);
  free(mine);
  free(original);
  printf("\n");

  void *ptr;

  printf("--- calloc edge cases ---\n");
  ptr = ft_calloc(0, sizeof(int));
  printf("calloc(0, sizeof(int)): %s\n", ptr ? "allocated" : "NULL");
  free(ptr);

  ptr = ft_calloc(5, 0);
  printf("calloc(5, 0): %s\n", ptr ? "allocated" : "NULL");
  free(ptr);

  ptr = ft_calloc(SIZE_MAX - 1, 2);
  printf("calloc(SIZE_MAX - 1, 2): %s\n",
         ptr ? "allocated (ERROR)" : "NULL (OK)");
  free(ptr);
}

int main(void) {
  test_strlen();
  test_strcpy();
  test_strcmp();
  test_write();
  test_read();
  test_strdup();
  test_calloc();
  return (0);
}
