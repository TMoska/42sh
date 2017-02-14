/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 06:57:47 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/18 07:10:53 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		length;
	char	*string;
	char	*tmp;

	if (!s || !(*f))
		return (0);
	length = ft_strlen(s);
	tmp = NULL;
	if ((string = (char *)malloc(length + 1)))
	{
		tmp = string;
		while (*s)
		{
			*tmp = (*f)(*s);
			s++;
			tmp++;
		}
	}
	else
		return (0);
	*tmp = '\0';
	return (string);
}
