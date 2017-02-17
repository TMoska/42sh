/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:03:23 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/17 18:17:20 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_str2new(size_t size)
{
	char	**str;
	size_t	i;

	i = 0;
	if (!(str = (char **)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	str[size] = 0;
	while (i < size)
		str[i++] = NULL;
	return (str);
}
