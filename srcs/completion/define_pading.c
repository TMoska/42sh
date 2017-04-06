/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_pading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/04/06 02:53:09 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_c_tab			*tpad(t_c_tab *tmp, struct s_pad *pad)
{
	size_t				len;

	len = ft_strlen(tmp->content);
	(len > (*pad).len_x ? (*pad).len_x = len : (*pad).len_x);
	tmp->place = (*pad).line_s++;
	tmp->col = (*pad).col_s;
	tmp->page = (*pad).page_s;
	return (tmp);
}

static t_c_tab			*treat_pading(t_c_tab *list, struct s_pad pad)
{
	t_c_tab				*tmp;
	size_t				total_len;

	tmp = list;
	total_len = 0;
	while (tmp)
	{
		pad.line_s = 1;
		pad.len_x = 0;
		while (tmp && (pad.line_s <= pad.len_y))
		{
			tmp = tpad(tmp, &pad);
			tmp = tmp->next;
		}
		total_len += pad.len_x + 3;
		if (total_len >= pad.max_x - 20)
		{
			total_len = 0;
			pad.col_s = 0;
			pad.page_s++;
		}
		pad.col_s++;
	}
	return (list);
}

static struct s_pad		init_pading(size_t nb_files, struct winsize w,
		t_c_tab *tmp)
{
	struct s_pad		pad;
	size_t				max_len;
	size_t				opt_y;

	pad = start_pad(w, nb_files);
	opt_y = 0;
	if ((pad.len_y = ((nb_files / pad.cols))) > pad.max_y)
		pad.len_y = pad.max_y;
	if (pad.len_y <= 5)
	{
		while (tmp)
		{
			max_len = 0;
			while (tmp && max_len < pad.max_x - 2)
				if ((max_len += ft_strlen(tmp->content) + 3) < pad.max_x - 5)
					tmp = tmp->next;
			opt_y++;
		}
		(!tmp ? pad.len_y = opt_y : pad.len_y);
	}
	if (pad.len_y > pad.max_y + 4)
		pad.len_y = pad.max_y + 4;
	return (pad);
}

static size_t			too_much_file(t_c_tab *list, size_t i, size_t key)
{
	char				*buff[5];

	ft_putstr(tgetstr("vi", NULL));
	while (list && list->next)
	{
		list = list->next;
		i++;
	}
	if (i > 99)
	{
        put_question(i);
        ft_memset(buff, 0, 5);
		while (read(0, buff, 5) && (key = (unsigned int)*buff) != BTN_Y &&
				key != BTN_N && key != BTN_TAB && key != BTN_BACK)
			ft_memset(buff, 0, 5);
		DEL_LINES;
        MOVE_DOWN;
		return (((unsigned int)*buff == BTN_Y || (unsigned int)*buff == BTN_TAB)
				? (i) : (0));
	}
	return (i);
}

t_c_tab					*define_pading(t_c_tab *list, size_t *val)
{
	size_t				nb_files;
    size_t              key;
    size_t              i;
	struct s_pad		pad;
	struct winsize		w;

	nb_files = 0;
    key = 0;
    i = 1;
    if (!list || ((nb_files = too_much_file(list, i, key)) == 0))
		return (NULL);
    if (nb_files < 2)
        (*val) = 69;
	ioctl(0, TIOCGWINSZ, &w);
	pad = init_pading(nb_files, w, list);
	list = treat_pading(list, pad);
    if (list)
        list->cursor = 1;
	return (list);
}
