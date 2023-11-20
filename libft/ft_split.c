/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 14:19:06 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/07 10:13:10 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	freear(char **ar)
{
	int	i;

	i = 0;
	while (ar && ar[i])
	{
		free(ar[i]);
		i++;
	}
	if (ar)
		free(ar);
}

static int	wcount(char const *s, char c)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	if (s[i] == c)
	{
		if (s[i] == 0)
			return (0);
		i++;
	}
	while (s[i] != 0)
	{
		if (s[i] == c && s[i -1] != c)
			count++;
		i++;
		if (s[i] == 0 && s[i -1] != c)
			count++;
	}
	return (count);
}

static size_t	words(char const *s, char c, int i)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[i + len] != c && s[i + len])
		len++;
	return ((size_t) len);
}

char	**ft_split(char const *s, char c)
{
	char			**ar;
	unsigned int	i;
	int				j;
	size_t			len;

	if (!s)
		return (NULL);
	ar = (char **) malloc((wcount(s, c) + 1) * sizeof(char *));
	if (!ar)
		return (NULL);
	i = 0;
	j = 0;
	while (j < wcount(s, c))
	{
		while (s[i] == c)
			i++;
		len = words(s, c, i);
		ar[j] = ft_substr(s, i, len);
		if (!ar[j])
			return (freear(ar), NULL);
		i = i + len;
		j++;
	}
	ar[j] = 0;
	return (ar);
}
