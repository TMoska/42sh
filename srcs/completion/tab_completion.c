/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/04/08 01:22:36 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (v != 1 && v <= 9)
		return (tab_term(2, *shell, 0));
	while (list && list->cursor != 1)
		list = list->next;
	i = ft_strlen((*shell)->buff);
	while (i > 0 && (*shell)->buff[i] != ' ')
		i--;
	((i != 0) ? (tmp = ft_strsub((*shell)->buff, 0, i + 1)) : (tmp));
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, (*shell)->term->prompt_len));
	try_up(shell);
	ft_bzero((*shell)->buff, ft_strlen((*shell)->buff));
	reset_line(shell);
	if (!(res = NULL) && list && list->content)
		res = (check_dir(list->content) ? ft_strjoin(tmp, list->content) :
				ft_str3join(tmp, list->content, " "));
	ft_strdel(&tmp);
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

	ft_memset(buff, 0, 5);
	tab_term(4, NULL, 0);
	if (get_dir(shell))
		return ;
	while ((!list || (list && (get_list(NULL, 0)))) &&
			(v == 0 || (v != 69 && read(0, buff, 5)
			&& (v = verify_btn((unsigned int)*buff)) > 1 && v < 9)))
	{
		tab_term(1, NULL, 0);
		(list ? list = move_select(list, v) : NULL);
		if (v == 0 && (binary_directories(*shell)))
		{
			if (!(list = tab_binary(list, *shell)) || !list->content)
				return (tab_term(2, *shell, 1));
		}
		else if (v == 0 && (!(list = search_on_dir(".", *shell, NULL, 1))
					|| !list->content))
			return (tab_term(2, *shell, 1));
		if (v == 0 && !(list = define_pading(list, &v)))
			break ;
		if (((v = (v != 69 ? (v) : (69))) || !v) && !put_options(list, v))
			break ;
		(v = (v != 69 ? (1) : (69)));
		ft_memset(buff, 0, 5);
	}
	if (!get_list(NULL, 0))
		return ;
	MOVE_UP;
	put_tab(list, shell, v);
	(list ? clean_list(list) : NULL);
	get_list(NULL, 1);
}
