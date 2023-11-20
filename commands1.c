/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands1.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/13 10:41:49 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/17 13:48:50 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_which_command(t_main *main, char **cmd)
{
	if (!main || !cmd)
		return (ft_exit_code_change(main, 1));
	else if (main->exit_code != 0 || !cmd[0])
		return ;
	else if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo_command(main, cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_change_dir(main, cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd_command(main);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export_command(main, cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset_command(main, cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env_command(main, cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit_command(main, cmd);
	else
		ft_execute_other_commands(main, cmd);
}

void	ft_no_pipes(t_main *main)
{
	while (main && main->token)
	{
		if (!ft_strcmp(main->token->redirection, "end"))
			ft_which_command(main, main->token->parameters);
		else if (!ft_strcmp(main->token->redirection, "<<"))
			ft_here_document(main);
		else if (!ft_strcmp(main->token->redirection, "<"))
			ft_input_redirection(main);
		else if (!ft_strcmp(main->token->redirection, ">"))
			ft_output_redirection(main);
		else if (!ft_strcmp(main->token->redirection, ">>"))
			ft_append_output(main);
		main->token = main->token->next_token;
	}
}

void	ft_here_doc(t_main *main)
{
	t_tokens	*head;

	if (!main)
		return ;
	head = main->token;
	while (main->token)
	{
		if (!ft_strcmp(main->token->redirection, "<<"))
			ft_here_document_pipe(main);
		main->token = main->token->next_token;
	}
	main->token = head;
}

static void	ft_fd_swap(t_main *main)
{
	if (!main || !main->token)
		return ;
	if (main->token->fd_buf > 2)
	{
		if (main->fd[0] > 2)
			close(main->fd[0]);
		main->fd[0] = main->token->fd_buf;
	}
}

void	ft_redirections(t_main *main)
{
	while (main && main->token)
	{
		if (!ft_strcmp(main->token->redirection, "end"))
		{
			ft_which_command(main, main->token->parameters);
			break ;
		}
		else if (!ft_strcmp(main->token->redirection, "|"))
		{
			ft_which_command(main, main->token->parameters);
			break ;
		}
		else if (!ft_strcmp(main->token->redirection, "<"))
			ft_input_redirection(main);
		else if (!ft_strcmp(main->token->redirection, ">"))
			ft_output_redirection(main);
		else if (!ft_strcmp(main->token->redirection, ">>"))
			ft_append_output(main);
		else if (!ft_strcmp(main->token->redirection, "<<"))
			ft_fd_swap(main);
		main->token = main->token->next_token;
	}
}
