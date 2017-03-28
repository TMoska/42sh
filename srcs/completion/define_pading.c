/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_pading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/03/28 23:02:23 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static c_tab			*tpad(c_tab *tmp, struct d_pad *pad, size_t len)
{
	(len > (*pad).len_x ? (*pad).len_x = len : (*pad).len_x);
	tmp->place = (*pad).line_s++;
	tmp->col = (*pad).col_s;
	tmp->page = (*pad).page_s;
	return (tmp);
}

static c_tab			*treat_pading(c_tab *list, struct d_pad pad)
{
	c_tab      		*tmp;
	size_t			len;
	size_t			total_len;

	tmp = list;
	total_len = 0;
	while (tmp)
	{
		pad.line_s = 1;
		pad.len_x = 0;
		pad.line_s = 1;
		while (tmp && pad.line_s <= pad.len_y)
		{
			len = ft_strlen(tmp->content);
			tmp = tpad(tmp, &pad, len);
			tmp = tmp->next;
		}
		total_len += pad.len_x;
		if (total_len >= pad.max_x - 50)
		{
			total_len = 0;
			pad.col_s = 0;
			pad.page_s++;
		}
		pad.col_s++;
	}
	return (list);
}

static struct d_pad init_pading(size_t nb_files, struct winsize w)
{
    struct d_pad	pad;
    size_t			cols;

    cols = 2;
    pad.line_s = 1;
    pad.col_s = 1;
    pad.page_s = 1;
    pad.max_x = w.ws_col - 2;
    pad.max_y = 10;
    while (nb_files > (pad.max_y * (cols)))
        cols++;
    pad.len_x = 0;
    pad.len_y = ((nb_files / cols));
    if (pad.len_y > pad.max_y)
        pad.len_y = pad.max_y;
    return (pad);
}

static size_t   too_much_file(c_tab *list, t_shell *shell)
{
    size_t      i;
    char        buff[1];

    i = 1;
    while (list && list->next)
    {
        list = list->next;
        i++;
    }
    (void)shell;
    if (i > 25)
    {
        SAVE_LINE;
        MOVE_DOWN;
        DEL_LINES;
        LOAD_LINE;
        ft_putstr(tgetstr("vi", NULL));
        ft_putstr("\033[1;91mBro, there is a lot of possibilities O.O like ");
        ft_putnbr(i);
        ft_putstr(" possibilities O.O Are you sure about that? (y or n)\033[0m");
        while (buff[0] != 'y' && buff[0] != 'n')
            i = read(0, buff, 1);
        ft_putstr(tgetstr("ve", NULL));
        if (buff[0] == 'y')
            return (i);
        else if (buff[0] == 'n')
            return (0);
    }
    return (i);
}

c_tab           *define_pading(c_tab *list, t_shell *shell)
{
    size_t          nb_files;
    struct d_pad    pad;
    struct winsize  w;

    nb_files = 0;
    if (list && ((nb_files = too_much_file(list, shell)) == 0))
        return (NULL);
    ioctl(0, TIOCGWINSZ, &w);
    pad = init_pading(nb_files, w);
    list = treat_pading(list, pad);
    return (list);
}
