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
	int		j;
	int		capl;

	i = 1;
	capl = 0;
	while ((*shell)->cmd[i] != 0)
	{
		if ((*shell)->cmd[i][0] == '-' && ft_strlen((*shell)->cmd[i]) != 1)
		{
			j = 1;
			while ((*shell)->cmd[i][j] != '\0' && 
					((*shell)->cmd[i][j] == 'P' || (*shell)->cmd[i][j] == 'L'))
			{
				if ((*shell)->cmd[i][j] == 'P')
					*p_option = 1;
				else if ((*shell)->cmd[i][j] == 'L')
					capl = 1;
				j++;
			}
			if ((*shell)->cmd[i][j] != '\0')
				break ;
		}
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
