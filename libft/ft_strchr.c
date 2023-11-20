/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 17:38:35 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/10/19 18:47:17 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s != 0)
	{
		if (*s == (char) c)
			return ((char *) s);
		else
			s++;
	}
	if (*s == 0 && (char) c == 0)
		return ((char *) s);
	else
		return (0);
}
