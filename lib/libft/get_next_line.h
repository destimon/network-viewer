/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:57:34 by dcherend          #+#    #+#             */
/*   Updated: 2018/05/11 16:52:12 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define BUFF_SIZE 25

# define ERR -1
# define END 0
# define LINE 1

# define IFMALL(x) if (!x) return (ERR)
# define BYTECHECK(x) if (x < 0) return (ERR)
# define ENDCHECK(x) if (!x) return (END)
# define VALID(f, l, b) if (f < 0 || !l || b < 0 || f >= 4864) return (ERR)

int					get_next_line(const int fd, char **line);

typedef struct		s_file
{
	int				fd;
	char			*str;
	struct s_file	*next;
}					t_file;

#endif
