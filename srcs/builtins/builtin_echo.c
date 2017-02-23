/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:38:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/23 23:36:22 by tmoska           ###   ########.fr       */
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
	i = 1;
	size = (int)ft_str2len((*shell)->cmd);
	commands = (*shell)->cmd;
	while ((i + 1) < size)
	{
		if (i == 1)
			new = ft_str3join(commands[1], " ", commands[2]);
		else
			new = ft_str3join(new, " ", commands[i + 1]);
		i++;
	}
	ft_str2del(&(*shell)->cmd);
	(*shell)->cmd = ft_str2new(2);
	(*shell)->cmd[0] = ft_strdup("echo");
	(*shell)->cmd[1] = new;
}

void	echo_simple(t_shell **shell, char *cmd)
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
		if (tab[i][0] == '$')
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
	ft_putendl("");
}

void	builtin_echo(t_shell **shell)
{
	char	*cmd;

	cmd = (*shell)->cmd[1];
	if ((*shell)->cmd_len == 1)
		ft_putendl("");
	else
	{
		if (cmd[0] == '\"' || cmd[0] == '\'')
		{
			rebuild_cmd(shell, cmd);
			(*shell)->cmd[1] = ft_strtrim_char((*shell)->cmd[1], '\"');
			(*shell)->cmd[1] = ft_strtrim_char((*shell)->cmd[1], '\'');
			cmd = (*shell)->cmd[1];
		}
		echo_simple(shell, cmd);
	}
}
