/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:47:30 by marcsilv          #+#    #+#             */
/*   Updated: 2024/09/19 16:11:40 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(const char *file)
{
	char	*str;
	int		fd;
	int		lines;

	lines = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_error("Error opening file", NULL);
	str = get_next_line(fd);
	while (str)
	{
		lines++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

int	count_columns(const char *file)
{
	char	*str;
	int		fd;
	int		rows;
	int		i;

	rows = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_error("Error opening file", NULL);
	str = get_next_line(fd);
	while (str)
	{
		i = 0;
		while (str[i])
			i++;
		if (i > rows)
			rows = i;
		free(str);
		str = get_next_line(fd);
	}
	return (rows);
}

int	parse_map(const char *file, t_map *map)
{
	char	*str;
	int		fd;
	int		row;
	int		lines;

	row = 0;
	lines = count_lines(file);
	if (lines == -1)
		return (-1);
	map->matrix = malloc(sizeof(char *) * lines);
	map->matrix[lines] = NULL;
	if (!map->matrix)
		print_error("Error allocating memory", map);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_error("Error opening file", map);
	str = get_next_line(fd);
	while (str)
	{
		map->matrix[row] = str;
		row++;
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
}
