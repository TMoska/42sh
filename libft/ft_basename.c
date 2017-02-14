/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 23:28:20 by moska             #+#    #+#             */
/*   Updated: 2017/01/14 16:46:47 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_basename(char *folder_name)
{
	char		*start;

	if (ft_strequ(folder_name, "/"))
		return (folder_name);
	start = ft_strchr(folder_name, '\0');
	while (start > folder_name && *(start - 1) != '/')
		start--;
	return (start);
}
