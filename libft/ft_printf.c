/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 12:48:33 by jvorstma      #+#    #+#                 */
/*   Updated: 2023/04/25 17:48:49 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnum(char c, va_list arguments)
{
	char			*set;
	int				num;

	set = "0123456789";
	if (c == 'c')
		return (ft_putchar(va_arg(arguments, int)));
	if (c == 's')
		return (ft_putstr(va_arg(arguments, char *)));
	num = va_arg(arguments, int);
	if (c == 'd' || c == 'i')
	{
		if (num == -2147483648)
			return (ft_putstr("-2147483648"));
		if (num < 0)
		{
			ft_putchar('-');
			return (ft_putbnum(-num, set, 10), ft_count(-num, 10) + 1);
		}
		return (ft_putbnum(num, set, 10), ft_count(num, 10));
	}
	return (0);
}

int	ft_hexus(char c, va_list arguments)
{
	char	*set;
	size_t	num;

	set = "0123456789abcdef";
	if (c == 'p')
	{
		num = (unsigned long long) va_arg(arguments, void *);
		ft_putstr("0x");
		return (ft_putbnum(num, set, 16), ft_count(num, 16) + 2);
	}
	num = va_arg(arguments, unsigned int);
	if (c == 'u')
		return (ft_putbnum(num, set, 10), ft_count(num, 10));
	if (c == 'x')
		return (ft_putbnum(num, set, 16), ft_count(num, 16));
	set = "0123456789ABCDEF";
	if (c == 'X')
		return (ft_putbnum(num, set, 16), ft_count(num, 16));
	return (0);
}

int	ft_printf(const char *c, ...)
{
	int		count;
	va_list	arguments;

	va_start(arguments, c);
	count = 0;
	while (*c)
	{
		if (*c == '%')
		{
			if (!*++c)
				break ;
			if (*c == '%')
				count += ft_putchar('%');
			if (*c == 'c' || *c == 's' || *c == 'd' || *c == 'i')
				count += ft_strnum(*c, arguments);
			if (*c == 'x' || *c == 'X' || *c == 'p' || *c == 'u')
				count += ft_hexus(*c, arguments);
		}
		else
			count += ft_putchar(*c);
		c++;
	}
	va_end(arguments);
	return (count);
}
