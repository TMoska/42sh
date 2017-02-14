/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 22:32:36 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/17 22:32:37 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	if ((str = (char *)malloc(size + 1)))
	{
		ft_bzero(str, size + 1);
		return (str);
	}
	else
		return (NULL);
}
