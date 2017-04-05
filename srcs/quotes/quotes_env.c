/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 03:57:10 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/05 02:58:56 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*dup_env_val(char *pt)
{
	size_t	sz;

	sz = 1;
	if (pt[sz] <= '9' && pt[sz] >= '1')
		return (NULL);
	while (((pt[sz] >= 'A' && pt[sz] <= 'Z') || pt[sz] == '_' ||
			(pt[sz] >= '1' && pt[sz] <= '9')))
		sz++;
	return (ft_strndup(pt, sz));
}

static int		quostatus_env(t_shell **shell, char **temp)
{
	char	*tmp;

	if (ft_strstr(*temp, "$?"))
	{
		tmp = ft_itoa((*shell)->ret);
		ft_str_replace(temp, "$?", tmp, 1);
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}

char			*quotes_env(char *temp)
{
	t_shell	*shell;
	char	*pt;
	char	*env_val;
	char	*tmp;
	int		i;

	i = 0;
	shell = get_shell(NULL);
	pt = temp;
	while (pt)
	{
		if ((pt = ft_strchr(pt, '$')))
		{
			if (quostatus_env(&shell, &temp))
				continue ;
			if (!(tmp = dup_env_val(pt)))
				return (temp);
			if ((env_val = get_env_val(&shell, &(tmp[1]))))
				ft_str_replace(&temp, tmp, env_val, 1);
			ft_strdel(&tmp);
			++pt;
		}
		i++;
	}
	return (temp);
}
