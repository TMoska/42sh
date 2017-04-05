/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_del_at.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:02:53 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/02 05:01:21 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arr_del_at(char **arr, int index)
{
	int		len;
	int		i;
	char	**new_arr;

	if (!arr || !(len = ft_str2len(arr)))
		return (NULL);
	i = 0;
	new_arr = ft_str2new(len - 1);
	while (i < len)
	{
		new_arr[i] = ft_strdup(arr[((i + 1) <= index) ? i : (i + 1)]);
		i++;
	}
	ft_str2del(&arr);
	return (new_arr);
}
