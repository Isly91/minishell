/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 17:40:02 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/07 10:10:01 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*d;

	d = (unsigned char *) s;
	while (n > 0 && d)
	{
		if (*d == (unsigned char) c)
			return ((void *) s);
		d++;
		n--;
		s++;
	}
	if (n > 0 && *d == (unsigned char) c)
		return ((void *) s);
	return (NULL);
}
