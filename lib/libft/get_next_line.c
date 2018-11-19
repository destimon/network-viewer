/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 17:54:50 by dcherend          #+#    #+#             */
/*   Updated: 2018/05/05 14:00:23 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			copy_part(char **dst, char *src)
{
	char			*tmp;
	int				i;
	int				len;

	len = 0;
	i = 0;
	if (src && dst)
	{
		while (src[len] && src[len] != '\n')
			len++;
		IFMALL((tmp = ft_strnew(len)));
		while (i < len)
		{
			tmp[i] = src[i];
			i++;
		}
		free(*dst);
		*dst = tmp;
	}
	return (len);
}

t_file				*file_list(int fd, t_file **file)
{
	t_file			*copy;

	copy = *file;
	while (copy)
	{
		if (copy->fd == fd)
			return (copy);
		copy = copy->next;
	}
	copy = (t_file*)malloc(sizeof(t_file));
	copy->str = ft_strnew(0);
	copy->fd = fd;
	copy->next = *file;
	*file = copy;
	return (*file);
}

int					reading(t_file *file, int fd)
{
	char			buf[BUFF_SIZE + 1];
	int				count;
	char			*lost;

	while ((count = read(fd, (void*)buf, BUFF_SIZE)))
	{
		BYTECHECK(count);
		buf[count] = '\0';
		lost = file->str;
		IFMALL((file->str = ft_strjoin(file->str, buf)));
		free(lost);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (count);
}

int					get_next_line(const int fd, char **line)
{
	static t_file	*file = NULL;
	t_file			*tmp;
	int				count;
	char			*lost;

	VALID(fd, line, BUFF_SIZE);
	IFMALL((*line = ft_strnew(0)));
	tmp = file_list(fd, &file);
	BYTECHECK(reading(tmp, fd));
	ENDCHECK((ft_strlen(tmp->str)));
	count = copy_part(line, tmp->str);
	if ((int)ft_strlen(tmp->str) > count)
	{
		lost = ft_strdup(tmp->str + count + 1);
		free(tmp->str);
		tmp->str = lost;
	}
	else
		ft_strclr(tmp->str);
	return (LINE);
}
