/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exclamation_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 13:44:42 by moska             #+#    #+#             */
/*   Updated: 2017/04/08 22:36:18 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		no_history_err(char *arg)
{
	ft_putstr_fd("No such history index: ", 2);
	ft_putendl_fd(arg, 2);
	return (1);
}

/*
**	Returns a type of a single exclamation mark token
**	# = 2;
**	numbers = 1;
**	string = 0;
*/

int		single_excl_type(char *str)
{
	if (*str == '?')
		return (3);
	if (*str == '#')
		return (2);
	else if (ft_isdigit(*str) || (*str == '-' && ft_isdigit(*(str + 1))))
		return (1);
	else if (ft_isalpha(*(str)))
		return (0);
	else
		return (-1);
}
