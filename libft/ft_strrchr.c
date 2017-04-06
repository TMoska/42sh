/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 12:53:59 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/06 06:26:24 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	ln;

	ln = ft_strlen(s) - 1;
	while (ln >= 0)
		if (s[ln--] == (char)c)
			return ((char *)&s[ln]);
	return (0);
}
