/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:13:53 by apigeon           #+#    #+#             */
/*   Updated: 2021/11/30 15:07:29 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



int		get_newline(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*build_line(t_list *first, int size)
{
	int		size;
	char	*new;
	t_list	*lst;

	new = malloc(size + 1);
	if (!new)
		return (NULL);
	size = 0;
	lst = first;
	while (lst->next)
	{
		strlcpy(new + size, lst->s, BUFFER_SIZE + 1);
		size += BUFFER_SIZE;
		lst = lst->next;
	}
	strlcpy(new + size, lst->s, )
}

char	*get_next_line(int fd)
{
	int			newlineIndex;
	char		buff[BUFFER_SIZE + 1];
	static char	*leftover;
	t_list		*lst;

	ret = BUFFER_SIZE;
	size = get_newline(left_over);
	if (size != ft_strlen(left_over) - 1)
	{
		lst = lstnew(leftover);
		free(leftover);
		ret = 0;
	}
	while (ret == BUFFER_SIZE)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		buff[BUFFER_SIZE] = 0;
		newlineIndex = get_newline(buff);
		lstadd_back(&strings, lstnew(strdup(buff), ret));
		if (newlineIndex + 1 != ret)
			break;
	}
	leftover = build_line(lst, newlineIndex + 1);
	return (leftover);
}
