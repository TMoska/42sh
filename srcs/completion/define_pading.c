/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_pading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/03/28 04:37:07 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int      too_much_file(c_tab *list, t_shell *shell)
{
    int         i;
    char        buff[1];

    i = 1;
    while (list && list->next)
    {
        list = list->next;
        i++;
    }
    (void)shell;
    if (i > 25)
    {
        SAVE_LINE;
        MOVE_DOWN;
        DEL_LINES;
        LOAD_LINE;
        ft_putstr(tgetstr("vi", NULL));
        ft_putstr("\033[1;91mBro, there is a lot of possibilities O.O like ");
        ft_putnbr(i);
        ft_putstr(" possibilities O.O Are you sure about that? (y or n)\033[0m");
        while (buff[0] != 'y' && buff[0] != 'n')
            i = read(0, buff, 1);
        ft_putstr(tgetstr("ve", NULL));
        return (buff[0] == 'y');
    }
    return (1);
}

c_tab           *define_pading(c_tab *list, t_shell *shell)
{
    //c_tab           *tmp;
//    struct winsize  w;

    if (list && !too_much_file(list, shell))
        return (NULL);
    return (list);
}
