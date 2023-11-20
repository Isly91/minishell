/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   output_red.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 19:41:31 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/13 10:27:02 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	which_error(t_main *main)
{
	struct stat	file_info;

	if (main->exit_code != 0)
		return ;
	if (access(main->token->file, F_OK) != 0)
		ft_error_no_file_dir(main->token->file);
	else if (stat(main->token->file, &file_info) == 0
		&& S_ISDIR(file_info.st_mode))
		ft_error_is_dir(main->token->file);
	else if (access(main->token->file, R_OK) != 0
		|| access(main->token->file, W_OK) != 0)
		ft_error_file_permis(main->token->file);
	main->exit_code = 1;
}

void	ft_output_redirection(t_main *main)
{
	int	fd;

	fd = -1;
	if (!main || !main->token || !main->token->file)
		return (ft_exit_code_change(main, 9));
	if (access(main->token->file, F_OK) == 0)
	{
		if (access(main->token->file, W_OK) == 0)
			fd = open(main->token->file, O_WRONLY | O_TRUNC);
	}
	else
		fd = open(main->token->file, O_WRONLY | O_CREAT, 0644);
	if (fd == -1 || access(main->token->file, F_OK) != 0)
	{
		which_error(main);
		if (fd > -1)
			close (fd);
		if (main->token->file)
			unlink(main->token->file);
		return ;
	}
	if (main->fd[1] > 2)
		close (main->fd[1]);
	main->fd[1] = fd;
}

void	ft_append_output(t_main *main)
{
	int	fd;

	fd = -1;
	if (!main || !main->token || !main->token->file)
		return (ft_exit_code_change(main, 9));
	if (access(main->token->file, F_OK) == 0)
	{
		if (access(main->token->file, W_OK) == 0)
			fd = open(main->token->file, O_WRONLY | O_APPEND);
	}
	else
		fd = open(main->token->file, O_WRONLY | O_CREAT, 0644);
	if (fd == -1 || access(main->token->file, F_OK) != 0)
	{
		which_error(main);
		if (fd > -1)
			close (fd);
		return ;
	}
	if (main->fd[1] > 2)
		close (main->fd[1]);
	main->fd[1] = fd;
}
