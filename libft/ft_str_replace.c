/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 05:06:21 by moska             #+#    #+#             */
/*   Updated: 2017/03/26 14:45:25 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_str_replace(char **str, char *old, char *new, int only_one)
{
	int		i;
	int		old_len;
	int		str_len;
	char	*p2;
	char	*tmp;

	i = 0;
	str_len = ft_strlen(*str);
	old_len = ft_strlen(old);
	while (str_len - i >= old_len)
	{
		tmp = *str;
		if (ft_strncmp(*str + i, old, old_len) == 0)
		{
			p2 = *str + i + old_len;
			ft_bzero(*str + i, old_len);
			*str = ft_str3join(*str, new, p2);
			ft_strdel(&tmp);
			str_len = ft_strlen(*str);
			i += ft_strlen(new);
			if (only_one)
				break ;
			else
				continue ;
		}
		i++;
	}
}
