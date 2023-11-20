/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 09:14:51 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/17 13:17:50 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_write_here_doc(char *s, int i)
{
	write(i, s, ft_strlen(s));
	write(i, "\n", 1);
	ft_free_single_array(s);
}

static void	ft_child_process_here_doc(t_main *main, int *pipe_fd, int i)
{
	char	*maybe_command;

	ft_child_signal();
	if (!pipe_fd || !main)
		exit(1);
	close(pipe_fd[0]);
	while (1)
	{
		maybe_command = readline("> ");
		if (!maybe_command || ft_strcmp(maybe_command, main->token->file) == 0)
		{
			close(pipe_fd[1]);
			ft_free_single_array(maybe_command);
			exit(0);
		}
		i = 0;
		while (maybe_command && maybe_command[i])
		{
			if (maybe_command[i] == '$')
				maybe_command = ft_expand_check(maybe_command, &i, main);
			i++;
		}
		ft_write_here_doc(maybe_command, pipe_fd[1]);
	}
}

void	ft_here_document(t_main *main)
{
	int		status;
	pid_t	child_pid;
	int		pipe_fd[2];

	if (!main || !main->token || !main->token->file)
		return (ft_exit_code_change(main, 9));
	if (pipe(pipe_fd) == -1)
		return (ft_exit_code_change(main, 9));
	ft_sigign();
	child_pid = fork();
	if (child_pid == 0)
		ft_child_process_here_doc(main, pipe_fd, 0);
	else if (child_pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(child_pid, &status, 0);
		if (main->exit_code == 0)
			main->exit_code = status / 256;
	}
	else
		perror("fork");
	if (main->fd[0] > 2)
		close(main->fd[0]);
	main->fd[0] = pipe_fd[0];
	ft_signal();
}

void	ft_here_document_pipe(t_main *main)
{
	int		status;
	pid_t	child_pid;
	int		pipe_fd[2];

	if (!main || !main->token || !main->token->file)
		return (ft_exit_code_change(main, 9));
	if (pipe(pipe_fd) == -1)
		return (ft_exit_code_change(main, 9));
	ft_sigign();
	child_pid = fork();
	if (child_pid == 0)
		ft_child_process_here_doc(main, pipe_fd, 0);
	else if (child_pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(child_pid, &status, 0);
		main->exit_code = status / 256;
	}
	else
		perror("fork");
	main->token->fd_buf = pipe_fd[0];
	ft_signal();
}
