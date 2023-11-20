/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 17:38:01 by jvorstma      #+#    #+#                 */
/*   Updated: 2023/04/26 12:00:38 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (s1 && s2 && s1[i] && s2[i] && n > 0)
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		n--;
		i++;
	}
	if (n > 0 && s1 && s2 && (s1[i] == 0 || s2[i] == 0))
		return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	if (!s1 && s2)
		return (-1);
	if (!s2 && s1)
		return (1);
	return (0);
}
