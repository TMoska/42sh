/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/04/03 17:27:32 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*ft_change(int n, size_t i)
{
	char	*tmp;

	tmp = ft_strnew(i);
	tmp[i--] = '\0';
	while (n != 0)
	{
		tmp[i] = n % 8 + '0';
		n /= 8;
		i--;
	}
	return (tmp);
}

static int			ft_dtoo(int nb)
{
	size_t		i;
	int			z;
	char		*tmp;

	z = nb;
	i = 0;
	while (z != 0)
	{
		z /= 8;
		i++;
	}
	tmp = ft_change(nb, i);
	z = ft_atoi(tmp);
	free(tmp);
	return (z);
}

int                 check_dir(char *tmp)
{
    struct stat     data;

    if (lstat(tmp, &data) == -1)
        return (0);
    if ((ft_dtoo(data.st_mode) / 10000) % 10 == 4)
        return (1);
    return (0);
}
