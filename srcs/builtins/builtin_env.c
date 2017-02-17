/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:27:17 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/17 19:20:46 by tmoska           ###   ########.fr       */
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

void	builtin_env(t_shell **shell)
{
	char **env;

	env = (*shell)->env;
	if ((*shell)->cmd_len == 1)
		print_env(shell);
	else
	{
		// Todo: support options
		printf("Sorry, don't support options yet.\n");
		print_env(shell);
	}
}
