/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:41:27 by labintei          #+#    #+#             */
/*   Updated: 2021/05/10 11:08:00 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		get_next_line(char **line)
{
	int		ret;
	int		i;
	int		buf;

	i = 0;
	buf = 0;
	ret = 0;
	*line = malloc(1000000);
	while((ret = read(0,(char *)&buf, 1) == 1) && buf != '\n')
		(*line)[i++] = buf;
	(*line)[i] = '\0';
	return(ret);
}
