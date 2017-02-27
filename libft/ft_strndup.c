/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 22:39:08 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/27 23:13:40 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(char *src, size_t size)
{
	char	*str;

	if ((str = ft_strnew(size)))
		ft_strncpy(str, src, size);
	else
		return (0);
	return (str);
}
