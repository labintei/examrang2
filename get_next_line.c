/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:41:27 by labintei          #+#    #+#             */
/*   Updated: 2021/05/09 18:04:49 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<stdlib.h>

int		get_next_line(char **line)
{
	char		stock[100000];
	static int			n;
	int					i;
	int					c;
	char				*line;

	c = -1;
	stock = read(0, stock, 100000);
	if(stock < 0 || fd != 0)
		return(-1);
	i = n;
	while(stock[n] != '\n' || stock[n] != '\0')
		n++;
	line = malloc((sizeof(char)) * (n - i + 1));
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
