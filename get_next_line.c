#include "get_next_line.h"

int	ft_new_line(char **s, char **line, int fd, int ret)
{
	char	*new;
	int	len;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;//go on reading through the file 
	if (s[fd][len] == '\n')//if you get to a new line then terminate and begin in new line
	{
		*line = ft_strsub(s[fd], 0, len);//allocate fresh string
		new = ft_strdup(s[fd] + len + 1);//save the copy of the string including null terminator
		free(s[fd]);
		s[fd] = new;
		if (s[fd][0] == '\0')
			ft_strdel(&s[fd]);//free string
	}
	else if (s[fd][len] == '\0')
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*s[255];
	char		buf[BUFF_SIZE + 1];
	char		*new;
	int		ret;

	if (s[fd] < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strnew(1);
		new = ft_Strjoin(s[fd], buf);
		free(s[fd]);
		s[fd] = new;
		if (ft_strchr(buf, '\n'))
			break;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (s[fd] == NULL || s[fd][0] == '\0'))
		return (0);
	return (ft_new_line(s, line, fd, ret));
}

