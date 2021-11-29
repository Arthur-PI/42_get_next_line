/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:14:09 by apigeon           #+#    #+#             */
/*   Updated: 2021/11/29 16:51:42 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define NOT_FOUND BUFFER_SIZE

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	contains_newline(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (NOT_FOUND);
}

static int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static t_list	*lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

static t_list	*lstnew(char *s, int size)
{
	t_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->s = s;
	new->size = size;
	new->next = NULL;
	return(new);
}

static void	lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = lstlast(*lst);
	if (last)
		last->next = new;
	else
		*lst = new;
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	while (src[i])
		i++;
	return (i);
}

static char	*build_line(t_list *first, int newlineIndex)
{
	int		size;
	char	*new;
	t_list	*lst;

	size = 0;
	lst = first;
	while (lst->next)
	{
		size += lst->size;
		lst = lst->next;
	}
	size += min(newlineIndex + 1, lst->size);
	//printf("Line size = %d\n", size);
	new = malloc(size + 1);
	if (!new)
		return (NULL);
	size = 0;
	lst = first;
	while(lst->next)
	{
		ft_strlcpy(new + size, lst->s, lst->size + 1);
		//printf("Adding: %s\n", lst->s);
		size += lst->size;
		lst = lst->next;
	}
	ft_strlcpy(new + size, lst->s, min(newlineIndex + 1, lst->size) + 1);
	return (new);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*s_dst;
	const char	*s_src;

	i = 0;
	if (!dst && !src)
		return (NULL);
	s_dst = dst;
	s_src = src;
	while (i < n)
	{
		s_dst[i] = s_src[i];
		i++;
	}
	return (dst);
}

char	*substr(char *s, int n)
{
	int		i;
	char	*new;

	new = malloc(ft_strlen(s) - n + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s[n + i])
	{
		new[i] = s[n + i];
		i++;
	}
	new[i] = 0;
	return (new);
}

void	free_list(t_list **first, int newlineIndex)
{
	t_list	*lst;
	t_list	*next;

	lst = *first;
	while (lst->next)
	{
		free(lst->s);
		next = lst->next;
		free(lst);
		lst = next;
	}
	if (newlineIndex == NOT_FOUND)
	{
		free(lst->s);
		free(lst);
		lst = NULL;
	}
	else
	{
		lst->s = substr(lst->s, newlineIndex + 1);
		lst->size = ft_strlen(lst->s);
	}
	*first = lst;
}

char	*get_next_line(int fd)
{
	int				ret;
	int				newlineIndex;
	char			*buff;
	char			*res;
	static t_list	*strings = NULL;

	ret = BUFFER_SIZE;
	newlineIndex = NOT_FOUND;
	while (ret == BUFFER_SIZE && newlineIndex == NOT_FOUND)
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return (NULL);
		ret = read(fd, buff, BUFFER_SIZE);
		buff[ret] = 0;
		//printf("Read line: '%s'\n", buff);
		newlineIndex = contains_newline(buff);
		lstadd_back(&strings, lstnew(buff, ret));
	}
	res = build_line(strings, newlineIndex);
	free_list(&strings, newlineIndex);
	//if (strings)
	//	printf("Reste: '%s'\n", strings->s);
	return (res);
}
