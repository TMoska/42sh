/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/04/09 22:51:33 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t		verify_btn(unsigned int key)
{
	if (key == BTN_UP)
		return (8);
	else if (key == BTN_RIGHT)
		return (6);
	else if (key == 9)
		return (9);
	else if (key == BTN_LEFT || key == BTN_S_TAB)
		return (4);
	else if (key == BTN_DOWN)
		return (2);
	else if (key == BTN_BACK)
		return (10);
	else if (key == BTN_ENTER || key == BTN_SPACE)
		return (1);
	else if (key == BTN_SLASH)
		return (47);
	return (0);
}

static void			put_tab(t_c_tab *list, t_shell **shell, size_t v)
{
	char			*res;
	char			*tmp;
	size_t			i;

	tmp = NULL;
	MOVE_UP;
	if (v != 1 && v <= 10)
		return (tab_term(2, *shell, 0));
	while (list && list->cursor != 1)
		list = list->next;
	i = ft_strlen((*shell)->buff);
	while (i > 0 && (*shell)->buff[i] != ' ')
		i--;
	((i != 0) ? (tmp = ft_strsub((*shell)->buff, 0, i + 1)) : (tmp));
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, (*shell)->term->prompt_len));
	try_up(shell);
	if (!(res = NULL) && list && list->content)
		res = completion_buffer(list, *shell, search_cmd(*shell));
	ft_strdel(&tmp);
	reset_line(shell);
	work_buffer(shell, res);
	ft_strdel(&res);
}

/*
**		binary_directories && search_on_dir are in c_utils.c
**			tab_term && tab_binary is on c_utils3.c
*/

void				tab_completion(t_shell **shell, t_c_tab *list, size_t v)
{
	char			*buff[5];
	int				ttc;

	ft_memset(buff, 0, 5);
	tab_term(4, NULL, 0);
	if (get_dir(shell))
		return ;
	while ((!list || (list && (get_list(NULL, 0)))) &&
			(v == 0 || (v != 69 && read(0, buff, 5)
			&& (v = verify_btn((unsigned int)*buff)) > 1 && v < 10)))
	{
		ft_memset(buff, 0, 5);
		if ((ttc = treat_tab_c(&v, shell, &list)) == 0)
			break ;
		else if (ttc == -1)
			return (tab_term(2, *shell, 1));
	}
	if (!get_list(NULL, 0))
		return ;
	MOVE_UP;
	put_tab(list, shell, v);
	(list ? clean_list(list) : NULL);
	get_list(NULL, 1);
}
