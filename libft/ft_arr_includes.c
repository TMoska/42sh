/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_includes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:24:30 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/05 14:59:37 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_arr_includes(char **arr, char *str)
{
	char **tmp;

	tmp = arr;
	while (*tmp)
	{
		if (ft_strcmp(*tmp, str) == 0)
			return (1);
		tmp++;
	}
	return (0);
}
