/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 13:53:05 by mkhan             #+#    #+#             */
/*   Updated: 2022/06/13 14:56:13 by mkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *str, char *s)
{
	free(s);
	free(str);
	return (NULL);
}

char	*ft_readline(int fd, char *s, size_t buff)
{
	char	*str;
	int		i;

	i = 1;
	str = (char *)malloc(buff + 1);
	if (!str)
		return (NULL);
	while (i != 0 && !ft_strchr(s, '\n'))
	{
		i = read(fd, str, buff);
		if (i == -1)
		{
			free(str);
			return (NULL);
		}
		str[i] = '\0';
		s = ft_strjoin(s, str);
	}
	if (s[0] == '\0')
	{
		ft_free(str, s);
		return (NULL);
	}
	free (str);
	return (s);
}

char	*ft_currentline(char *str)
{
	char	*s;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	s = (char *)malloc(i + 2);
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_newline(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	s = (char *)malloc(ft_strlen(str) - i + 1);
	if (!s)
		return (NULL);
	i++;
	while (str[i])
		s[j++] = str[i++];
	s[j] = '\0';
	free (str);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*s;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	str = ft_readline(fd, str, BUFFER_SIZE);
	if (!str)
		return (NULL);
	s = ft_currentline(str);
	str = ft_newline(str);
	return (s);
}

// int main()
// {
// 	int fd = open("f.txt", O_RDONLY);
// 	// printf("%d", fd);
// 	printf("%s", get_next_line(fd));
// 	int fd1 = open("fo.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd1));
// 	int fd2 = open("foo.txt", O_RDONLY);	
// 	printf("%s", get_next_line(fd2));
// 	int fd3 = open("fooo.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd3));
// }