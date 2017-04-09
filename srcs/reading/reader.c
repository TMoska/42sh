/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 19:37:58 by moska             #+#    #+#             */
/*   Updated: 2017/04/09 19:46:26 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cancel_heredoc(t_shell **shell, char *heredoc)
{
	ft_strdel(&(*shell)->buff);
	(*shell)->buff = ft_strdup(heredoc);
	return (reset_line(shell));
}

static int	identify_key(t_shell **shell, char *buff, unsigned int key,\
		char *heredoc)
{
	(key != BTN_ENTER && ft_isprint(key)) ? work_buffer(shell, buff) : (0);
	(key == BTN_BACK || key == BTN_DEL) ? modify_buffer(shell, key) : (0);
	(key == BTN_ALEFT || key == BTN_ARIGHT) ? move_cursor_alt(shell, key) : (0);
	(key == BTN_UP || key == BTN_DOWN) ? history(shell, key) : (0);
	(key == BTN_CTRL_K || key == BTN_CTRL_L) ? cut_line(shell, key) : (0);
	(key == BTN_CTRL_P) ? work_buffer(shell, (*shell)->clipboard) : (0);
	(key == BTN_CTRL_H) ? copy(shell) : (0);
	(key == BTN_TAB && !heredoc) ? tab_completion(shell, NULL, 0) : (0);
	(key == BTN_CTRL_U) ? cmd_rewrite(shell) : (0);
	if (key == BTN_LEFT || key == BTN_RIGHT ||
			key == BTN_END || key == BTN_HOME)
		move_cursor_sides(shell, key);
	else if (key == BTN_CTRL_D && heredoc)
		return (cancel_heredoc(shell, heredoc));
	else if (key == BTN_CTRL_D && ft_strlen((*shell)->buff) == 0)
		sig_callback(SIGQUIT);
	else if (key == BTN_ENTER)
	{
		goto_endcmdline(shell);
		return (reset_line(shell));
	}
	return (1);
}

void		read_input(t_shell **shell, char *heredoc)
{
	char	*buff[5];

	ft_memset(buff, 0, 5);
	while ((read(0, buff, 5)) > 0 &&
			identify_key(shell, (char *)buff, (unsigned int)*buff, heredoc))
		ft_memset(buff, 0, 5);
	ft_putchar('\n');
}
