/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 19:27:38 by tmoska            #+#    #+#             */
/*   Updated: 2016/12/07 19:53:14 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			clean_buff(t_rdr *rdr)
{
	int		str_len;
	char	*tmp;

	str_len = (rdr->tot_buff - (rdr->eol - rdr->buff + 1));
	if (!(tmp = (char *)ft_memalloc(str_len + 1)))
		return (0);
	ft_memmove(tmp, &rdr->buff[rdr->eol - rdr->buff + 1], str_len);
	ft_memdel((void **)&rdr->buff);
	rdr->char_buff = ft_strlen(tmp);
	if (!(rdr->buff = (char *)ft_memalloc(sizeof(char) * (rdr->char_buff))))
		return (0);
	if (!(ft_memmove(rdr->buff, tmp, rdr->char_buff)))
		return (0);
	ft_memdel((void **)&(tmp));
	rdr->tot_buff = rdr->char_buff;
	return (1);
}

int			reading_file(t_rdr *rdr, int *cnt, char **line)
{
	char	*tmp;

	if (!(tmp = (char *)ft_memalloc(rdr->char_buff)))
		return (-1);
	ft_memmove(tmp, rdr->buff, rdr->char_buff);
	ft_memdel((void **)&rdr->buff);
	if (!(rdr->buff = (char *)ft_memalloc(rdr->char_buff + BUFF_SIZE)))
		return (-1);
	ft_memmove(rdr->buff, tmp, rdr->char_buff);
	ft_memdel((void **)&(tmp));
	if (!(*cnt = read(rdr->fd, rdr->buff + rdr->char_buff, BUFF_SIZE)))
	{
		rdr->eol = &rdr->buff[rdr->char_buff];
		rdr->stop = 1;
		if (!rdr->tot_buff)
			return (0);
		else
		{
			*line = ft_strnew(rdr->eol - rdr->buff);
			ft_memmove(*line, rdr->buff, rdr->eol - rdr->buff);
			return (1);
		}
	}
	return (2);
}

int			read_buff(t_rdr *rdr, char **line)
{
	int		cnt;
	int		ret;

	while (!(rdr->eol = ft_memchr(rdr->buff, '\n', rdr->char_buff)))
	{
		if (((ret = reading_file(rdr, &cnt, line)) != 2))
			return (ret);
		if (cnt < 0)
			return (-1);
		rdr->char_buff += cnt;
		rdr->tot_buff += cnt;
	}
	*line = ft_strnew(rdr->eol - rdr->buff + 1);
	ft_memmove(*line, rdr->buff, rdr->eol - rdr->buff);
	return (1);
}

t_rdr		*find_reader(t_list **readers, int fd)
{
	t_list	*tmp;
	t_rdr	*rdr;

	tmp = *readers;
	while (tmp)
	{
		rdr = (t_rdr *)(tmp->content);
		if (rdr->fd == fd)
			return ((t_rdr *)(tmp->content));
		tmp = tmp->next;
	}
	if (!(rdr = (t_rdr *)ft_memalloc(sizeof(t_rdr))))
		return (0);
	rdr->fd = fd;
	rdr->stop = 0;
	if (!(tmp = ft_lstnew(rdr, sizeof(t_rdr))))
		return (0);
	ft_lstadd(readers, tmp);
	free(rdr);
	return ((t_rdr *)(tmp->content));
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*readers;
	t_rdr			*rdr;

	if (fd < 0 || !line || !(rdr = find_reader(&readers, fd)))
		return (-1);
	if (rdr->stop)
		return (0);
	if (rdr->buff && !(clean_buff(rdr)))
		return (-1);
	return (read_buff(rdr, line));
}
