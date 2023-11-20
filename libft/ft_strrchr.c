/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 17:38:24 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/07 10:16:00 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*d;

	d = NULL;
	while (*s != 0)
	{
		if (*s == (char) c)
			d = (char *) s;
		s++;
	}
	if (*s == (char) c)
		return ((char *) s);
	return (d);
}
