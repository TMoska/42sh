/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 04:03:08 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/08 00:54:38 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			get_extention(t_c_tab *list)
{
	struct stat buf;

	if ((lstat(list->content, &buf)) != 0)
		stat(list->content, &buf);
	if (S_ISDIR(buf.st_mode))
		ft_putchar('/');
	else if (S_ISLNK(buf.st_mode))
		ft_putchar('@');
	else if (S_ISSOCK(buf.st_mode))
		ft_putchar('=');
	else if (S_ISFIFO(buf.st_mode))
		ft_putchar('|');
	else if (S_ISWHT(buf.st_mode))
		ft_putchar('%');
	else if (ft_strchr(list->perm, 'x'))
		ft_putchar('*');
	else if (list->perm[0] == 'c')
		ft_putchar('%');
	else if (list->perm[0] == 'b')
		ft_putchar('#');
}

static void		set_color(t_c_tab *list)
{
	if (ft_strncmp(list->perm, "drwxrwxrwxt", 10) == 0)
		ft_putstr(TEMP);
	else if (list->perm[0] == 'p')
		ft_putstr(YELL);
	else if (list->perm[0] == 'd')
		ft_putstr(RED);
	else if (list->perm[0] == 'l')
		ft_putstr(LCYA);
	else if (list->perm[0] == 'c')
		ft_putstr(CHAR);
	else if (list->perm[0] == 's')
		ft_putstr(DGRE);
	else if (list->perm[0] == 'b')
		ft_putstr(CHAR);
	else if (ft_strchr(list->perm, 'x'))
		ft_putstr(LGRE);
	ft_putstr(list->name);
	ft_putstr(NORM);
}

void			ft_print(t_c_tab *list)
{
	set_color(list);
	get_extention(list);
}
