/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:49:51 by labintei          #+#    #+#             */
/*   Updated: 2021/05/13 10:44:30 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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
	char	ecrit[1000];
	int		n;

	n = 0;
	if(argc == 3)
	{
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
	}
	write(1, "\n", 1);
}
