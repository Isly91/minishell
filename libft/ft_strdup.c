/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 18:48:29 by jvorstma      #+#    #+#                 */
/*   Updated: 2023/05/09 13:00:55 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*am;

	i = 0;
	if (!s1)
		return (NULL);
	am = (char *) malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!am)
		return (NULL);
	while (s1[i])
	{
		am[i] = s1[i];
		i++;
	}
	am[i] = '\0';
	return (am);
}
