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

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#include<stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);

size_t 		ft_strlen(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
char	*ft_strdup(const char *s1)
{
	char	*rtn;
	size_t	len;

	len = ft_strlen(s1) + 1;
	rtn = malloc(sizeof(char) * len);
	if (!rtn)
		return (0);
	rtn = memcpy(rtn, s1, len);
	return (rtn);
}

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == c)
		return ((char *)s + i);
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t src_len;

	i = 0;
	if (!dst || !src)
		return (0);
	src_len = ft_strlen(src);
	if (!dstsize)
		return (src_len);
	while (src[i] != '\0' && i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize < src_len)
		dst[dstsize - 1] = '\0';
	else if (dstsize != 0)
		dst[i] = '\0';
	return (src_len);
}


char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	new_len;

	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	new_len = ft_strlen(s + start);
	if (new_len < len)
		len = new_len;
	if (!(substr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
char		*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		s1_len;
	int		s2_len;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (!(s1) ? ft_strdup(s2) : ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(newstr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	strncpy(newstr, s1, s1_len + 1);
	strncat(newstr + (s1_len), s2, s2_len + 1);
	//free(s1);
	//free(s2);
	return (newstr);
}


char	*read_file(int fd, char *old_buff)
{
	char	*buff;
	char	*line;
	int		x;

	buff = malloc((BUFFER_SIZE * sizeof(char)) + 1);
	x = read(fd, buff, BUFFER_SIZE);
	if (x <= 0 )
	{
	 	if (old_buff)
			return (old_buff);
		else 
			return (NULL);	
	}
	buff[x] = 0;
	line = malloc((x * sizeof(char)) + 1);
	line = buff;
	if (old_buff)
		line = ft_strjoin(line, old_buff);
	
	return (line);
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

char *save_next_line(char *buff)
{
	return (buff + get_index_of_char(buff, '\n'));
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	while (!line && buffer)
	{
		buffer = read_file(fd, buffer);
		line = get_line(buffer);
	}
	buffer = save_next_line(buffer);
	return (line);
}

int main ()
{
    int fd = open("./a.txt", O_RDONLY);
	printf("%s",get_next_line(fd));printf("-");
	printf("%s",get_next_line(fd));printf("-");
	printf("%s",get_next_line(fd));printf("-");
	printf("%s",get_next_line(fd));printf("-");
//	printf("%s",get_next_line(fd));
	//printf("-");
	close(fd);

    return (0);
}
