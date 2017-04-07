/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/04/08 00:58:02 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					check_dir(char *tmp)
{
	struct stat		data;

	if (lstat(tmp, &data) == -1)
		return (0);
	if (S_ISDIR(data.st_mode))
		return (1);
	return (0);
}

size_t				nb_pages(t_c_tab *tmp)
{
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->page);
}
