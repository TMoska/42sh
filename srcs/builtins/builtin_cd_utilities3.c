/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utilities3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 17:37:21 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/05 04:47:34 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		join_back(char ***split_tab, char **new, int *size, int *i)
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

static int	sub_parser(t_shell **shell, int *p_option, int *capl, int *i)
{
	int		j;

	while ((*shell)->cmd[*i] != 0)
	{
		if ((*shell)->cmd[*i][0] == '-' && ft_strlen((*shell)->cmd[*i]) != 1)
		{
			j = 1;
			while ((*shell)->cmd[*i][j] != '\0' &&
					((*shell)->cmd[*i][j] == 'P'
					|| (*shell)->cmd[*i][j] == 'L'))
			{
				if ((*shell)->cmd[*i][j] == 'P')
					*p_option = 1;
				else if ((*shell)->cmd[*i][j] == 'L')
					*capl = 1;
				j++;
			}
			if ((*shell)->cmd[*i][j] != '\0')
				return (-1);
		}
		else
			break ;
		(*i)++;
	}
	return (0);
}

int			parse_cd_options(t_shell **shell, int *p_option, char **path)
{
	int		capl;
	int		i;

	capl = 0;
	i = 1;
	if (sub_parser(shell, p_option, &capl, &i) == -1)
	{
		ft_putstr_fd("cd: invalid option\nUsage: cd [-L|-P] [dir]\n", 2);
		return (-1);
	}
	if (*p_option == 1)
		*p_option = (capl == 1) ? 0 : 1;
	if ((*shell)->cmd[i] == 0)
		(*path) = get_env_val(shell, "HOME");
	else
		(*path) = (*shell)->cmd[i];
	return (0);
}
