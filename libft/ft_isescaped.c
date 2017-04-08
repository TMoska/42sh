/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isescaped.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 03:19:14 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/08 03:32:09 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isescaped(char const *str, size_t index)
{
	int count;

	count = 0;
	if (index <= 0 || index >= ft_strlen(str))
		return (0);
	if (str[index - 1] != '\\')
		return (0);
	--index;
	while (str[index] && str[index] == '\\')
	{
		++count;
		--index;
	}
	if (count % 2 == 0)
		return (0);
	return (1);
}
