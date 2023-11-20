/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 16:41:28 by jvorstma      #+#    #+#                 */
/*   Updated: 2023/11/15 17:57:08 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quotes_closing(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			i = ft_f_next_quote(input, input[i], i);
		if (i == -2)
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_for_quotes(char *str)
{
	int	i;
	int	x;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			x = str[i];
			i++;
			while (str[i] && str[i] != x)
				i++;
			if (str[i] && str[i] == x)
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_is_red(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "<"))
		return (1);
	else if (!ft_strcmp(str, "<<"))
		return (1);
	else if (!ft_strcmp(str, ">"))
		return (1);
	else if (!ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

int	ft_f_next_quote(char *input, int c, int i)
{
	if (!input)
		return (-2);
	i++;
	while (input[i] && input[i] != c)
		i++;
	if (!input[i] || input[i] != c)
		return (-2);
	return (i);
}

int	ft_get_var_brac(char *cmd, int i)
{
	if (!cmd)
		return (-2);
	if (cmd[i] && cmd[i] == '$')
	{
		i++;
		if (cmd[i] && cmd[i] == '{')
		{
			i++;
			while (cmd[i] && cmd[i] != '}')
				i++;
		}
	}
	return (i);
}
