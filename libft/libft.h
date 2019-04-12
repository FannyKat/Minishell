/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:17:01 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/12 10:38:10 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 100
# define OPEN_MAX 4096

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <dirent.h>
# include <stdio.h>

typedef struct		s_printf
{
	int				flag;
	void			(*f)(va_list*);
}					t_printf;

typedef struct		s_list
{
	void			*content;
	void			*data;
	size_t			size;
	struct s_list	*next;
}					t_list;

char				**realloc_tab(char **array, int len);
void				ft_tabfree(char **array);
char				**ft_tabcopy(char **tab_dest, char **tab_copy);
void				print_tab(char **array);
int					ft_tablen(char **array);
int					isstart(char *s1, char *s2);
int					ft_isupper(int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
void				*ft_memset(void *b, int c, size_t len);
void				ft_memdel(void **ap);
void				ft_bzero(void *s1, size_t n);
void				*ft_memcpy(void *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
size_t				ft_strlen(const char *s);
size_t				strlen_to(const char *s, char c);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, int n);
char				*strdupfree(char *s1);
char				*ft_strcpy(char *s1, const char *s2);
char				*ft_strncpy(char *s1, const char *s2, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isspace(int c);
int					ft_isblank(int c);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoinclr(char *s1, char *s2, int xfree);
char				*ft_strnjoinclr(char *s1, char *s2, size_t n, int free_s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void(*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void(*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_swap(int *a, int *b);
int					get_next_line(const int fd, char **line);
t_list				*ft_xlstadd(void *data);
void				my_printf(char *format, ...);
void				fun_s(va_list *ap);
void				fun_c(va_list *ap);
void				fun_d(va_list *ap);
char				**ft_split(char *s);

#endif
