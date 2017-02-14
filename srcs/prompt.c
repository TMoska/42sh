/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:33:26 by moska             #+#    #+#             */
/*   Updated: 2017/02/08 21:02:28 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_prompt(int terminated)
{
  // Todo: show working directory on the left
  if (terminated)
    write (1, "\n> ", 3);
  else
    write (1, "moska prompt $> ", 16);
}