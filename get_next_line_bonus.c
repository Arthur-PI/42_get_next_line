/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:13:53 by apigeon           #+#    #+#             */
/*   Updated: 2021/12/01 17:26:08 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	contains_newline(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		if (s[i++] == '\n')
			return (1);
	return (0);
}

int		getline_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*extract_line(char *s, char **leftover)
{
	int		i;
	int		size;
	char	*line;

	size = getline_len(s);
	if (size == 0)
		return (NULL);
	line = malloc(size + 1);
	if (line)
		ft_strlcpy(line, s, size + 1);
	i = size;
	while (s[size])
		size++;
	*leftover = malloc((size - i) + 1);
	if (*leftover)
		ft_strlcpy(*leftover, s + i, (size - i) + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	int			ret;
	char		*buff;
	char		*tmp;
	char		*string;
	static char	*leftover[OPEN_MAX] = {NULL};

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, leftover[fd], 0) == -1)
		return (NULL);
	ret = BUFFER_SIZE;
	string = leftover[fd];
	leftover[fd] = NULL;
	while (ret == BUFFER_SIZE && !contains_newline(string))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return (NULL);
		ret = read(fd, buff, BUFFER_SIZE);
		buff[ret] = 0;
		string = ft_strjoin(string, buff);
	}
	tmp = extract_line(string, &leftover[fd]);
	free(string);
	return (tmp);
}
