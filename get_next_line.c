#include "get_next_line.h"

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


int			ft_getstart(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

int			ft_getend(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, s1[len - i - 1]) == 0)
			break ;
		i++;
	}
	return (len - i);
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

char		*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*newstr;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start = ft_getstart(s1, set);
	end = ft_getend(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	newstr = (char *)malloc(sizeof(char) * (end - start + 1));
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, s1 + start, end - start + 1);
	return (newstr);
}
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dstc;
	const char	*srcc;

	if (!dst && !src)
		return (0);
	dstc = (char *)dst;
	srcc = (const char *)src;
	while (n--)
		dstc[n] = srcc[n];
	return (dst);
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
	return (newstr);
}






const int size = 50;
char *readbuff(int fd)
{
	char *buff = malloc((size * sizeof(char)) + 1);
	int x = read(fd, buff, size);
	if(x <= 0)
		return (NULL);
	buff[x] = 0;
	char *line = malloc((x * sizeof(char)) + 1);
	line = buff;
	return line;
}

char *get_next_line(int fd)
{
    static char *line;
	char ch = '\n';

	char *newbuff = readbuff(fd);
	line = ft_strjoin(line, newbuff);
	
	if (line)
	{	
		int endOfline = 0;
		while (!endOfline)
		{
			if (ft_strchr(line, '\n')) {
				endOfline = 1;
				int i = 0;
				while (line[i])
				{
					if (line[i] == '\n')
						break;
					i++;
				}
				int indexOfEnter = i+ 1;
				char *returnLine = ft_substr(line, 0, indexOfEnter);
				line = line + indexOfEnter;
				return returnLine;
			} 
			else 
			{
				char *buff = readbuff(fd);
				if (buff)
					line = ft_strjoin(line, buff);
				else 
				{
					//when it's the end of the file
					char *lineCopy = line;
					line = NULL;
					return (lineCopy);
				}
				
			}
		}
		return (line);
	}
	return (NULL);	
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