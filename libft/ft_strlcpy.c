/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 17:54:49 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/09 11:16:49 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] != 0)
		i++;
	if (*src == 0 && dstsize != 0)
	{
		*dst = *src;
		return (i);
	}
	while (dstsize > 1 && *src != 0)
	{
		*dst = *src;
		dstsize--;
		dst++;
		src++;
	}
	if (dstsize >= 1)
		*dst = 0;
	return (i);
}
