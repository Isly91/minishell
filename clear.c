/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 11:48:57 by jvorstma      #+#    #+#                 */
/*   Updated: 2023/11/15 16:51:09 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_tenv(t_env **env)
{
	t_env	*buf;

	while (env && *env)
	{
		if ((*env)->key)
			free ((*env)->key);
		if ((*env)->value)
			free ((*env)->value);
		buf = *env;
		*env = (*env)->next;
		if (buf)
			free(buf);
	}
	if (env)
		free (env);
}

void	ft_free_token_struct(t_main *main)
{
	t_tokens	*buf;

	while (main->token)
	{
		ft_free_single_array(main->token->input_pipe);
		ft_free_double_array(main->token->parameters);
		ft_free_single_array(main->token->file);
		ft_free_single_array(main->token->redirection);
		if (main->token->fd_buf > 2)
			close (main->token->fd_buf);
		buf = main->token;
		main->token = main->token->next_token;
		if (buf)
			free (buf);
	}
}

void	ft_free_main(t_main *main)
{
	if (main)
	{
		ft_free_tenv(main->env_parameters);
		ft_free_token_struct(main);
		ft_free_single_array(main->prompt);
		ft_free_double_array(main->double_array_env_char);
		if (main->fd[0] > 2)
			close (main->fd[0]);
		if (main->fd[1] > 2)
			close (main->fd[1]);
		free(main);
	}
	rl_clear_history();
}

int	ft_last_clean_out(char *input, t_main *main)
{
	ft_free_single_array(input);
	ft_free_main(main);
	rl_clear_history();
	return (0);
}

void	ft_check_arg(char **argv)
{
	printf("Please use %s without arguments!\n", argv[0]);
	exit(127);
}
