/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 21:19:27 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/29 02:11:11 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*d;
	size_t	index;

	d = b;
	index = 0;
	while (len--)
	{
		d[index++] = (unsigned char)c;
	}
	b = d;
	return (b);
}
