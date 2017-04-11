/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/04/11 13:48:15 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			begin_resize_tab(t_c_tab **list, size_t number)
{
	ioctl(0, TIOCSTI, "\t");
	MOVE_DOWN;
	MOVE_DOWN;
	tab_cursor_fix(list);
	put_options(((*list) = define_pading((*list), &number)), number);
	(*list) = get_list((*list), 1);
}

t_c_tab			*tab_binary(t_c_tab *list, t_shell *shell)
{
	size_t			i;
	char			*path;
	char			**paths;

	i = -1;
	if (!(path = get_env_val(&shell, "PATH")))
		return (NULL);
	if (!path || !(paths = ft_strsplit(path, ':')))
		return (NULL);
	while (paths[++i])
		list = search_on_dir(paths[i], shell, list, 0);
	ft_str2del(&paths);
	return (list);
}

void			tab_term(int v, t_shell *shell, int put)
{
	if (v == 1)
	{
		DEL_LINES;
	}
	else if (v == 2)
	{
		ft_putstr(tgetstr("ve", NULL));
		MOVE_DOWN;
		DEL_LINES;
		MOVE_UP;
		(put == 1 ? (ft_putstr(tgetstr("up", NULL))) : (0));
		(put == 1 ? (ft_putstr(tgetstr("up", NULL))) : (0));
		if (shell->term->tc_in + shell->term->prompt_len <= ft_linesize())
			ft_putstr(tgoto(tgetstr("ch", NULL), 0,
			shell->term->tc_in + shell->term->prompt_len));
		else
			ft_putstr(tgoto(tgetstr("ch", NULL), 0, (shell->term->tc_in +
			shell->term->prompt_len) % ft_linesize()));
	}
	else if (v == 3)
		ft_put2str(tgetstr("ve", NULL), tgetstr("cd", NULL));
	else if (v == 4)
		ft_put2str(tgetstr("do", NULL), tgetstr("do", NULL));
}

t_c_tab			**init_left(t_c_tab **tmp, size_t *c, size_t *l, size_t *page)
{
	while ((*tmp) != NULL && (*tmp)->cursor != 1)
		(*tmp) = (*tmp)->next;
	if ((*tmp) == NULL)
		return (NULL);
	((*tmp)->cursor) = 0;
	(*c) = (*tmp)->col - 1;
	(*l) = (*tmp)->place;
	(*page) = (*tmp)->page;
	return (tmp);
}

t_c_tab			**init_right(t_c_tab **tmp, size_t *c, size_t *l, size_t *page)
{
	while ((*tmp) != NULL && (*tmp)->cursor != 1)
		(*tmp) = (*tmp)->next;
	if ((*tmp) == NULL)
		return (NULL);
	((*tmp)->cursor) = 0;
	(*c) = (*tmp)->col + 1;
	(*l) = (*tmp)->place;
	(*page) = (*tmp)->page;
	while ((*tmp)->next && (*tmp)->col == (*c) - 1)
		(*tmp) = (*tmp)->next;
	if (!(*tmp)->next && (*c) != (*tmp)->col)
		(*c) = 1;
	else if ((*c) != (*tmp)->col)
		(*c) = 1;
	return (tmp);
}
