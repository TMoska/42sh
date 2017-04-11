/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 03:05:08 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/11 17:28:40 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*last_matching_opening(t_shell **shell, char *txt)
{
	t_list	*tmp;
	t_list	*ret;

	tmp = (*shell)->heredoc;
	while (tmp)
	{
		if (((t_heredoc*)(tmp->content))->type == 1\
			&& ft_strcmp(((t_heredoc*)(tmp->content))->txt, txt) == 0)
			ret = tmp;
		tmp = tmp->next;
	}
	return (ret);
}

t_heredoc	*new_heredoc_node(char *txt, int type)
{
	t_heredoc	*new;

	if (!(new = (t_heredoc*)ft_memalloc(sizeof(t_heredoc))))
		return (NULL);
	new->txt = ft_strdup(txt);
	new->type = type;
	return (new);
}

void		read_heredoc(char *f, t_shell **shell)
{
	char		*buff_tmp;
	t_heredoc	*hd;

	hd = new_heredoc_node(f, 1);
	buff_tmp = ft_strdup((*shell)->buff);
	ft_lst_new_add_back(&(*shell)->heredoc, (void*)hd, sizeof(*hd));
	free(hd);
	while (1)
	{
		print_prompt(shell, ft_str3join("heredoc: ", f, " >"));
		signal(SIGINT, SIG_IGN);
		read_input(shell, f);
		hd = new_heredoc_node((*shell)->buff, 0);
		if (ft_strcmp((*shell)->buff, f) == 0)
			hd->type = 2;
		ft_lst_new_add_back(&(*shell)->heredoc, (void*)hd, sizeof(*hd));
		free(hd);
		if (ft_strcmp((*shell)->buff, f) == 0)
			break ;
		ft_strdel(&(*shell)->buff);
	}
	ft_strdel(&(*shell)->buff);
	(*shell)->buff = buff_tmp;
}

void		scan_heredocs(t_shell **shell)
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
