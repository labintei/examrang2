
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 18:05:23 by labintei          #+#    #+#             */
/*   Updated: 2021/05/13 15:03:37 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

typedef struct	s_flags
{
	char	i;
	int		largeur;
	char	precision;
	int		intprecision;
	char	type;
}				t_flags;

void	init_flags(struct s_flags *f)
{
	f->i = 0;
	f->largeur = 0;
	f->precision = 0;
	f->intprecision = 0;
	f->type = 0;
	return ;
}

char	ft_find(char c, char *s)
{
	int		n;

	n = -1;
	while(s[++n])
	{
		if(c == s[n])
			return(c);
	}
	return(0);
}

int		ft_putstr(char *s, int precision, char y)
{
	int		ret;

	ret  = 0;
	while(s[ret] && (ret < precision || precision == 0))
	{
		if(y == 1)
			ret += write(1, &s[ret], 1);
		else
			ret++;
	}
	return(ret);
}

int		ft_puthex(unsigned int u, char y)
{
	char	*s;
	int		i;
	char	c;

	i = 0;
	s = "0123456789abcdef";
	if(u / 16 != 0)
		i = ft_puthex(u / 16, y);
	c = s[u % 16];
	if(y == 1)
		i += write(1, &c, 1);
	else
		i += 1;
	return(i);
}

int		ft_putnbr(long int n, char y)
{
	int		i;
	char	c;
	long int	t;
	char		d;

	d = '-';
	t = n;
	i = 0;
	if(t < 0)
	{
		if(y == 1)
			write(1, &d, 1);
		t *= -1;
		i++;
	}
	if(t / 10 != 0)
		i += ft_putnbr(t / 10, y);
	c = t % 10 + '0';
	if(y == 1)
		i += write(1, &c , 1);
	else
		i += 1;
	return(i);
}

int		print_type(struct s_flags *f,long int d, unsigned int u, char *s, char y)
{
	int		i;

	i = 0;
	if(f->type == 's' && (f->precision != '.' || f->intprecision > 0))
		return(ft_putstr(s, f->intprecision, y));
	if(f->type == 'x' && (f->precision != '.' || u != 0))
		return(ft_puthex(u, y));
	if(f->type == 'd' && (f->precision != '.' || d != 0))
		return(ft_putnbr(d, y));
	return(i);
}

int		ft_largeur(struct s_flags *f, int size, char y)
{
	int		ret;
	int		sizebis;
	int		stock;

	stock = f->intprecision;
	sizebis = (f->type != 's' && size < f->intprecision && f->precision == '.')? f->intprecision : size;
	ret = 0;
	if(y == 0 && f->i != '-')
	{
		while(f->largeur > sizebis)
		{
			if(f->i == '0' && (f->intprecision <= 0 || f->precision != '.'))
				ret += write(1, "0", 1);
			else
				ret += write(1, " ", 1);
			f->largeur--;
		}
	}
	if(y == 2 && f->type != 's')
	{
		while(f->intprecision > size && f->precision == '.')
		{
			ret += write(1, "0", 1);
			f->intprecision--;
		}
	}
	f->intprecision = stock;
	if(y == 1 && f->i == '-')
	{
		while(f->largeur > sizebis)
		{	
			ret += write(1, " ", 1);
			f->largeur--;
		}
	}
	return(ret);
}

int		ft_print_type(struct s_flags *f, va_list ap)
{
	int		ret;
	int		size;
	unsigned int	u;
	long int		n;
	char			*s;
	char			neg;

	u = (f->type == 'x')? va_arg(ap, unsigned int) : 0;
	n = (f->type == 'd')? (long int)(va_arg(ap, int)) : 0;
	s = (f->type == 's')? va_arg(ap, char*) : "";
	s = (!s) ? "(null)" : s;
	size = print_type(f, n, u, s, 0);
	ret = 0;
	neg = (n < 0)? 1 : 0;
	if(n < 0 && f->i == '0' && !(f->intprecision > 0 && f->precision == '.'))
	{
		ret += write(1, "-", 1);
		n *= -1;
		size--;
	}
	ret += ft_largeur(f, size, 0);
	if(n < 0 && f->intprecision > 0 && f->precision == '.')
	{
		ret += write(1, "-", 1);
		n *= -1;
		size--;
	}
	ret += ft_largeur(f, size, 2);
	ret += print_type(f, n, u, s, 1);
	ret += ft_largeur(f, size + neg, 1);
	return(ret);
}

int		printflags(const char *s, va_list ap,int *n)
{
	struct s_flags	f;

	(*n)++;
	init_flags(&f);
	while (ft_find(s[(*n)],"0"))
	{
		f.i = '0';
		++(*n);
	}
	while(ft_find(s[(*n)], "-"))
	{
		f.i = '-';
		++(*n);
	}
	while(ft_find(s[(*n)], "0123456789"))
	{
		f.largeur = (f.largeur * 10) + (s[*n] - '0');
		++(*n);
	}
	if(ft_find(s[(*n)],"."))
	{
		f.precision = '.';
		++(*n);
	}
	while(ft_find(s[(*n)], "0123456789"))
	{
		f.intprecision = (f.intprecision * 10) + (s[*n] - '0');
		++(*n);
	}
	if(ft_find(s[(*n)], "sxd"))
	{	
		f.type = s[*n];
		(*n)++;
		return(ft_print_type(&f, ap));
	}
	return(0);
}

int		ft_printf(const char *s, ...)
{
	va_list		ap;
	int			ret;
	int			n;

	ret = 0;
	n = 0;
	va_start(ap, s);
	while(s[n])
	{
		if(s[n] && s[n] == '%')
		{
			ret += printflags(s, ap, &n);
		}
		if(s[n] && s[n] != '%')
		{
			ret += write(1, &s[n], 1);
			n++;
		}
	}
	va_end(ap);
	return (ret);
}
