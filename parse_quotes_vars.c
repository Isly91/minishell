/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chdir_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 19:00:30 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/07 16:33:42 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_for_var(char *str)
{
	int	i;
	int	c;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
			{
				if (str[i] && str[i] == '$' && c == '"')
					return (1);
				i++;
			}
		}
		else if (str[i] == '$' && str[i + 1])
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_strip_quotes(char *str, int i, int j)
{
	int		k;
	char	*buf;

	if (!str)
		return (NULL);
	buf = (char *)malloc((ft_strlen(str) - 1) * sizeof(char));
	if (!buf)
		return (ft_free_single_array(str), NULL);
	k = 0;
	while (str[k] && k < j)
	{
		buf[k] = str[k];
		k++;
	}
	j++;
	while (str[j] && j < i)
		buf[k++] = str[j++];
	i++;
	while (str[i])
		buf[k++] = str[i++];
	buf[k] = '\0';
	ft_free_single_array(str);
	return (buf);
}

char	*ft_parse_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			j = i;
			i++;
			while (str[i] && str[i] != str[j])
				i++;
			if (str[i])
			{
				str = ft_strip_quotes(str, i, j);
				i -= 2;
			}
			else
				return (str);
		}
		i++;
	}
	return (str);
}

char	*ft_expander(char *str, t_main *main)
{
	int	i;
	int	k;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\'')
			i = ft_f_next_quote(str, str[i], i);
		else if (str[i] == '"')
		{
			k = ft_f_next_quote(str, str[i], i);
			while (str && str[++i] && str[i] != '"')
				if (str[i] == '$' && str[i + 1] && (i + 1) < k)
					str = ft_expand_check(str, &i, main);
		}
		else if (str[i] == '$' && str[i + 1])
			str = ft_expand_check(str, &i, main);
		if (!str || i == -2)
			return (str);
	}
	return (str);
}

char	*ft_exp_pars(char *str, t_main *main)
{
	char	*buf;

	buf = ft_strdup(str);
	if (ft_check_for_var(str))
		buf = ft_expander(buf, main);
	if (ft_check_for_quotes(str))
		buf = ft_parse_quotes(buf);
	return (buf);
}
