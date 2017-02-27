/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 16:33:19 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/27 22:39:58 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <sys/types.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <dirent.h>
# include "libft.h"
# include <sys/stat.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <unistd.h>

typedef char		t_bool;

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

size_t				ft_strlen(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big,
					const char *little, size_t len);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strdup(char *src);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src,
					size_t size);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *c);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void**, size_t*));
void				ft_lstdel(t_list **alst, void (*del)(void**, size_t*));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstrev(t_list **begin_list);
void				ft_lstsort(t_list **begin_list, int (*cmp)());
int					ft_lstsize(t_list *begin);
void				ft_lstforeach(t_list *begin_list, void (*f)(void *));
void				ft_lstmerge(t_list **begin_list1, t_list *begin_list2);
void				ft_lstrmif(t_list **begin_list,
					void *data_ref, int (*cmp)());
t_list				*ft_lst_create_elem(void *data);
void				ft_lst_removenode(t_list **begin_list, t_list *removable);
void				ft_lst_remove_if(t_list **begin_list, void *content,\
		int (*cmp)());
int					ft_ptrequ(const void *one, const void *two);
char				*ft_get_path(char *folder_name);
char				*ft_basename(char *folder_name);
char				*ft_itoa(int n);
char				*ft_itoa_ularge(unsigned long long number);
int					ft_count_umax_digits(uintmax_t number);
void				ft_put_justified_str(char *str, size_t tot_size,\
		char fill, t_bool right);
void				ft_put_justified_nbr(int nb, size_t tot_size,\
		char fill, t_bool right);
void				ft_putchar_if(int condition, char pos, char neg);
int					ft_lst_in_list(t_list *begin_list, void *data,\
		int (*cmp)());
int					ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lst_clear(void **list_content, size_t *content_size);
int					ft_char_arr_len(char **arr);
int					ft_strisblank(char *str);
void				ft_str2del(char ***tab);
size_t				ft_str2len(char **tab);
char				**ft_str2new(size_t size);
char				**ft_str2dup(char **str);
int					get_next_line(const int fd, char **line);
char				*ft_str3join(char *s1, char *s2, char *s3);
size_t				ft_strlen_until(const char *str, char c);
char				**ft_str2join(char **s1, char **s2);
char				*ft_strtrim_char(char const *s, char c);
char				*ft_strndelat(char *str, int index, size_t size);
char				*ft_strndup(char *src, size_t size);
#endif
