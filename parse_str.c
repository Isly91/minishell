/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 15:35:29 by jvorstma      #+#    #+#                 */
/*   Updated: 2023/11/17 13:32:44 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_smaller_bigger(char *buf, int i)
{
	char	c;

	if (!buf || !buf[i])
		return (-2);
	c = buf[i++];
	if (buf[i] && buf[i] == c)
		i++;
	while (buf[i] && (buf[i] == ' ' || buf[i] == '\t'))
		i++;
	if ((buf[i] && (buf[i] == '<' || buf[i] == '>'
				|| buf[i] == '|')) || !buf[i])
		return (ft_error_token_msg(buf[i]), -2);
	i--;
	return (i);
}

static char	**ft_parse_str(char **str, t_main *main, char **params)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (str && str[i])
	{
		if (ft_is_red(str[i]))
		{
			if (str[i + 1])
				i++;
		}
		else
		{
			params[c] = ft_exp_pars(str[i], main);
			if (params[c] && !params[c][0] && !ft_check_for_quotes(str[i]))
				ft_free_single_array(params[c]);
			else
				c++;
		}
		i++;
	}
	params[c] = NULL;
	return (params);
}

static int	ft_count_params(char **str, t_main *main, int c)
{
	int		i;

	(void)main;
	i = -1;
	while (str && str[++i])
	{
		if (ft_is_red(str[i]) && str[i + 1])
			i++;
		else if (!ft_is_red(str[i]))
			c++;
	}
	return (c);
}

char	**ft_parse_params(char **str, t_main *main)
{
	int		c;
	char	**params;

	if (!main || !str)
		return (NULL);
	c = ft_count_params(str, main, 0);
	if (c == -1)
		return (NULL);
	params = (char **)malloc((c + 1) * sizeof(char *));
	if (!params)
		return (NULL);
	params = ft_parse_str(str, main, params);
	return (params);
}
