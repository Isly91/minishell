/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 16:30:33 by jvorstma      #+#    #+#                 */
/*   Updated: 2023/11/17 13:35:28 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_file_permis(char *s)
{
	ft_print_fd("minishell: ", 2);
	ft_print_fd(s, 2);
	ft_print_fd(": Permission denied\n", 2);
}

void	ft_error_is_dir(char *s)
{
	ft_print_fd(s, 2);
	ft_print_fd(": Is a directory\n", 2);
}

void	ft_error_no_file_dir(char *s)
{
	ft_print_fd("minishell: ", 2);
	ft_print_fd(s, 2);
	ft_print_fd(": No such file or directory\n", 2);
}

void	ft_error_token_msg(char s)
{
	ft_print_fd(" syntax error near unexpected token `", 2);
	if (!s)
		ft_print_fd("newline", 2);
	else
		write(2, &s, 1);
	ft_print_fd("'\n", 2);
}
