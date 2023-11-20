/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 09:55:12 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/15 16:48:58 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pipes(t_main *main, int *pid, int i)
{
	int	pipe_fd[2];

	if (!main || !main->token || pipe(pipe_fd) == -1)
		return (ft_exit_code_change(main, 1));
	ft_sigign();
	pid[i] = fork();
	if (pid[i] == 0)
	{
		close(pipe_fd[0]);
		if (main->fd[1] > 2)
			close(main->fd[1]);
		main->fd[1] = pipe_fd[1];
		ft_child_signal();
		ft_redirections(main);
		close(pipe_fd[1]);
		exit(main->exit_code);
	}
	else if (pid[i] == -1)
		exit(1);
	close(pipe_fd[1]);
	if (main->fd[0] > 2)
		close(main->fd[0]);
	main->fd[0] = pipe_fd[0];
	ft_signal();
}

static	void	ft_end_child(t_main *main)
{
	ft_child_signal();
	ft_redirections(main);
	exit(main->exit_code);
}

static void	ft_end(t_main *main, int *pid_pipes)
{
	int			status;
	int			i;

	if (!main || !pid_pipes)
		return (ft_exit_code_change(main, 1));
	ft_sigign();
	pid_pipes[main->num_p] = fork();
	if (pid_pipes[main->num_p] == 0)
		ft_end_child(main);
	else if (pid_pipes[main->num_p] == -1)
		exit(1);
	else
	{
		i = -1;
		while (++i <= main->num_p)
		{
			close(main->fd[0]);
			waitpid(pid_pipes[i], &status, 0);
		}
		main->exit_code = status / 256;
	}
	ft_signal();
	free(pid_pipes);
}

static	void	exec_loop(t_main *main, int *pid_pipes)
{
	int	i;

	i = 0;
	while (i < main->num_p)
	{
		ft_pipes(main, pid_pipes, i);
		while (main->token && ft_strcmp(main->token->redirection, "|"))
		{
			if (!ft_strcmp(main->token->redirection, "end"))
				break ;
			main->token = main->token->next_token;
		}
		if (main->token && main->token->next_token)
			main->token = main->token->next_token;
		i++;
	}
}

void	ft_execute(t_main *main)
{
	t_tokens	*head;
	int			*pid_pipes;

	if (!main || !main->token)
		return (ft_exit_code_change(main, 1));
	head = main->token;
	pid_pipes = NULL;
	if (main->num_p > 0)
	{
		ft_here_doc(main);
		pid_pipes = (int *)malloc((main->num_p + 1) * sizeof(int));
		if (!pid_pipes)
			return (ft_exit_code_change(main, 1));
		exec_loop(main, pid_pipes);
		ft_end(main, pid_pipes);
	}
	else
		ft_no_pipes(main);
	main->token = head;
}
