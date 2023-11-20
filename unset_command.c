/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 18:56:09 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/09/19 17:43:12 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_print_error(char *prompt, char *str1, char *str2, char *str3)
{
	int	x;

	x = ft_print_fd(prompt, 2);
	x *= ft_print_fd(": ", 2);
	x *= ft_print_fd(str1, 2);
	x *= ft_print_fd(": ", 2);
	x *= ft_print_fd(str2, 2);
	x *= ft_print_fd(": ", 2);
	x *= ft_print_fd(str3, 2);
	return (x);
}

static int	ft_unset_loop(t_main *main, char *prompt, char **cmd)
{
	int		i;

	i = 1;
	if (!main || !cmd)
		return (0);
	while (cmd && cmd[i])
	{
		if (ft_valid_key_name(cmd[i]) == 0)
			return (ft_print_error(prompt, cmd[0], cmd[i], "invalid option\n"));
		ft_search_remove_key_value(main, cmd[i]);
		i++;
	}
	return (1);
}

void	ft_unset_command(t_main *main, char **cmd)
{
	char	*prompt_trimmed;

	prompt_trimmed = ft_strtrim(main->prompt, " ");
	if (!prompt_trimmed)
		return (ft_exit_code_change(main, 2));
	if (ft_unset_loop(main, prompt_trimmed, cmd) == 0)
		ft_exit_code_change(main, 6);
	ft_free_single_array(prompt_trimmed);
}
