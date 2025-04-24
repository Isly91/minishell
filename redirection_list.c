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

static char	**ft_change_parameters(t_main *main, char **param)
{
	char	**str;

	str = NULL;
	if (param)
		str = ft_parse_params(param, main);
	if (str)
		ft_free_double_array(param);
	return (str);
}

static t_tokens	*ft_fill_struct(char **str, int i, t_main *main)
{
	t_tokens	*new_token;
	char		*buf;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_token)
		return (NULL);
	new_token->redirection = ft_strdup(str[i]);
	if (str[i + 1])
	{
		buf = ft_strdup(str[i + 1]);
		if (ft_strcmp(str[i], "<<"))
			buf = ft_expander(buf, main);
		new_token->file = ft_parse_quotes(buf);
	}
	else
		new_token->file = NULL;
	new_token->fd_buf = 0;
	new_token->parameters = ft_parse_params(str, main);
	new_token->next_token = NULL;
	new_token->input_pipe = NULL;
	return (new_token);
}

static t_tokens	*ft_new_structs(t_main *main, t_tokens *c, t_tokens *p)
{
	int			i;

	if (!main || !c || !c->parameters)
		return (NULL);
	i = 0;
	while (c->parameters[i])
	{
		if (ft_is_red(c->parameters[i]))
		{
			if (!p)
			{
				p = ft_fill_struct(c->parameters, i, main);
				main->token = p;
			}
			else
			{
				p->next_token = ft_fill_struct(c->parameters, i, main);
				p = p->next_token;
			}
		}
		i++;
	}
	return (p);
}

void	ft_make_red_structs(t_main *main)
{
	t_tokens	*curr;
	t_tokens	*prev;

	if (!main || !main->token)
		return ;
	curr = main->token;
	prev = NULL;
	while (curr)
	{
		prev = ft_new_structs(main, curr, prev);
		curr->parameters = ft_change_parameters(main, curr->parameters);
		if (prev)
		{
			prev->next_token = curr;
			prev = prev->next_token;
		}
		else
		{
			main->token = curr;
			prev = curr;
		}
		curr = curr->next_token;
	}
}
