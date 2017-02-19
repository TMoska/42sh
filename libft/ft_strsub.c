/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 07:18:37 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/19 23:03:24 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*string;
	char	*tmp;

	tmp = NULL;
	if (!s || !(string = ft_strnew(len)))
		return (0);
	tmp = string;
	ft_strncpy(string, &s[start], len);
	return (string);
}
