/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmayika <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:06:25 by kmayika           #+#    #+#             */
/*   Updated: 2018/06/11 16:16:06 by kmayika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# include "./libft/libft.h"
# define BUFF_SIZE 1
/*maximum number of files (limit)*/
# define MAX_FD 1024
# define RET_VALUE(ret) ret > 0 ? 1 : ret

int	get_next_line(int const fd, char **line);

#endif
