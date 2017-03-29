/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 17:00:08 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/29 02:17:33 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*str;

	if (!src)
		return (NULL);
	if (!(str = ft_strnew(ft_strlen(src) + 1)))
		return (NULL);
	ft_bzero(str, ft_strlen(src) + 1);
	ft_strncpy(str, src, ft_strlen(src));
	return (str);
}
