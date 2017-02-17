/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:11:46 by moska             #+#    #+#             */
/*   Updated: 2017/02/17 16:06:21 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mid_clean_shell(t_shell **shell)
{
	ft_strdel(&((*shell)->buff));
	ft_str2del((*shell)->cmd);
}

void	clean_shell(t_shell **shell)
{
	ft_str2del((*shell)->env);
}
