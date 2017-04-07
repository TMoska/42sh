/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 06:35:35 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/07 09:04:55 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	try_up(t_shell **shell)
{
	int tc;
	int tin;

	tc = (*shell)->term->tc_len;
	tin = (*shell)->term->tc_in;
	while (tin + (*shell)->term->prompt_len >= ft_linesize())
	{
		ft_putstr(tgetstr("up", NULL));
		tin -= ft_linesize();
	}
}
