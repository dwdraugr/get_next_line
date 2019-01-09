/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwdraugr <dwdraugr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 15:53:35 by dwdraugr          #+#    #+#             */
/*   Updated: 2019/01/09 19:13:21 by dwdraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

/*
** return element with equal fd or create new, if it is missing
*/

static t_list	*get_struct(t_list **file, int fd)
{
	t_list	*tmp;

	tmp = *file;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(file, tmp);
	tmp = *file;
	return (tmp);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_list	*fd_lst;
	//char			*end_line;
	t_list			*curr;
	int				read_bytes;
	int			i;

	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	curr = get_struct(&fd_lst, fd);
	MALL_CHECK((*line = ft_strnew(1)));
	while ((read_bytes = read(fd, buf, BUFF_SIZE)))
	{
		buf[read_bytes] = '\0';
		MALL_CHECK((curr->content = ft_strjoin((char*)curr->content, buf)));
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (read_bytes < BUFF_SIZE && !ft_strlen((char*)curr->content))
		return (0);

	i = ft_copyuntil(line, curr->content, '\n');
	if (i < (int) ft_strlen(curr->content))
		curr->content += (i + 1);
	else
		ft_strclr(curr->content);
	return (1);
}
