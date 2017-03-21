/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndelat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:01:27 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/22 00:25:54 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndelat(char *str, int index, size_t size)
{
	char	*ret;

	if (!str)
		return (NULL);
	ret = ft_strnew(ft_strlen(str) - size);
	ret = ft_strncpy(ret, str, index);
	ret[index] = *ft_strcpy(&ret[index], &str[index + (int)size]);
	return (ret);
}
