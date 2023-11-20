/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 16:10:13 by jvorstma      #+#    #+#                 */
/*   Updated: 2023/08/16 19:40:34 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int n)
{
	int	i;
	int	k;

	i = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0 && n > -2147483648)
	{
		i++;
		k = -n;
	}
	else
		k = n;
	while (k / 10 >= 1)
	{
		k = k / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*am;
	int			size;
	long int	i;

	i = (long int) n;
	size = length(n);
	am = (char *) malloc((size + 1) * (sizeof(char)));
	if (am == NULL)
		return (NULL);
	am[size--] = '\0';
	if (i < 0)
	{
		am[0] = '-';
		i = -i;
	}
	if (i == 0)
		am[0] = i + 48;
	while (i >= 1)
	{
		am[size--] = i % 10 + 48;
		i = i / 10;
	}
	return (am);
}
