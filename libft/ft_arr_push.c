/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:47:23 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/05 14:59:44 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arr_push(char **arr, char *str)
{
	int		len;
	char	**new_arr;
	int		i;

	if (!str)
		return (NULL);
	len = (int)ft_str2len(arr);
	new_arr = ft_str2new(len + 1);
	i = 0;
	while (i < len)
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i] = ft_strdup(str);
	ft_str2del(&arr);
	return (new_arr);
}
