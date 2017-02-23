/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 23:01:00 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/23 23:01:31 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim_char(char const *s, char c)
{
	char	*res;
	size_t	beg;
	size_t	end;

	if (!s)
		return (0);
	beg = 0;
	end = 0;
	end = ft_strlen(s);
	while (s[beg] == c)
		beg++;
	while (s[end - 1] == c)
		end--;
	if ((res = ft_strncpy(ft_strnew(end - beg), &s[beg], end - beg)))
		return (res);
	return (NULL);
}
