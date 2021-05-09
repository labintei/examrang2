/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 18:05:23 by labintei          #+#    #+#             */
/*   Updated: 2021/05/09 18:23:14 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

defi

int		ft_putstr(char *s, int p)
{
	int		n;

	n = -1;
	while(s[++n] && (n <= p || p == 0))
		write(1,&s[n],1);
	return(n);
}

int		ft_int()
{
	
}

int		ft_hexa(unsigned int res, char x)
{
	char *s;
	char *stock;
	int	 n;
	int	 i;

	n = -1;
	s = "0123456789abcdef";
	while((i = res % 16))
	{
		stock[++n] = s[i];
		n /= 16;
	}
	i = n;
	n++;
	while(--n >= 0)
		write(1,&stock[n], 1);
	return(i);
}

int		main(const char *s, ...)
{
	va_list		ap;
	int			ret;

	va_start(ap, char*);
	while(*s)
	{
		if(*s == '%')
		{
			
		}
		if(*s != '%')
		{
			ret += write(1, &*s, 1);
			s++;
		}
	}
	va_end(ap);
	return (ret);
}
