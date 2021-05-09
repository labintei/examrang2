/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:49:51 by labintei          #+#    #+#             */
/*   Updated: 2021/05/09 17:40:37 by labintei         ###   ########.fr       */
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
			if(ft_find(*argv[1],argv[2]) && !(ft_find(*argv[1],ecrit)))
			{
				write(1, &*argv[1], 1);
				ecrit[n] = *argv[1];
				n++;
			}
			argv[1]++;
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
