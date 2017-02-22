/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str3join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:18:47 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/22 21:08:09 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str3join(char *s1, char *s2, char *s3)
{
	char	*result;
	int		length;
	int		i;

	i = 0;
	length = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if ((result = ft_strnew(length)))
	{
		while (s1 && *s1)
			result[i++] = *s1++;
		while (s2 && *s2)
			result[i++] = *s2++;
		while (s3 && *s3)
			result[i++] = *s3++;
		return (result);
	}
	else
		return (NULL);
}
