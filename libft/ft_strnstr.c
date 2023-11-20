/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 14:27:40 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/07 10:16:27 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ih;
	size_t	in;

	ih = 0;
	if (needle[0] == '\0')
		return ((char *) haystack);
	while (haystack[ih] != '\0' && len > 0)
	{
		in = 0;
		while (haystack[in + ih] == needle[in] && len > in)
		{
			if (needle[in + 1] == '\0')
				return ((char *) &haystack[ih]);
			in++;
		}
		ih++;
		len--;
	}
	return (NULL);
}
