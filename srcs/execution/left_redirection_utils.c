/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirection_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 23:29:48 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/23 23:33:03 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		open_tmp_heredoc(int *fd)
{
	*fd = open(".21sh_heredoc_tmp", O_RDONLY);
	return (0);
}

int		redirection_type(t_tkn *node)
{
	return (ft_strcmp(node->data, "<<") == 0 ? 2 : 1);
}
