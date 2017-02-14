/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 23:24:14 by moska             #+#    #+#             */
/*   Updated: 2017/01/30 17:32:39 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_get_path(char *folder_name)
{
	char	*start;
	char	*start_tmp;
	char	*tmp;

	tmp = NULL;
	start = ft_strdup(folder_name);
	start_tmp = start;
	while (*start_tmp != '\0')
	{
		if (*start_tmp == '/')
			tmp = start_tmp;
		start_tmp++;
	}
	if (tmp)
		*tmp = '\0';
	else
	{
		free(start);
		return (ft_strdup("."));
	}
	return (start);
}
