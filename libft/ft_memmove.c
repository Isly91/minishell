/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 17:32:46 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/07 10:11:30 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	char		*s;
	size_t		i;

	d = (char *) dst;
	s = (char *) src;
	if (!dst && !src)
		return (NULL);
	if (s < d)
	{
		while (len-- != 0)
			d[len] = s[len];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
