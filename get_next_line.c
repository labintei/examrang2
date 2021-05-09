/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:41:27 by labintei          #+#    #+#             */
/*   Updated: 2021/05/10 00:26:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		get_next_line(int fd, char **line)
{
	char		stock[100000];
	static int			n;
	int					i;
	int					c;

	c = -1;
	read(0, stock, 100000);
	if(stock < 0 || !line)
		return(-1);
	i = n;
	while(stock[n] != '\n' || stock[n] != '\0')
		n++;
	*line = malloc((sizeof(char)) * (n - i + 1));
	--i;
	while(stock[++i] != '\n' || stock[i] != '\0')
		*line[++c] = stock[i];
	*line[++c] = '\0';
	if(stock[n] == '\n')
	{
		n++;
		return(1);
	}
	else
		return(0);
}

void		ft_putstr(char *s)
{	
	int		i;

	i = -1;
	while(s[++i])
		write(1, &s[i], 1);
	return ;
}

int		main(int argc, char **argv)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(argv[1],O_RDONLY);
	while(get_next_line(fd, &line) == '1')
	{
		ft_putstr(line);
		ft_putstr("\n");
	}
	close(fd);
	return(0);
}
