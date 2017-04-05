/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 09:56:54 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/02 10:00:05 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_arr_to_str(char **arr)
{
	char	*res;
	char	*tmp;
	int		i;

	if (!arr || !*arr)
		return (NULL);
	res = ft_strdup(arr[0]);
	i = 1;
	while (arr[i])
	{
		tmp = res;
		res = ft_str3join(res, " ", arr[i]);
		ft_strdel(&tmp);
		i++;
	}
	return (res);
}
