/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmayika <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 09:45:06 by kmayika           #+#    #+#             */
/*   Updated: 2018/06/11 16:15:59 by kmayika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			gnl_verify_line(char **stack, char **line)
{
	char			*tmp_stack;
	char			*strchr_stack;
	int				x;

	x = 0;
	strchr_stack = *stack;
	/*check if the stack contains a new line, return zero if not*/
	while (strchr_stack[x] != '\n')
		if (!strchr_stack[x++])
			return (0);
	/*if there is a new line, assign stack chr into temporary stack */
	tmp_stack = &strchr_stack[x];
	/*null terminate the temp stack eg. My name is kwezi\0*/
	*tmp_stack = '\0';
	/*copy stack into line*/
	*line = ft_strdup(*stack);
	/*copy whatever was copied in the stack before back to stack*/
	*stack = ft_strdup(tmp_stack + 1);
	return (1);
}

static	int			gnl_read_file(int fd, char *heap, char **stack, char **line)
{
	int				ret;
	char			*tmp_stack;
	/*while there is a file open with no errors*/
	while ((ret = read(fd, heap, BUFF_SIZE)) > 0)
	{/*take the read return as index and null terminate the heap*/
		heap[ret] = '\0';
		if (*stack)
		{
			tmp_stack = *stack;
			*stack = ft_strjoin(tmp_stack, heap);
			free(tmp_stack);
			tmp_stack = NULL;
		}
		else
			*stack = ft_strdup(heap);
		if (gnl_verify_line(stack, line))
			break ;
	}
	return (RET_VALUE(ret));
}

int			get_next_line(int const fd, char **line)
{
	static char	*stack[MAX_FD];
	char		*heap;
	int			ret;
	int			x;

	if (!line || (fd < 0 || fd > MAX_FD) || (read(fd, stack[fd], 0) < 0)\
		|| !(heap = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	/* if there is something in the stack verify that it has a newline,return 1 if it does*/
	if (stack[fd])
		if (gnl_verify_line(&stack[fd], line))
			return (1);
	x = 0;
	/** When the reading of the file ends, we will free the heap (we're not gonna
** use it anymore)*/
	while (x < BUFF_SIZE)
		heap[x++] = '\0';
	ret = gnl_read_file(fd, heap, &stack[fd], line);
	free(heap);
	/*check for the value of ret (if it's 1 or -1, return
** that, if the stack is empty, return 0)*/
	if (ret != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
	{
		if (!ret && *line)
			*line = NULL;
		return (ret);
	}
	/*if the conditions above are invalid, assign line to the value of stack and free stack and return 1*/
	*line = stack[fd];
	stack[fd] = NULL;
	return (1);
}


