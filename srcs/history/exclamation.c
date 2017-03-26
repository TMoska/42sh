/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 06:00:06 by moska             #+#    #+#             */
/*   Updated: 2017/03/26 06:50:48 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_double_exclamation(t_shell **shell, char *tmp)
{
	if ((*shell)->history->size > 0)
	{
		ft_str_replace(&(*shell)->buff, "!!", (*shell)->history->list->cmd);
		if (ft_strcmp(tmp, (*shell)->buff) != 0)
			ft_putendl((*shell)->buff);
	}
}
