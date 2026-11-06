#ifndef LIBASM
#define LIBASM

#include <unistd.h>

extern size_t ft_strlen(const char *str);
extern char *ft_strcpy(char *dst, const char *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const void *buf, size_t count);
extern ssize_t ft_read(int fd, const void *buf, size_t count);
extern char *ft_strdup(const char *s);
extern void *ft_calloc(size_t n, size_t size);

#endif