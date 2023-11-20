/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 11:43:18 by jvorstma      #+#    #+#                 */
/*   Updated: 2023/08/31 17:25:25 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num(const char *str, int i)
{
	int	num;

	num = 0;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;

	i = 0;
	s = 1;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if ((str[i] == '-' || str[i] == '+') && (ft_isdigit(str[i + 1])))
	{
		if (str[i] == '-')
			s = -s;
		i++;
		return (num(str, i) * s);
	}
	if (ft_isdigit(str[i]))
		return (num(str, i));
	else
		return (0);
}
