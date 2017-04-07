/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:27:17 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/05 04:17:57 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_env(t_envl *env_list)
{
	while (env_list)
	{
		if (env_list->value)
		{
			ft_putstr("\033[1;34m");
			ft_putstr(env_list->name);
			ft_putstr("\033[0m");
			ft_putstr("=");
			ft_putendl(env_list->value);
		}
		env_list = env_list->next;
	}
}

static t_env_s	*create_env_struct(char **cmd)
{
	t_env_s *env_s;

	env_s = NULL;
	if ((env_s = (t_env_s *)malloc(sizeof(t_env_s))))
	{
		env_s->set = op_setenv(cmd);
		env_s->ignore = op_ignore(cmd);
		env_s->cmd = op_cmd(cmd);
	}
	return (env_s);
}

static void		set_error_flag(t_shell **shell, t_env_s *env_s, int *ret)
{
	if (env_s->unset == -1 && (*ret = 1))
		ft_putendl_fd("env: option requires an argument -- 'u'", 2);
	else if (env_s->null == 1 && env_s->cmd == 1 && (*ret = 1))
		ft_putendl_fd("env: cannot specify --null (-0) with command", 2);
	if (*ret)
	{
		((*shell)->ret = -1);
		g_exit_code = -1;
	}
}

int				has_errors(t_shell **shell, t_env_s *env_s, char **cmd)
{
	int	ret;
	int	bin;

	bin = 0;
	ret = 0;
	while (*cmd)
	{
		if (*cmd[0] != '-')
			bin++;
		if (bin == 2)
			break ;
		if (*cmd[0] == '-' && *(*cmd + 1) && \
				!(*(*cmd + 1) == 'u' || *(*cmd + 1) == 'i'
			|| *(*cmd + 1) == '0' || ft_strcmp(*cmd, "--null") == 0)
			&& (ret = 1))
			ft_putendl_fd("env: illegal argument", 2);
		cmd++;
	}
	set_error_flag(shell, env_s, &ret);
	return (ret);
}

int				builtin_env(t_shell **shell)
{
	t_env_s	*env_s;

	if ((*shell)->cmd_len == 1)
		print_setenv((*shell)->env);
	else if ((env_s = create_env_struct((*shell)->cmd)))
	{
		if (has_errors(shell, env_s, (*shell)->cmd))
		{
			free(env_s);
			return (-1);
		}
		else if (env_s->ignore == 1 && env_s->cmd == 0 && env_s->set == 1)
			print_setenv((*shell)->cmd);
		else if (env_s->ignore == 1 && env_s->cmd == 1)
			work_as_newenv((*shell)->cmd, shell);
		else if (env_s->cmd == 1)
			work_with_alterenv((*shell)->cmd, shell);
		else if (env_s->cmd == 0)
			work_environ_and_display((*shell)->cmd, shell, env_s);
		free(env_s);
	}
	return (0);
}
