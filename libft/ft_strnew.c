/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 22:32:36 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/29 03:44:19 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	if ((str = (char *)malloc(sizeof(char) * (size + 1))))
	{
		ft_bzero(str, size + 1);
		if ((str = ft_memalloc(size + 1)))
			return (str);
	}
	return (NULL);
}
