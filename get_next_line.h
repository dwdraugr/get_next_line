/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 22:52:40 by jrameau           #+#    #+#             */
/*   Updated: 2016/11/19 12:27:23 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <libft.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFF_SIZE 42

# define MALLCHECK(x) if (!x) return (-1);
# define MALL_CHECK(x) if (!(x)) return (-1);

int		get_next_line(const int fd, char **line);
#endif
