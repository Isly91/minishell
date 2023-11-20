/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 19:02:51 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/08 16:33:52 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd_command(t_main *main)
{
	if (!main)
		return ;
	if (getcwd(main->cwd, PATH_MAX))
	{
		if (ft_print_fd(main->cwd, main->fd[1]) == 0)
			ft_exit_code_change(main, 6);
		if (ft_print_fd("\n", main->fd[1]) == 0)
			ft_exit_code_change(main, 6);
	}
	else
		ft_exit_code_change(main, 8);
}
