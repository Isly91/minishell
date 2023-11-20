/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 14:14:51 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/07 10:16:17 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	begin(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1 && s1[i] && set && set[i])
	{
		if ((unsigned char) s1[j] == (unsigned char) set[i])
		{
			j++;
			i = -1;
		}
		i++;
	}
	return (j);
}

static int	end(char const *s1, char const *set)
{
	int	i;
	int	k;
	int	size;

	i = 0;
	k = 0;
	size = ft_strlen(s1) - 1;
	while (s1 && s1[i] && set && set[i])
	{
		if ((unsigned char) s1[size - k] == (unsigned char) set[i])
		{
			k++;
			i = -1;
		}
		i++;
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*am;
	int		numb;
	int		len;
	int		i;

	numb = begin(s1, set);
	if (numb < (int) ft_strlen(s1))
		len = (ft_strlen(s1) - end(s1, set));
	else
		len = ft_strlen(s1);
	i = 0;
	am = (char *) malloc((len - numb + 1) * sizeof(char));
	if (!am)
		return (NULL);
	while (numb + i < len && s1 && s1[numb + i])
	{
		am[i] = (char) s1[numb + i];
		i++;
	}
	if (len == numb + i)
		am[i] = '\0';
	return (am);
}
