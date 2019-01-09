/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwdraugr <dwdraugr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:19:25 by dwdraugr          #+#    #+#             */
/*   Updated: 2019/01/09 15:48:17 by dwdraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# define BUFF_SIZE 32

# define MALL_CHECK(x) if (!(x)) return (-1);
# define ERRCHECK(x, y, z) if ((x) < 0 || (y) == NULL || (z) < 0) return (-1);
# define READ_CHECK(r) if ((r) == 0) return (0); else if ((r) < 0) return (-1);
# define BUFF_CHECK(buf) if ((buf) == NULL) return (0);
# define START_CHECK(fd, li) if ((fd) < 0 || (line) == NULL) return (-1);

typedef struct			s_fd_list
{
	int					fd;
	char				*buf;
	struct s_fd_list	*next;

}						t_fd_list;

int						get_next_line(const int fd, char **line);

#endif
