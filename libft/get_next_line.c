/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:23:37 by hde-oliv          #+#    #+#             */
/*   Updated: 2021/07/06 19:08:11 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	newline_handler(char **string, char **line)
{
	int		i;
	char	*temp_str;

	i = 0;
	while ((*string)[i] != '\n')
		if ((*string)[i++] == '\0')
			return (0);
	(*string)[i] = 0;
	*line = ft_strdup(*string);
	temp_str = *string;
	*string = ft_strdup(&(*string)[i + 1]);
	free(temp_str);
	return (1);
}

static int	eof_handler(char **string, char **line)
{
	char	*temp_str;

	if (*string == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	if (newline_handler(string, line))
		return (1);
	*line = ft_strdup(*string);
	temp_str = *string;
	free(temp_str);
	*string = NULL;
	return (0);
}

static int	get_line(int fd, char **string, char *slice, char **line)
{
	char	*temp;
	int		read_val;

	read_val = read(fd, slice, BUFFER_SIZE);
	if (read_val == -1)
		return (-1);
	while (read_val > 0)
	{
		if (*string)
		{
			temp = *string;
			*string = ft_strjoin(*string, slice);
			free(temp);
		}
		else
			*string = ft_strdup(slice);
		if (newline_handler(string, line))
			return (1);
		ft_bzero(slice, BUFFER_SIZE + 1);
		read_val = read(fd, slice, BUFFER_SIZE);
	}
	return (eof_handler(string, line));
}

int	get_next_line(int fd, char **line)
{
	char			*slice;
	static char		*string;
	int				res;

	if (!line || BUFFER_SIZE <= 0)
		return (-1);
	slice = (char *) malloc(sizeof(char) * BUFFER_SIZE + 1);
	ft_bzero(slice, BUFFER_SIZE + 1);
	res = get_line(fd, &string, slice, line);
	free(slice);
	if (*line == NULL)
		return (-1);
	return (res);
}
