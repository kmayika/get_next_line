#include "libft.h"

char	*ft_bigger(int const fd, char *buf, int *ret)
{
	char	temp[BUFF_SIZE + 1];
	char	*temp2;

	*ret = read(fd, temp, BUFF_SIZE);
	temp[*ret] = '\0';
	temp2 = buf;
	buf = ft_strjoin(buf, temp);
	ft_strdel(&temp2);//free ... ft_memdel(void **ap)
	return (buf);
}

int	get_next_line(int const fd, char **line)
{
	static char	*buf = NULL;
	int		retval;
	char		*new;
	int		len;

	if (!line || fd < 0)
		return (-1);
	if (buf[0] == '\0')
		buf = ft_strnew(0);//set memory == \0 
	retval = 1;
	while (retval > 0)
	{
		if ((new = ft_strchr(buf, '\n')) != 0)//if new string is  not equal to new line then 
		{
			*new = '\0';
			*line = ft_strdup(buf);
			len = ft_strlen(new + 1) + 1;
			ft_memmove(buf, new + 1, len);
			return (1);
		}
		buf = ft_bigger(fd, buf, &retval);
	}
	return (retval);
}
