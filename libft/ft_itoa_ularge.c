/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ularge.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:25:35 by moska             #+#    #+#             */
/*   Updated: 2017/01/19 01:08:55 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	do_chars(char *first, char *now, unsigned long long number)
{
	while (now >= first)
	{
		*now = number % 10 + '0';
		number /= 10;
		now--;
	}
}

char		*ft_itoa_ularge(unsigned long long number)
{
	char	*new;
	int		length;

	if (number == 0)
		return (ft_strdup("0"));
	length = ft_count_umax_digits(number);
	new = malloc(sizeof(char*) * (length + 1));
	do_chars(new, new + length - 1, number);
	new[length] = '\0';
	return (new);
}
