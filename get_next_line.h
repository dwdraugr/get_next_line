/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwdraugr <dwdraugr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:19:29 by dwdraugr          #+#    #+#             */
/*   Updated: 2019/01/11 17:31:56 by dwdraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# define BUFF_SIZE 32

# define MALL_CHECK(x) if (!(x)) return (-1);
# define VAL_FILE(f, l, r) if ((f) < 0 || (l) == NULL || (r) < 0) return (-1);

typedef struct			s_fd_list
{
	int					fd;
	char				*buf;
	struct s_fd_list	*next;

}						t_fd_list;

int						get_next_line(const int fd, char **line);

#endif
