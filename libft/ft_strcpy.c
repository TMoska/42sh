/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 17:01:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/22 00:24:58 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strcpy(char *dst, const char *src)
{
	char *tmp;

	if (!dst || !src)
		return (NULL);
	tmp = dst;
	while (*src)
	{
		*dst = *src;
		src++;
		dst++;
	}
	*dst = 0;
	return (tmp);
}
