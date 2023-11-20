/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   other_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 18:02:02 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/16 09:57:26 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_acces_handle(char *str, t_main *main, char **cmd, int i)
{
	if (!main || !cmd || !str)
		return ;
	ft_struct_to_char_double(main);
	if (i == 1 && execve(str, cmd, main->double_array_env_char) == -1)
		ft_print_fd(" No such file or directory\n", 2);
	else
		execve(str, cmd, main->double_array_env_char);
}

static void	ft_command_not_found(char **cmd, t_main *main)
{
	struct stat	file_info;

	if (!main || !cmd)
		return ;
	stat(cmd[0], &file_info);
	if (access(cmd[0], F_OK) == 0 && !S_ISDIR(file_info.st_mode))
	{
		ft_print_fd(" command not found\n", 2);
		exit(127);
	}
	else
	{
		ft_print_fd(cmd[0], 2);
		ft_print_fd(": command not found\n", 2);
		exit (127);
	}
}

static void	ft_check_exec(char **cmd, t_main *main)
{
	struct stat	file_info;
	char		*str;

	if (!cmd || !cmd[0])
		return ;
	str = cmd[0];
	if (str && str[0] && str[1] && (str[0] == '.' && str[1] == '/'))
		str = str + 2;
	if (stat(str, &file_info) == 0)
	{
		if (S_ISDIR(file_info.st_mode))
			ft_print_fd(" Is a directory\n", 2);
		else if (access(str, X_OK) != 0 && stat(str, &file_info) == 0
			&& !S_ISDIR(file_info.st_mode))
			ft_print_fd(" Permission denied\n", 2);
		else if (access(str, X_OK) == 0 && stat(str, &file_info) == 0
			&& !S_ISDIR(file_info.st_mode))
			ft_acces_handle(str, main, cmd, 0);
		exit (126);
	}
	else
		ft_print_fd(" No such file or directory\n", 2);
	exit (127);
}

static void	ft_child_process(char **cmd, t_main *main, char	*exec_path)
{
	char	*str;

	if (!main || !cmd || !cmd[0])
		exit (1);
	ft_child_signal();
	str = cmd[0];
	if (dup2(main->fd[1], STDOUT_FILENO) == -1)
		exit(0);
	if (dup2(main->fd[0], STDIN_FILENO) == -1)
		exit (0);
	if (str[0] == '/' || (str[0] == '.' && str[1] == '/'))
		ft_check_exec(cmd, main);
	if (execve(exec_path, cmd, main->double_array_env_char) == -1)
	{
		if (exec_path == NULL)
			ft_acces_handle(str, main, cmd, 1);
		else
			ft_command_not_found(cmd, main);
	}
	exit(0);
}

void	ft_execute_other_commands(t_main *main, char **cmd)
{
	pid_t	child_pid;
	int		status;
	char	*ex_path;

	if (!main || !cmd)
		return (ft_exit_code_change(main, 1));
	ex_path = ft_create_ex_path(cmd[0], main);
	ft_sigign();
	child_pid = fork();
	if (child_pid == 0)
		ft_child_process(cmd, main, ex_path);
	else if (child_pid > 0)
	{
		waitpid(child_pid, &status, 0);
		other_command_status(main, status);
	}
	else
		ft_exit_code_change(main, errno);
	ft_signal();
	ft_free_single_array(ex_path);
}
