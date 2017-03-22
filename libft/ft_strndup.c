/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 22:39:08 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/22 00:23:17 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(char *src, size_t size)
{
	char	*str;

	if (!src || size == 0)
		return (0);
	if ((str = ft_strnew(size)))
		ft_strncpy(str, src, size);
	else
		return (0);
	return (str);
}
