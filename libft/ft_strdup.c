/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 17:00:08 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/28 23:48:42 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*str;

  if (!src)
    return (NULL);
	if ((str = (char*)malloc(sizeof(*str) * (ft_strlen(src) + 1))))
		ft_strcpy(str, src);
	else
		return (NULL);
	return (str);
}
