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

static void	ft_update_last_command(t_main *main)
{
	t_tokens	*b;
	int			i;

	if (!main || !main->token)
		return ;
	b = main->token;
	while (b && b->next_token && b->next_token->parameters
		&& b->next_token->parameters[0])
		b = b->next_token;
	i = -1;
	while (b->parameters && b->parameters[i + 1])
		i++;
	if (i == -1)
		i = 0;
	if (b && b->parameters && b->parameters[i])
		ft_update_env_value(main, "_", b->parameters[i]);
}

static void	ft_commands_input(char *input, t_main *main)
{
	char		*buf;

	if (!main)
		return ;
	buf = ft_strdup(input);
	if (ft_check_trim(buf, main) == 0)
	{
		ft_free_single_array(buf);
		main->exit_code = 2;
		return ;
	}
	ft_free_single_array(buf);
	ft_update_last_command(main);
	ft_execute(main);
}

static void	ft_reset_for_new_input(char *input, t_main *main)
{
	char	*buf;

	ft_free_single_array(input);
	if (main)
	{
		main->old_exit_code = main->exit_code;
		main->num_p = 0;
		if (main->fd[0] > 2)
			close (main->fd[0]);
		main->fd[0] = 0;
		if (main->fd[1] > 2)
			close (main->fd[1]);
		main->fd[1] = 1;
		main->exit_code = 0;
		ft_free_token_struct(main);
		main->token = NULL;
		ft_free_single_array(main->prompt);
		buf = ft_strjoin("minishell:", main->cwd);
		main->prompt = ft_strjoin(buf, "$ ");
		ft_free_single_array(buf);
	}
}

static char	*ft_get_input(char *input)
{
	char	*buf;
	char	*buf2;

	if (!input)
		return (NULL);
	buf = ft_strtrim(input, " 	");
	if (input)
		free(input);
	input = buf;
	while (input && input[0] && input[ft_strlen(input) - 1] == '|')
	{
		buf = ft_strdup(input);
		ft_free_single_array(input);
		if (buf[0] == '|')
			return (buf);
		input = readline("> ");
		if (!input)
			return (ft_free_single_array(buf), NULL);
		buf2 = ft_strtrim(input, " 	");
		ft_free_single_array(input);
		input = ft_strjoin(buf, buf2);
		ft_free_single_array(buf);
		ft_free_single_array(buf2);
	}
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_main	*main;

	if (argc > 1)
		ft_check_arg(argv);
	main = ft_init_main(envp);
	ft_signal();
	while (main)
	{
		input = ft_get_input(readline(main->prompt));
		if (!input)
		{
			printf("exit\n");
			rl_clear_history();
			exit(main->old_exit_code);
		}
		if (input && *input)
		{
			ft_commands_input(input, main);
			add_history(input);
		}
		ft_reset_for_new_input(input, main);
	}
	return (ft_last_clean_out(input, main));
}
