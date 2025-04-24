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

static int	ft_next_pipe(char *input, int i)
{
	if (!input)
		return (-1);
	while (input[i] && input[i] != '|')
	{
		if (input[i] == '"' || input[i] == '\'')
			i = ft_f_next_quote(input, input[i], i);
		if (i == -2)
			return (-1);
		i++;
	}
	return (i);
}

static int	ft_count_pipes(char *input)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	if (!input)
		return (-1);
	while (input[i])
	{
		if (input[i] == '|')
		{
			p++;
			if (i == 0)
				return (-2);
		}
		if (input[i] && (input[i] == '"' || input[i] == '\''))
			i = ft_f_next_quote(input, input[i], i);
		if (i == -2)
			return (-3);
		i++;
	}
	return (p);
}

static int	ft_check_valid_red(char *buf)
{
	int	i;

	i = -1;
	while (buf && buf[++i])
	{
		if (buf[i] == '"' || buf[i] == '\'')
			i = ft_f_next_quote(buf, buf[i], i);
		else if (buf[i] == '<' || buf[i] == '>')
			i = ft_check_smaller_bigger(buf, i);
		else if (buf[i] == '|')
		{
			i++;
			while (buf[i] && (buf[i] == ' ' || buf[i] == '\t'))
				i++;
			if (buf[i] && buf[i] == '|')
				return (ft_error_token_msg(buf[i]), 0);
			else
				i--;
		}
		if (i == -2)
			return (0);
	}
	return (1);
}

static void	ft_split_input_pipes(char *input, t_main *main)
{
	int		i;
	int		p;
	int		b;
	char	*buf;

	i = 0;
	p = 0;
	if (!input || !main)
		return ;
	while (p <= main->num_p)
	{
		b = i;
		i = ft_next_pipe(input, i);
		if (i < b)
			return ;
		buf = ft_substr(input, b, (i - b));
		ft_make_pipe_list(buf, main, p);
		ft_free_single_array(buf);
		i++;
		p++;
	}
	ft_make_red_structs(main);
}

int	ft_check_trim(char *input, t_main *main)
{
	char	*buf;

	if (!main || !input)
		return (0);
	buf = ft_strtrim(input, " 	");
	if (ft_check_quotes_closing(buf) == 0)
	{
		ft_print_fd(" Quote error\n", 2);
		return (ft_free_single_array(buf), 0);
	}
	if (!ft_check_valid_red(buf))
		return (ft_free_single_array(buf), 0);
	main->num_p = ft_count_pipes(buf);
	if (main->num_p == -2)
		ft_error_token_msg('|');
	if (main->num_p == -3)
		ft_print_fd(" Quote error\n", 2);
	if (main->num_p < 0)
		return (ft_free_single_array(buf), 0);
	ft_split_input_pipes(buf, main);
	ft_free_single_array(buf);
	return (1);
}
