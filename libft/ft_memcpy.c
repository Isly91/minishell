/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 17:31:27 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/09 10:58:37 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;

	d = (char *) dst;
	s = (char *) src;
	if (!dst && !src)
		return (NULL);
	while (n != 0)
	{
		*d = *s;
		s++;
		d++;
		n--;
	}
	return (dst);
}
