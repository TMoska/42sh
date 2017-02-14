/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:09:23 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/18 14:12:56 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	length;
	char			*string;
	char			*tmp;
	int				index;

	index = 0;
	if (!s || !(*f))
		return (0);
	length = ft_strlen(s);
	tmp = NULL;
	if ((string = (char *)malloc(length + 1)))
	{
		tmp = string;
		while (*s)
		{
			*tmp = (*f)(index, *s);
			s++;
			tmp++;
			index++;
		}
	}
	else
		return (0);
	*tmp = '\0';
	return (string);
}
