/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/03/31 04:40:39 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_pad		start_pad(struct winsize w, size_t nb_files)
{
	struct s_pad	pad;

	pad.line_s = 1;
	pad.col_s = 1;
	pad.page_s = 1;
	pad.pages = 1;
	pad.cols = 1;
	pad.max_x = w.ws_col - 2;
	pad.max_y = 10;
	while (nb_files > pad.cols * pad.pages)
		(pad.cols < 5 ? pad.cols++ : pad.pages++);
	pad.len_x = 0;
	return (pad);
}

static size_t		verify_btn(unsigned int key)
{
	if (key == BTN_UP)
		return (8);
	else if (key == BTN_RIGHT || key == BTN_TAB)
		return (6);
	else if (key == BTN_LEFT || key == BTN_S_TAB)
		return (4);
	else if (key == BTN_DOWN)
		return (2);
	else if (key == BTN_BACK)
		return (9);
	else if (key == BTN_ENTER)
		return (1);
	return (0);
}

void				put_tab(t_c_tab *list, t_shell **shell, size_t val)
{
	char			*res;
	char			*tmp;
	size_t			i;

	tmp = NULL;
	if (val == 1)
	{
		while (list && list->cursor != 1)
			list = list->next;
		i = ft_strlen((*shell)->buff);
		while (i > 0 && (*shell)->buff[i] != ' ')
			i--;
		if (i != 0)
			tmp = ft_strsub((*shell)->buff, 0, i + 1);
		clear_cmdline(shell);
		ft_bzero((*shell)->buff, ft_strlen((*shell)->buff));
		reset_line(shell);
		res = ft_str3join(tmp, list->content, " ");
		ft_strdel(&tmp);
		work_buffer(shell, res);
		ft_strdel(&res);
	}
	else
		tab_term(2);
}

void				tab_completion(t_shell **shell, t_c_tab *list, size_t val)
{
	char			*buff[5];

	ft_memset(buff, 0, 5);
	tab_term(4);
	while (val == 0 || (read(0, buff, 5)
	&& (val = verify_btn((unsigned int)*buff)) != 0 && val != 1 && val != 9))
	{
		tab_term(1);
		(list ? list = move_select(list, val) : NULL);
		if (val == 0 && (binary_directories(*shell)))
		{
			MOVE_DOWN;
			if (!(list = tab_binary(list, *shell)))
				return ;
		}
		else if (val == 0 && !(list = search_on_dir(".", *shell, NULL)))
			return ;
		if (val == 0 && !(list = define_pading(list)) &&
				(val = 1) && put_options(list) == 0)
			break ;
		ft_memset(buff, 0, 5);
	}
	ft_putstr(tgetstr("rc", NULL));
	put_tab(list, shell, val);
	(list ? clean_c_list(&list) : NULL);
}
