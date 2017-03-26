/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exclamation_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 13:44:42 by moska             #+#    #+#             */
/*   Updated: 2017/03/26 14:01:10 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		no_history_err(char *arg)
{
	ft_putstr_fd("No such history index: ", 2);
	ft_putendl_fd(arg, 2);
	return (1);
}
