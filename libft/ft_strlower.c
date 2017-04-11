/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 23:35:17 by ede-sous          #+#    #+#             */
/*   Updated: 2017/04/11 16:53:57 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strlower(char *s)
{
	int		i;
	int		len;

	if (s)
	{
		len = (int)ft_strlen(s);
		i = -1;
		while (++i < len)
			s[i] = ft_tolower((int)s[i]);
		return (s);
	}
	return (NULL);
}
