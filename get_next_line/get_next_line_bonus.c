/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bouns.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 16:01:14 by mbari             #+#    #+#             */
/*   Updated: 2019/11/28 23:49:17 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	write_line(int fd, char **line, char **str, int x)
{
	char	*temp1;
	int		i;

	i = 0;
	while (str[fd][i] != '\0' && str[fd][i] != '\n')
		i++;
	if (str[fd][i] == '\n' || (str[fd][i] == '\0' && str[fd][0] != '\0'))
	{
		if (!(*line = ft_substr(str[fd], 0, i)))
			return (-1);
		temp1 = str[fd];
		if (str[fd][i] != '\0')
		{
			if (!(str[fd] = ft_strdup(str[fd] + i + 1)))
				return (-1);
		}
		else if (!(str[fd] = ft_strdup(str[fd] + i)))
			return (-1);
		free(temp1);
		return (1);
	}
	if (!x && !*str[fd])
		free(str[fd]);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int				r;
	char			*buff;
	char			*temp;
	static	char	*str[LIMIT];

	if (fd < 0 || fd > LIMIT || BUFFER_SIZE <= 0 ||
	!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!(ft_strchr(buff, '\n')) && (r = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[r] = '\0';
		temp = str[fd];
		if (!(str[fd] = ft_strjoin(str[fd], buff)))
			return (-1);
		if (temp)
			free(temp);
	}
	free(buff);
	if (r == -1)
		return (-1);
	return (write_line(fd, line, str, r));
}
