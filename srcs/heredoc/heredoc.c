/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 03:05:08 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/25 04:14:53 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_heredoc(char *f, t_shell **shell)
{
	char	*buff_tmp;

	buff_tmp = ft_strdup((*shell)->buff);
	ft_lst_new_add_back(&(*shell)->heredoc, f, ft_strlen(f));
	while (1)
	{
		print_prompt(shell, ft_str3join("heredoc: ", f, " >"));
		read_input(shell, f);
		ft_lst_new_add_back(&(*shell)->heredoc, (*shell)->buff,\
							ft_strlen((*shell)->buff));
		if (ft_strcmp((*shell)->buff, f) == 0)
			break ;
		ft_strdel(&(*shell)->buff);
	}
	ft_strdel(&(*shell)->buff);
	(*shell)->buff = buff_tmp;
}

void	scan_heredocs(t_shell **shell)
{
	t_tkn *t;

	t = (*shell)->tkns;
	while (t)
	{
		if (ft_strcmp(t->data, "<<") == 0)
			read_heredoc(t->right->data, shell);
		t = t->right;
	}
}
