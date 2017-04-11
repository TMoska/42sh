/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 17:29:34 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/11 17:30:04 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_heredoc(void **content, size_t *content_size)
{
	(void)content_size;
	ft_strdel(&(((t_heredoc*)(*content))->txt));
	free((t_heredoc*)(*content));
}
