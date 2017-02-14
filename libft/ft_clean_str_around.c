/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_str_around.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 00:30:58 by moska             #+#    #+#             */
/*   Updated: 2017/02/09 02:24:24 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *ft_clean_str_around(char *str, char c)
{
  size_t  len;
  int     beg;
  int     end;

  len = ft_strlen(str);
  end = len;
  while (str[beg] == c)
    beg++;
  if (str[beg] == '\0')
    return (NULL);
  while (str[end - 1] == c)
    end--;
  end = len - end;
  len = len - beg - end
}



e = len - e;
len = len - (b + len - e);
len = e - sb

  len   

len = 8
e = 5
b = 2