/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:54:17 by apigeon           #+#    #+#             */
/*   Updated: 2021/12/01 17:10:46 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(int ac, char **av)
{
	int		fd;
	char	*s;

	if (ac < 2)
	{
		printf("No input file given !\n");
		return (1);
	}
	else if (ac > 2)
	{
		printf("Too many arguments !\n");
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	printf("FOPEN_MAX = %d\n", FOPEN_MAX);
	printf("File descriptor: %d\n", fd);
	s = get_next_line(fd);
	printf("%s", s);
	free(s);
	s = get_next_line(fd);
	printf("%s", s);
	free(s);
	//s = get_next_line(fd);
	//printf("%s", s);
	//free(s);
	close(fd);
	return (0);
}
