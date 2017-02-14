/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_justified_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 20:05:48 by moska             #+#    #+#             */
/*   Updated: 2017/01/19 01:05:29 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_justified_str(char *str, size_t tot_size, char fill,\
		t_bool right)
{
	size_t len;
	size_t i;

	i = 0;
	len = ft_strlen(str);
	if (!right)
		ft_putstr(str);
	while (i < (tot_size - len))
	{
		ft_putchar(fill);
		i++;
	}
	if (right)
		ft_putstr(str);
}
