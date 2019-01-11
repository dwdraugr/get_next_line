/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwdraugr <dwdraugr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 15:53:35 by dwdraugr          #+#    #+#             */
/*   Updated: 2019/01/11 18:03:39 by dwdraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

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
	*file = tmp;
	return (*file);
}

/*
** ft_strplus - create fresh string with size = old_size + add
*/

static int		ft_strplus(char **str, size_t add)
{
	char	*tmp;
	size_t	len;

	tmp = ft_strdup(*str);
	len = ft_strlen(tmp);
	free(*str);
	*str = ft_strnew(len + add);
	ft_strncpy(*str, tmp, len);
	ft_strdel(&tmp);
	return (1);
}

/*
** copy_to_chr -	add read the characters in destination
**					until we find the value of c
** 70-73 search c-char in src
** 79-80 add every character in destination
*/

static int		copy_to_chr(char **dst, char **src, char c)
{
	int		i;
	int		count;
	int		pos;
	char	*tmp;

	i = -1;
	tmp = *src;
	count = 0;
	while (tmp[++i])
		if (tmp[i] == c)
			break ;
	pos = i;
	if (!(*dst = ft_strnew(i + 1)))
		return (0);
	while (tmp[count] && count < i)
	{
		ft_strncat(*dst, tmp + count, 1);
		count++;
	}
	free(*src);
	*src = tmp;
	return (pos);
}

/*
** get_next_line -	reads from a file one line in line
**					return 1 if line is read successfully
** 					return 0 if reading complete
**					return -1 if error
**	110: check input
**	111: obtain a structure with handle
**	112-119: until we don't find \n, continue reading
**	120-121: if we have reached end of file we exit of function
**	123-125: coping line in line
**	127: if we wrote in line last characters, clear content in current
**		 structure
*/

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_list	*fd_lst;
	t_list			*curr;
	int				read_bytes;
	int				i;

	VAL_FILE(fd, line, read(fd, buf, 0));
	curr = get_struct(&fd_lst, fd);
	while ((read_bytes = read(fd, buf, BUFF_SIZE)))
	{
		buf[read_bytes] = '\0';
		MALL_CHECK(ft_strplus((char**)(&curr->content), read_bytes));
		ft_strncat((char*)curr->content, buf, read_bytes);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (read_bytes < BUFF_SIZE && !ft_strlen((char*)curr->content))
		return (0);
	i = copy_to_chr(line, (char**)&curr->content, '\n');
	if (i < (int)ft_strlen(curr->content))
		curr->content = ft_strsub(curr->content, i + 1,
							ft_strlen(&curr->content[i + 1] - 1));
	else
		ft_strclr(curr->content);
	return (1);
}
