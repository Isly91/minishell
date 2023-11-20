/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 17:55:18 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/09 11:39:32 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (dst != NULL)
		i = ft_strlen(dst);
	else
		i = 0;
	k = ft_strlen(src);
	j = 0;
	while (src[j] && dstsize > i + j + 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (dstsize != 0 && dstsize >= i)
		dst[i + j] = 0;
	if (dstsize == 0 || dstsize < i)
		return (k + dstsize);
	else
		return (k + i);
}
