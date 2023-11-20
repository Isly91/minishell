/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:41:30 by jvorstma      #+#    #+#                 */
/*   Updated: 2023/04/26 12:32:15 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

int	ft_is_int(char *str)
{
	int	i;
	int	len;

	i = 0;
	if (!str)
		return (0);
	if (ft_is_n_int(str) == 0 && ft_is_p_int(str) == 0)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i] == '0')
		i++;
	len = ft_strlen(&str[i]);
	if (len > 10)
		return (0);
	else if (len == 10)
	{
		if (str[0] == '-' && ft_strncmp("2147483648", &str[i], len + 1) < 0)
			return (0);
		if (str[0] != '-' && ft_strncmp("2147483647", &str[i], len + 1) < 0)
			return (0);
	}
	return (1);
}

int	ft_is_p_int(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '+' && i == 0)
		i++;
	while (str && ft_isdigit(str[i]) == 1)
		i++;
	if (i != (int) ft_strlen(str))
		return (0);
	else
		return (1);
}

int	ft_is_n_int(char *str)
{
	if (!str || str[0] != '-')
		return (0);
	else
		str++;
	return (ft_is_p_int(str));
}
