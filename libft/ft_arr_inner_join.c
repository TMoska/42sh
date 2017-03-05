/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_inner_join.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:39:07 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/05 15:00:34 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arr_inner_join(char **arr, char **arr1)
{
	int		size;
	char	**tmp;
	char	**res;
	int		i;
	int		a;

	size = 0;
	i = 0;
	a = 0;
	tmp = arr;
	while (*tmp)
	{
		size += ft_arr_includes(arr1, *tmp);
		tmp++;
	}
	res = ft_str2new(size);
	while (a < size)
	{
		if (ft_arr_includes(arr1, arr[i]))
			res[a++] = ft_strdup(arr[i]);
		i++;
	}
	return (res);
}
