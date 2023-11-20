/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_command.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 18:54:21 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/10/31 17:15:29 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_print_error(char **cmd, char *s3)
{
	int	x;

	if (!cmd)
		return (0);
	x = ft_print_fd(cmd[0], 2);
	x *= ft_print_fd(": ", 2);
	x *= ft_print_fd(cmd[1], 2);
	x *= ft_print_fd(": ", 2);
	x *= ft_print_fd(s3, 2);
	x *= ft_print_fd("\n", 2);
	return (x);
}

void	ft_env_command(t_main *main, char **cmd)
{
	char		*exec_path;
	struct stat	file_info;

	if (!main || !cmd)
		return (ft_exit_code_change(main, 1));
	exec_path = ft_strjoin(main->path, cmd[1]);
	ft_update_env_value(main, "_", "/usr/bin/env");
	if (cmd && cmd[1])
	{
		if (stat(exec_path, &file_info) == 0 && S_ISDIR(file_info.st_mode))
		{
			if (ft_print_error(cmd, " Permission denied") == 0)
				return (ft_exit_code_change(main, 6));
			else
				ft_exit_code_change(main, 100);
		}
		else
		{
			if (ft_print_error(cmd, strerror(errno)) == 0)
				ft_exit_code_change(main, 6);
		}
	}
	else
		ft_print_list(*main->env_parameters, main->env_size, main);
	ft_free_single_array(exec_path);
}
