/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwdraugr <dwdraugr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:19:25 by dwdraugr          #+#    #+#             */
/*   Updated: 2018/12/22 18:50:40 by dwdraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

/*
** 	strplus - add a block of memory in current string.
**	returned 1 if so cool
*/

int			ft_strplus(char **str, size_t add)
{
	char	*tmp;
	size_t	len;

	tmp = ft_strdup(*str);
	len = ft_strlen(tmp);
	ft_strdel(str);
	*str = ft_strnew(len + add);
	ft_strncpy(*str, tmp, len);
	ft_strdel(&tmp);
	return (1);
}

/*
**	add new element for current list or create new list if lst - NULL
**	returned 1, if so cool and 0 if have problem with malloc
*/

int			add_lst(t_fd_list **lst, int fd)
{
	t_fd_list *tmp;
	t_fd_list *new_list;

	tmp = *lst;
	if (tmp == NULL)
	{
		if (!(*lst = malloc(sizeof(t_fd_list))))
			return (0);
		(*lst)->fd = fd;
		(*lst)->buf = ft_strnew(BUFF_SIZE);
		(*lst)->next = NULL;
		return (1);
	}
	else
	{
		if (!(new_list = malloc(sizeof(t_fd_list))))
			return (0);
		new_list->fd = fd;
		new_list->buf = ft_strnew(BUFF_SIZE);
		new_list->next = *lst;
		*lst = new_list;
		return (1);
	}
}

/*
** search element in list by fd. On success returned point to element with
** same fd, else NULL
*/

t_fd_list	*search_lst(t_fd_list *lst, int fd)
{
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int			get_next_line(const int fd, char **line)
{
	static t_fd_list	*lst = NULL;
	t_fd_list			*current_lst;
	char				*end_line;
	char				*result;
	int					read_bytes;

	START_CHECK(fd, line);
	if (NULL == (current_lst = search_lst(lst, fd)))
	{
		add_lst(&lst, fd);
		current_lst = lst;
		read_bytes = read(current_lst->fd, current_lst->buf, BUFF_SIZE);
		READ_CHECK(read_bytes);
		*(current_lst->buf + read_bytes) = '\0';
	}
	BUFF_CHECK(current_lst->buf);
	result = ft_strnew(BUFF_SIZE);
	if ((end_line = ft_strchr(current_lst->buf, '\n')) == NULL)
	{
		ft_strcpy(result, current_lst->buf);
		read_bytes = read(fd, current_lst->buf, BUFF_SIZE);
		if (read_bytes == 0)
		{
			*line = ft_strdup(result);
			ft_strdel(&result);
			if (*current_lst->buf == '\0')
				return (0);
			else
			{
				ft_strdel(&current_lst->buf);
				current_lst->buf = NULL;
				return (1);
			}
		}
		*(current_lst->buf + read_bytes) = '\0';
		while ((end_line = ft_strchr(current_lst->buf, '\n')) == NULL)
		{
			ft_strplus(&result, read_bytes);
			ft_strncat(result, current_lst->buf, BUFF_SIZE);
			read_bytes = read(fd, current_lst->buf, BUFF_SIZE);
			if (read_bytes == 0)
			{
				*line = ft_strdup(result);
				ft_strdel(&result);
				ft_strdel(&current_lst->buf);
				current_lst->buf = NULL;
				return (1);
			}
			*(current_lst->buf + read_bytes) = '\0';
		}
		ft_strplus(&result, read_bytes);
		ft_strncat(result, current_lst->buf, end_line - current_lst->buf);
		ft_strcpy(current_lst->buf, ++end_line);
	}
	else
	{
		ft_strncpy(result, current_lst->buf, end_line - current_lst->buf);
		ft_strcpy(current_lst->buf, ++end_line);
	}
	*line = ft_strdup(result);
	ft_strdel(&result);
	return (1);
}

/*
** int main()
** {
** 	char *str;
** 	int aa, bb, cc, dd;
** 	int a = open("file.txt", O_RDONLY);
** 	int b = open("lines.txt", O_RDONLY);
** 	int c = open("gnl7_1.txt", O_RDONLY);
** 	int d = open("gnl7_2.txt", O_RDONLY);
** 	letsgo:
** 	aa = get_next_line(a, &str);
** 	printf("FILE.TXT: %s\n\n", str);
** 	ft_strdel(&str);
** 	bb = get_next_line(b, &str);
** 	printf("LINES.TXT: %s\n\n", str);
** 	ft_strdel(&str);
** 	cc = get_next_line(c, &str);
** 	printf("GNL7_1.TXT: %s\n\n", str);
** 	ft_strdel(&str);
** 	dd = get_next_line(d, &str);
** 	printf("GNL7_2.TXT: %s\n==============================\n", str);
** 	ft_strdel(&str);
** 	if (aa || bb || cc || dd)
** 		goto letsgo;
** 	return (0);
** }
*/
