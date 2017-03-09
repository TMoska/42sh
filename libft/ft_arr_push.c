/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:47:23 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/09 07:21:24 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arr_push(char ***arr, char *str)
{
	int		len;
	char	**new_arr;
	char	**tmp;
	int		i;

	if (!str)
		return ;
	len = (int)ft_str2len(*arr);
	new_arr = ft_str2new(len + 1);
	i = 0;
	while (i < len)
	{
		new_arr[i] = ft_strdup((*arr)[i]);
		i++;
	}
	new_arr[i] = ft_strdup(str);
	tmp = *arr;
	*arr = new_arr;
	ft_str2del(&tmp);
}
