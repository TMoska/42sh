/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:27:17 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/22 10:42:46 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(t_shell **shell)
{
	t_envl	*env;

	env = (*shell)->env_list;
	while (env->next)
	{
		ft_putstr("\033[1;34m");
		ft_putstr(env->name);
		ft_putstr("\033[0m");
		ft_putstr("=");
		ft_putendl(env->value);
		env = env->next;
	}
}

static t_env_s	*create_env_struct(char **cmd)
{
	t_env_s *env_s;

	if ((env_s = (t_env_s *)malloc(sizeof(t_env_s))))
	{
		env_s->null = op_null(cmd);
		env_s->unset = op_unset(cmd);
		env_s->set = op_setenv(cmd);
		env_s->ignore = op_ignore(cmd);
		env_s->cmd = op_cmd(cmd);
	}
	return(env_s);
}

int		has_errors(t_env_s *env_s)
{
	int	ret;

	ret = 0;
	if (env_s->unset == -1 && (ret = 1))
		ft_putendl_fd("env: option requires an argument -- 'u'", 2);
	else if (env_s->null == 1 && env_s->cmd == 1 && (ret = 1))
		ft_putendl_fd("env: cannot specify --null (-0) with command", 2);
	return (ret);
}

void	builtin_env(t_shell **shell)
{
	char **env;
	t_env_s *env_s;

	env = (*shell)->env;
	if ((*shell)->cmd_len == 1)
		print_env(shell);
	else if ((env_s = create_env_struct((*shell)->cmd)))
	{
		if (has_errors(env_s))
			return ;
		else if (env_s->ignore == 1 && env_s->cmd == 0 && env_s->set == 1)
			// display_only_setenv(command, env_s->null ? 0 : 1);
		else if (env_s->ignore == 1 && env_s->cmd == 1)
			// run_under_new_environ(command, shell);
		else if (env_s->cmd == 1)
			// run_under_alter_environ(command, shell);
		else if (env_s->cmd == 0)
			// alter_environ_and_display(command, shell, env_s->null ? 0 : 1);
		free(env_s);
	}
}
