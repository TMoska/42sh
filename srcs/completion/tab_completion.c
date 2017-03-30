/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/03/30 18:38:53 by ede-sous         ###   ########.fr       */
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
	else if (key == BTN_LEFT)
		return (4);
	else if (key == BTN_DOWN)
		return (2);
	else if (key == BTN_BACK)
		return (9);
	else if (key == BTN_ENTER)
		return (1);
	return (0);
}

void				tab_completion(t_shell **shell, t_c_tab *list, size_t val)
{
	char			*buff[5];

	ft_memset(buff, 0, 5);
	while (val == 0 || (read(0, buff, 5)
				&& (val = verify_btn((unsigned int)*buff)) != 0
				&& val != 1 && val != 9))
	{
		tab_term(1);
		(list ? list = move_select(list, val) : NULL);
		if (val == 0 && binary_directories(*shell))
		{
			if (!(list = tab_binary(list, *shell)))
				return ;
		}
		else if (val == 0 && !(list = search_on_dir(".", *shell, NULL)))
			return ;
		if (val == 0 && !(list = define_pading(list)))
			break ;
		if ((val = 1) && put_options(list) == 0)
			break ;
		ft_memset(buff, 0, 5);
	}
    if (val == 1)
    {
        while (list && list->cursor != 1)
            list = list->next;
        ft_strdel(&(*shell)->buff);
        work_buffer(shell, list->content);
        tab_term(3);
    }
    else
	   tab_term(2);
	(list ? clean_c_list(&list) : NULL);
    clear_cmdline(shell);
    print_prompt(shell, NULL);
    read_input(shell, NULL);
}
