/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 23:35:09 by mbari             #+#    #+#             */
/*   Updated: 2020/01/23 23:35:12 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int				get_line(char **rem, int n, char **line, int fd)
{
	char		*temp;
	int			i;

	i = 0;
	while (rem[fd][i] && rem[fd][i] != '\n')
		i++;
	*line = ft_substr(rem[fd], 0, i);
	if (!rem[fd][i])
	{
		temp = rem[fd];
		rem[fd] = NULL;
		free(temp);
		return (0);
	}
	else
	{
		temp = rem[fd];
		rem[fd] = ft_strdup((rem[fd]) + i + 1);
		free(temp);
	}
	if (!rem[fd] || !*line)
		return (-1);
	if (n || (n == 0 && rem[fd] != NULL))
		return (1);
	return (-1);
}

int				get_next_line(int fd, char **line)
{
	char				*buf;
	static char			*rem[4864];
	char				*temp;
	int					n;

	buf = NULL;
	if (!line || fd < 0 || fd >= 4864 || BUFFER_SIZE <= 0
			|| !(buf = malloc(BUFFER_SIZE + 1)) || read(fd, buf, 0) == -1)
		return (-1);
	if (!rem[fd])
		if (!(rem[fd] = ft_strdup("")))
			return (-1);
	while ((n = read(fd, buf, BUFFER_SIZE)))
	{
		temp = rem[fd];
		buf[n] = '\0';
		if (!(rem[fd] = ft_strjoin(rem[fd], buf)))
			return (-1);
		free(temp);
		if (ft_strchr(rem[fd], '\n') != 0)
			break ;
	}
	free(buf);
	return (get_line(rem, n, line, fd));
}
