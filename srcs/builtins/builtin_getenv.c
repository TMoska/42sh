/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_getenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:31:37 by moska             #+#    #+#             */
/*   Updated: 2017/04/06 02:35:06 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_getenv(t_shell **shell)
{
	size_t	len;
	char	*val;

	len = ft_str2len((*shell)->cmd);
	if (len > 2)
	{
		ft_putendl_fd("getenv: too many arguments", 2);
		(*shell)->ret = 2;
		g_exit_code = 2;
		return (-1);
	}
	else if (len == 2)
	{
		if ((val = get_env_val(shell, (*shell)->cmd[1])))
			ft_putendl(val);
		else
		{
			ft_putstr_fd("getenv: env variable ", 2);
			ft_putstr_fd((*shell)->cmd[1], 2);
			ft_putendl_fd(" is not found", 2);
		}
	}
	return (0);
}
