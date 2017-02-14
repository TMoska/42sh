/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 08:03:49 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/18 08:25:56 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;

	if (!s)
		return (0);
	if ((str = ft_strdup((char *)s)))
	{
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
		i = ft_strlen(str) - 1;
		while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			i--;
		str[++i] = '\0';
		return (ft_strdup(str));
	}
	else
		return (0);
	return (0);
}
