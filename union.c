/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:30:54 by labintei          #+#    #+#             */
/*   Updated: 2021/05/09 17:41:12 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(char *s)
{
	size_t		size;
	size = 0;
	while(s[size])
		size++;
	return(size);
}

char	ft_find(char c, char *s)
{
	int		i;

	i = -1;
	while(s[++i])
	{
		if(s[i] == c)
			return(c);
	}
	return(0);
}

int		main(int argc, char **argv)
{
	char	*ecrit;
	int		n;

	n = 0;
	if(argc == 3)
	{
		ecrit = malloc((sizeof(char) * ((ft_strlen(argv[1]) > ft_strlen(argv[2]))? ft_strlen(argv[1]) + 1 : ft_strlen(argv[2]) + 1)));
		while(*argv[1])
		{
			if(*argv[1] && !(ft_find(*argv[1],ecrit)))
			{
				write(1, &*argv[1], 1);
				ecrit[n] = *argv[1];
				n++;
			}
			argv[1]++;
		}
		while(*argv[2])
		{
			if(*argv[2] && !(ft_find(*argv[2],ecrit)))
			{
				write(1, &*argv[2], 1);
				ecrit[n] = *argv[2];
				n++;
			}
			argv[2]++;
		}
		ecrit[n] = '\0';
		while(*ecrit)
		{
			*ecrit = 0;
			ecrit++;
		}
		free(ecrit);
	}
	write(1, "\n", 1);
}
