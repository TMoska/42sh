/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 06:00:06 by moska             #+#    #+#             */
/*   Updated: 2017/03/26 14:47:36 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		replace_double_exclamation(t_shell **shell, char *tmp)
{
	if ((*shell)->history->size > 0)
	{
		ft_str_replace(&(*shell)->buff, "!!", (*shell)->history->list->cmd, 0);
		if (ft_strcmp(tmp, (*shell)->buff) != 0)
			ft_putendl((*shell)->buff);
		return (0);
	}
	ft_putendl_fd("Error: No previous history.", 2);
	return (-1);
}
