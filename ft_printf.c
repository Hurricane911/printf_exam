/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyim <joyim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:28:17 by joyim             #+#    #+#             */
/*   Updated: 2024/11/28 13:28:17 by joyim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// pass_tester
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
// #include <stdio.h>

void ft_putstr(char *str, int *count)
{
	if(!str)
	{
		write(1, "(null)", 6);
		(*count)+= 6;
		return ;
	}
	while(*str)
	{
		write(1, str, 1);
		str++;
		(*count)++;
	}
}

void ft_putnbr(int nbr, int *count)
{
	char c;
	if (nbr == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return ;
	}
	if(nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
		(*count)++;
	}
	if(nbr >= 10)
	{
		ft_putnbr(nbr/10, count);
	}
	c = nbr % 10 + 48;		
	(*count)++;
	
	write(1, &c, 1);
}

void ft_puthex(unsigned int nbr, int *count)
{
	char *base = "0123456789abcdef";

	if(nbr >= 16)
		ft_puthex(nbr/16, count);
	write(1, &base[nbr%16], 1);
	(*count)++;

}

int ft_printf(const char *operator , ... )
{
	va_list args;
	int count = 0;

	va_start(args, operator);

	while(*operator)
	{
		if(*operator == '%' && *(operator + 1))
		{
			operator++;
			if(*operator == 's')
				ft_putstr(va_arg(args, char *), &count);
			else if(*operator == 'd')
				ft_putnbr(va_arg(args, int), &count);
			else if(*operator == 'x')
				ft_puthex(va_arg(args, unsigned int), &count);
			else
			{
				write(1, operator, 1);
				count++;
			}
		}
		else
		{
			write(1, operator, 1);
			count++;
		}
		operator++;
	}

	va_end(args);
	return(count);
}	

// int main()
// {
// 	// int count = ft_printf("%s\n", "hello");
// 	// int count = ft_printf("%d\n", -2147483647);
// 	// int count = ft_printf("%d\n", 10);
// 	int count = ft_printf("%s\n", NULL);
// 	// int count = ft_printf("%d", -2147483648);

// 	ft_printf("%d", count);
// }