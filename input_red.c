/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_red.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 15:36:18 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/13 10:46:52 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input_redirection(t_main *main)
{
	int	fd;

	fd = -1;
	if (!main || !main->token || !main->token->file)
		return (ft_exit_code_change(main, 9));
	if (access(main->token->file, F_OK) == 0)
	{
		if (access(main->token->file, R_OK) == 0)
			fd = open(main->token->file, O_RDONLY, 0644);
	}
	if (access(main->token->file, F_OK) != 0 || fd == -1)
	{
		which_error(main);
		if (fd > -1)
			close (fd);
		return ;
	}
	if (main->fd[0] > 2)
		close(main->fd[0]);
	main->fd[0] = fd;
}
