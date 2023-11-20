/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 17:40:11 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/07 10:10:19 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*d1;
	char	*d2;

	d1 = (char *) s1;
	d2 = (char *) s2;
	while (n > 0)
	{
		if (*d1 != *d2)
			return ((unsigned char) *d1 - (unsigned char) *d2);
		else
		{
			d1++;
			d2++;
			n--;
		}
	}
	return (0);
}
