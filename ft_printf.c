/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 18:05:23 by labintei          #+#    #+#             */
/*   Updated: 2021/05/09 23:53:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

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
	c = s[u % 16] + '0';
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

	i = 0;
	if(n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if(n / 10 != 0)
		i += ft_putnbr(n / 10, y);
	c = n % 10 + '0';
	if(y == 1)
		i += write(1, &c , 1);
	else
		i += 1;
	return(i);
}

int		print_type(struct s_flags *f,long int d, unsigned int u, char *s)
{
	int		i;

	i = 0;
	if(f->type == 's')
		return(ft_putstr(s, f->intprecision, 1));
	if(f->type == 'x')
		return(ft_puthex(u, 1));
	if(f->type == 'd')
		return(ft_putnbr(d, 1));
	return(i);
}


int		calcul_size(struct s_flags *f, long int d, unsigned int h, char *s)
{
	if(f->type == 's')
		return(ft_putstr(s,f->intprecision,0));
	if(f->type == 'd')
		return(ft_putnbr(d, 0));
	if(f->type == 'x')
		return(ft_puthex(h, 0));
	return(0);
}

int		ft_largeur(struct s_flags *f, int size, char y)
{
	int		ret;
	int		sizebis;

	sizebis = (f->type != 's' && size < f->intprecision && f->precision == '.')? f->intprecision : size;
	ret = 0;
	if(y == 0 && f->i != '-')
	{
		while(f->largeur > sizebis)
		{
			if(f->i == '0')
				ret += write(1, "0", 1);
			else
				ret += write(1, " ", 1);
			f->largeur--;
		}
	}
	if(y == 2 && f->type != 's')
	{
		while(f->intprecision > size && f->precision == '.')
			ret += write(1, "0", 1);
	}
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

	u = (f->type == 'x')? va_arg(ap, unsigned int) : 0;
	n = (f->type == 'd')? (long int)(va_arg(ap, int)) : 0;
	s = (f->type == 's')? va_arg(ap, char*) : "";
	size = calcul_size(f, n, u, s);
	ret = 0;
	if(f->type == 'd' && n < 0 && (f->i == '0' || (f->intprecision > size && f->precision == '.')))
	{
		ret += write(1, "-", 1);
		n *= -1;
	}
	ret += ft_largeur(f, size, 0);
	ret += ft_largeur(f, size, 2);
	ret += print_type(f, n, u, s);
	ret += ft_largeur(f, size, 1);
	return(ret);
}

int		printflags(const char *s, va_list ap,int *n)
{
	struct s_flags	f;

	(*n)++;
	init_flags(&f);
	while (s[*n] && s[*n] == '0')
	{
		f.i = '0';
		(*n)++;
	}
	while(s[*n] && s[*n] == '-')
	{
		f.i = '-';
		(*n)++;
	}
	while(s[*n] && (s[*n] == '0' || s[*n] == '1' || s[*n] == '2' || s[*n] == '3' || s[*n] == '4' || s[*n] == '5' || s[*n] == '6' || s[*n] == '7' || s[*n] == '8' || s[*n] == '9'))
	{
		f.largeur = (f.largeur * 10) + (s[*n] - '0');
		(*n)++;
	}
	if(s[*n] && s[*n] == '.')
	{
		f.precision = '.';
		(*n)++;
	}
	while(s[*n] && (s[*n] == '0' || s[*n] == '1' || s[*n] == '2' || s[*n] == '3' || s[*n] == '4' || s[*n] == '5' || s[*n] == '6' || s[*n] == '7' || s[*n] == '8' || s[*n] == '9'))
	{
		f.intprecision = (f.intprecision * 10) + (s[*n] - '0');
		(*n)++;
	}
	if(s[*n] && (s[*n] == 's' || s[*n] == 'd' || s[*n] == 'x'))
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

/*
int		main(void)
{
	ft_printf("testtt %-45.6s ", "Lauranne");
	return(1);
}*/
