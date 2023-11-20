/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 14:47:24 by jvorstma      #+#    #+#                 */
/*   Updated: 2023/08/25 19:07:45 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*am;

	am = (char *) malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (am == NULL)
		return (NULL);
	i = 0;
	while (s[i] != 0)
	{
		am[i] = f(i, s[i]);
		i++;
	}
	if (s[i] == 0)
		am[i] = '\0';
	return (am);
}
