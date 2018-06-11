#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFF_SIZE
#define BUFF_SIZE 9999
#endif

#include "libft.h"

typedef struct		s_descriptor
{
	char			*start;
	char			*current;
	char			*end;
	int				full_read;
}					t_descriptor;

int	get_next_line(int const fd, char **line);

#endif
