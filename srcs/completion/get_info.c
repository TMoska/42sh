/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 04:48:53 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/07 09:24:02 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_has_acl(t_c_tab *list)
{
	char		res;
	struct stat buf;
	acl_t		acl;

	res = 0;
	if ((lstat(list->content, &buf) != 0))
		stat(list->content, &buf);
	acl = acl_get_link_np(list->content, ACL_TYPE_EXTENDED);
	if (acl != NULL)
	{
		if (buf.st_mode & S_ISVTX)
			list->perm[9] = 't';
		else if (buf.st_mode & S_IXOTH)
			list->perm[9] = 'x';
		list->perm[10] = '+';
		res = 1;
	}
	acl_free(acl);
	return (res);
}

void			get_acl(t_c_tab *list)
{
	struct stat buf;

	if (!(stat(list->content, &buf)))
		if (!(lstat(list->content, &buf)))
			return ;
	if (listxattr(list->content, NULL, 0, XATTR_NOFOLLOW) > 0)
	{
		if (buf.st_mode & S_ISVTX)
			list->perm[9] = 't';
		else if (buf.st_mode & S_IXOTH)
			list->perm[9] = 'x';
		list->perm[10] = '@';
		return ;
	}
	if (ft_has_acl(list))
		return ;
	if (buf.st_mode & S_ISVTX)
		list->perm[9] = 't';
	else if (buf.st_mode & S_IXOTH)
		list->perm[9] = 'x';
}

void			get_info(t_c_tab *list)
{
	struct stat		buf;

	list->perm = ft_strnew(13);
	ft_memset(list->perm, '-', 11);
	stat(list->content, &buf);
	((!readlink(list->content, NULL, 0)) && lstat(list->content, &buf));
	((S_ISLNK(buf.st_mode)) && (list->perm[0] = 'l'));
	((S_ISDIR(buf.st_mode)) && (list->perm[0] = 'd'));
	((S_ISCHR(buf.st_mode)) && (list->perm[0] = 'c'));
	((S_ISBLK(buf.st_mode)) && (list->perm[0] = 'b'));
	((S_ISSOCK(buf.st_mode)) && (list->perm[0] = 's'));
	((S_ISFIFO(buf.st_mode)) && (list->perm[0] = 'p'));
	((buf.st_mode & S_IRUSR) && (list->perm[1] = 'r'));
	((buf.st_mode & S_IWUSR) && (list->perm[2] = 'w'));
	((buf.st_mode & S_IXUSR) && (list->perm[3] = 'x'));
	((buf.st_mode & S_IRGRP) && (list->perm[4] = 'r'));
	((buf.st_mode & S_IWGRP) && (list->perm[5] = 'w'));
	((buf.st_mode & S_IXGRP) && (list->perm[6] = 'x'));
	((buf.st_mode & S_IROTH) && (list->perm[7] = 'r'));
	((buf.st_mode & S_IWOTH) && (list->perm[8] = 'w'));
	((buf.st_mode & S_IXOTH) && (list->perm[9] = 'x'));
	list->perm[12] = '\0';
	get_acl(list);
}
