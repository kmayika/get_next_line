/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmayika <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 13:23:04 by kmayika           #+#    #+#             */
/*   Updated: 2018/06/13 14:20:22 by kmayika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		gnl_verify(char **holder, char **line)
{
	char	*tmp;

	if (*holder[0] == '\0')
		return (0);
	if (ft_strchr(*holder, '\n') != NULL)
	{
		*(ft_strchr(*holder, '\n')) = '\0';
		*line = ft_strdup(*holder);
		tmp = ft_strdup(ft_strchr(*holder, '\0') + 1);
		free(*holder);
		if (tmp)
		{
			*holder = ft_strdup(tmp);
			free(tmp);
		}
	}
	else
	{
		*line = ft_strdup(*holder);
		ft_memdel((void**)holder);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	char		buffer[BUFF_SIZE + 1];
	static char	*sentence[MAX_FD];
	char		*tmp;

	if (fd == -1 || read(fd, buffer, 0) < 0 || !line)
		return (-1);
	if (!(sentence[fd]))
		sentence[fd] = ft_strnew(0);
	while (ft_strchr(sentence[fd], '\n') == NULL)
	{
		ret = read(fd, buffer, BUFF_SIZE);
		buffer[ret] = '\0';
		if (ret == 0)
			break ;
		tmp = ft_strjoin(sentence[fd], buffer);
		free(sentence[fd]);
		sentence[fd] = ft_strdup(tmp);
		if (!(sentence[fd]))
			sentence[fd] = ft_strnew(0);
		free(tmp);
	}
	return (gnl_verify(&sentence[fd], line));
}
