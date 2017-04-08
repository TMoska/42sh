/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/04/08 04:41:46 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					check_dir(char *tmp)
{
	struct stat		data;

	if (lstat(tmp, &data) == -1)
		return (0);
	if (S_ISDIR(data.st_mode))
		return (1);
	return (0);
}

size_t				nb_pages(t_c_tab *tmp)
{
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->page);
}

int					check_winsize(t_shell **shell)
{
	struct winsize	w;

	if (ioctl(0, TIOCGWINSZ, &w) == -1 || w.ws_col < 75)
	{
		MOVE_DOWN;
		MOVE_DOWN;
		ft_putendl("\033[31m The window is too small ;/ \033[0m");
		MOVE_DOWN;
		print_prompt(shell, NULL);
		ft_putstr((*shell)->buff);
		return (0);
	}
	return (1);
}

int					treat_tab_c(size_t *v, t_shell **shell, t_c_tab **list)
{
	tab_term(1, NULL, 0);
	(((*list)) ? ((*list)) = move_select(((*list)), (*v)) : NULL);
	if ((*v) == 0 && (binary_directories(*shell)))
	{
		if (!(((*list)) = tab_binary(((*list)), *shell)) || !((*list))->content)
			return (-1);
	}
	else if ((*v) == 0 && (!(((*list)) = search_on_dir(".", *shell, NULL, 1))
				|| !((*list))->content))
		return (-1);
	if ((*v) == 0 && !(((*list)) = define_pading(((*list)), &(*v))))
		return (0);
	if ((((*v) = ((*v) != 69 ? ((*v)) : (69))) || !(*v))
			&& !put_options(((*list)), (*v)))
		return (0);
	((*v) = ((*v) != 69 ? (1) : (69)));
	return (1);
}
