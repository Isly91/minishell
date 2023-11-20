/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/04 07:47:50 by jvorstma      #+#    #+#                 */
/*   Updated: 2023/04/25 17:57:57 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_read_short(int fd, char *line)
{
	ssize_t	rd;
	char	buf[BUFFER_SIZE + 1];

	while (!ft_gnl_strchr(line))
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
			return (free (line), line = NULL, NULL);
		if (rd == 0)
			break ;
		buf[rd] = '\0';
		line = ft_gnl_strjoin(line, buf);
	}
	return (line);
}

static char	*ft_read_large(int fd, char *line)
{
	ssize_t	rd;
	char	*buf;

	while (!ft_gnl_strchr(line))
	{
		buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
			return (free (line), line = NULL, NULL);
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
			return (free (buf), free (line), line = NULL, NULL);
		if (rd == 0)
		{
			free (buf);
			break ;
		}
		buf[rd] = '\0';
		line = ft_gnl_strjoin(line, buf);
		free (buf);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (BUFFER_SIZE < 10000000)
		line[fd] = ft_read_short(fd, line[fd]);
	else
		line[fd] = ft_read_large(fd, line[fd]);
	return_line = ft_line_return(line[fd]);
	if (return_line)
		return (line[fd] = ft_new_line(line[fd]), return_line);
	else
		return (free (line[fd]), line[fd] = NULL, return_line);
}
