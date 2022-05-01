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

char	*read_line(int fd, char *old_buff)
{
	char	*buff;
	int		x;

	if(old_buff && ft_strchr(old_buff, '\n'))
		return old_buff;
	buff = malloc((BUFFER_SIZE * sizeof(char)) + 1);
	x = read(fd, buff, BUFFER_SIZE);
	if (x <= 0 )
	{
	 	if (old_buff && old_buff[0])
			return (old_buff);
		else
			return (NULL);
	}
	buff[x] = 0;
	if (old_buff)
		buff = ft_strjoin(buff, old_buff);
	if (buff && !ft_strchr(buff, '\n'))
		read_line(fd, buff);
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
	char *return_line;

	if (ft_strchr(buff, '\n'))
	{
		return_line = ft_substr(buff, 0, get_index_of_char(buff, '\n'));
		return (return_line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	if(!line && buffer)
	{//file ends without enter in the last line
		char *result = buffer;
		buffer = NULL;
		return (result);
	}
	buffer = buffer + get_index_of_char(buff, '\n');
	return (line);
}

int main ()
{
    int fd = open("./a.txt", O_RDONLY);
	printf("%s",get_next_line(fd));printf("-");
	printf("%s",get_next_line(fd));printf("-");
	printf("%s",get_next_line(fd));printf("-");
	printf("%s",get_next_line(fd));printf("-");
	printf("%s",get_next_line(fd));printf("-");
	printf("%s",get_next_line(fd));printf("-");
	close(fd);

    return (0);
}