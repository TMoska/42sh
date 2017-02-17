/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 19:30:07 by tmoska            #+#    #+#             */
/*   Updated: 2016/12/07 22:49:16 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# define BUFF_SIZE 32

typedef struct		s_rdr
{
	char			*buff;
	char			*eol;
	int				tot_buff;
	int				char_buff;
	int				stop;
	int				fd;
}					t_rdr;

int					get_next_line(const int fd, char **line);

#endif
