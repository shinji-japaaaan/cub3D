/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/12 07:10:19 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_digit_str(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] && str[i] != ',' && str[i] != ' ')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_color_value(char *line, int *i)
{
	int		len;
	char	buffer[4];

	while (line[*i] == ' ')
		(*i)++;
	len = 0;
	while (ft_isdigit(line[*i]) && len < 3)
		buffer[len++] = line[(*i)++];
	buffer[len] = '\0';
	if (!is_digit_str(buffer))
		print_error_and_exit("Error: Invalid RGB format\n");
	return (ft_atoi(buffer));
}

void	check_color_range(int value)
{
	if (value < 0 || value > 255)
		print_error_and_exit("Error: RGB values out of range\n");
}
