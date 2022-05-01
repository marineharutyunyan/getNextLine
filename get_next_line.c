/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:34:00 by maharuty          #+#    #+#             */
/*   Updated: 2022/04/28 12:59:23 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *old_buff)
{
	char	*buff;
	char	*new_buff;
	int		x;

	buff = old_buff;
	while (!ft_strchr(buff, '\n') || !ft_strchr(buff, '\0'))
	{
		new_buff = malloc((BUFFER_SIZE * sizeof(char)) + 1);
		x = read(fd, new_buff, BUFFER_SIZE);
		if (x <= 0 )
		{
			if (old_buff)
				return (old_buff);
			else 
				return (NULL);	
		}
		new_buff[x] = 0;
		buff = ft_strjoin(buff, new_buff);
	}
	return (buff);
}

int	get_index_of_char(char *line, char ch)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ch)
			break ;
		i++;
	}
	return (i + 1);
}

char	*get_line(char *buff)
{
	if (ft_strchr(buff, '\n'))
		return (ft_substr(buff, 0, get_index_of_char(buff, '\n')));
	else if (ft_strchr(buff, '\0'))
		return (ft_substr(buff, 0, get_index_of_char(buff, '\0')));
	return (NULL);	
}

char *get_buffer(char *buff)
{
	return (buff + get_index_of_char(buff, '\n'));
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*result;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_file(fd, buffer);
	if (!line)
		return (NULL);
	result = get_line(line);
	buffer = get_buffer(line);
	return (result);
}
