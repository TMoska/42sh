/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:38:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/24 11:52:45 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rebuild_cmd(t_shell **shell, char *cmd)
{
	char	*new;
	int		i;
	int		size;
	int		quote;
	char	**commands;

	new = NULL;
	quote = (cmd[0] == '\"' ? 2 : 1);
	i = 2;
	size = (int)ft_str2len((*shell)->cmd);
	commands = (*shell)->cmd;
	new = ft_str3join(commands[1], " ", commands[2]);
	while ((i + 1) < size)
	{
		new = ft_str3join(new, " ", commands[i + 1]);
		i++;
	}
	ft_str2del(&(*shell)->cmd);
	(*shell)->cmd = ft_str2new(2);
	(*shell)->cmd[0] = ft_strdup("echo");
	(*shell)->cmd[1] = new;
}

void	echo_simple(t_shell **shell, char *cmd, int q_count)
{
	char	**tab;
	int		size;
	int		i;
	char	*tmp;

	tab = ft_strsplit(cmd, ' ');
	size = (int)ft_str2len(tab);
	i = 0;
	while (i < size)
	{
		if ((q_count == 2 || q_count == 0) && tab[i][0] == '$')
		{
			tmp = get_env_val(shell, (tab[i] + 1));
			if (tmp)
				ft_putstr(tmp);
		}
		else
			ft_putstr(tab[i]);
		i++;
		if (tab[i])
			ft_putstr(" ");
	}
}

void	builtin_echo(t_shell **shell)
{
	char	*cmd;
	int		i;
	int		q_count;

	i = 1;
	q_count = 0;
	while ((*shell)->cmd[i])
	{
		cmd = (*shell)->cmd[i];
		if ((*shell)->cmd_len == 1)
			ft_putendl("");
		else
		{
			if (cmd[0] == '\"' || cmd[0] == '\'')
			{
				q_count = (cmd[0] == '\"' ? 2 : 1);
				rebuild_cmd(shell, cmd);
				if (q_count == 2)
					(*shell)->cmd[i] = ft_strtrim_char((*shell)->cmd[i], '\"');
				else if (q_count == 1)
					(*shell)->cmd[i] = ft_strtrim_char((*shell)->cmd[i], '\'');
				cmd = (*shell)->cmd[i];
			}
			echo_simple(shell, cmd, q_count);
		}
		i++;
		if ((*shell)->cmd[i])
			ft_putstr(" ");
	}
	ft_putendl("");
}
