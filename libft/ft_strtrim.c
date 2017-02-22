/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 08:03:49 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/22 21:08:44 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*res;
	size_t	beg;
	size_t	end;

	if (!s)
		return (0);
	beg = 0;
	end = 0;
	end = ft_strlen(s);
	while (s[beg] == ' ' || s[beg] == '\n' || s[beg] == '\t')
		beg++;
	while (s[end - 1] == ' ' || s[end - 1] == '\n' || s[end - 1] == '\t')
		end--;
	if ((res = ft_strncpy(ft_strnew(end - beg), &s[beg], end - beg)))
		return (res);
	return (NULL);
}
