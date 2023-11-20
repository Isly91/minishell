/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:53:43 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/09/07 18:30:46 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	len;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	len = (int)ft_strlen(s1);
	if (len != (int)ft_strlen(s2))
		return (-1);
	while (s1[i] && s2[i] && i < len)
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	if (s1[i] != s2[i])
		return (-1);
	return (0);
}

int	ft_equal_in_a_str(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
