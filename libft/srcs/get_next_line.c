/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparviai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:42:34 by eparviai          #+#    #+#             */
/*   Updated: 2019/11/21 15:42:35 by eparviai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	buffer_to_line(char *file[], const int fd, char **out)
{
	char	*leftover;
	size_t	length;

	if (ft_strchr(file[fd], '\n'))
	{
		length = ft_strlen_chr(file[fd], '\n');
		*out = ft_strsub(file[fd], 0, length);
		if (file[fd][length + 1] != '\0')
		{
			leftover = ft_strdup(&file[fd][length + 1]);
			ft_strdel(&file[fd]);
			file[fd] = leftover;
		}
		else
			ft_strdel(&file[fd]);
	}
	else
	{
		*out = ft_strdup(file[fd]);
		ft_strdel(&file[fd]);
	}
	return (1);
}

int			get_next_line(const int fd, char **out)
{
	static char	*file[2048];
	char		buffer[BUFF_SIZE + 1];
	long		bytes;
	char		*combined;

	while (out != NULL && ((bytes = read(fd, buffer, BUFF_SIZE)) > 0))
	{
		buffer[bytes] = '\0';
		if (file[fd] == NULL)
			file[fd] = ft_strnew(0);
		combined = ft_strjoin(file[fd], buffer);
		ft_strdel(&file[fd]);
		file[fd] = combined;
		if (ft_strchr(combined, '\n'))
			return (buffer_to_line(file, fd, out));
	}
	if (bytes < 0 || fd < 0 || out == NULL)
		return (-1);
	else if ((bytes == 0) && (file[fd] != NULL))
		return (buffer_to_line(file, fd, out));
	else
	{
		*out = NULL;
		return (0);
	}
}
