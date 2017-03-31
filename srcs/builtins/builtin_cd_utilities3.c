/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utilities3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 17:37:21 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/24 17:38:31 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_back(char ***split_tab, char **new, int *size, int *i)
{
	char *tmp;

	tmp = NULL;
	*i += 2;
	while (*size != 1)
	{
		if (*split_tab[*i])
		{
			tmp = *new;
			*new = ft_str3join(*new, "/", *split_tab[*i]);
			ft_strdel(&tmp);
		}
		(*i)++;
		(*size)--;
	}
}

void	parse_cd_options(t_shell **shell, int *p_option, char **path)
{
	int		i;
	int		capl;

	i = 1;
	capl = 0;
	while ((*shell)->cmd[i] != 0)
	{
		if (ft_strncmp((*shell)->cmd[i], "-P", 2) == 0)
			*p_option = 1;
		else if (ft_strncmp((*shell)->cmd[i], "-L", 2) == 0
				|| ft_strncmp((*shell)->cmd[i], "-LP", 3) == 0
				|| ft_strncmp((*shell)->cmd[i], "-PL", 3) == 0)
			capl = 1;
		else
			break;
		i++;
	}
	*p_option = (capl == 1) ? 0 : 1;
	if ((*shell)->cmd[i] == 0)
		(*path) = get_env_val(shell, "HOME");
	else
		(*path) = (*shell)->cmd[i];
}
