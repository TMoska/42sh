/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_justified_nbr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 20:11:59 by moska             #+#    #+#             */
/*   Updated: 2017/01/19 01:05:55 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_justified_nbr(int nb, size_t tot_size, char fill, t_bool right)
{
	char *str;

	str = ft_itoa(nb);
	ft_put_justified_str(str, tot_size, fill, right);
	free(str);
}
