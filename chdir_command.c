/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chdir_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 19:00:30 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/07 16:33:42 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle to many arguments
// static int	ft_print_error(t_main *main, char *s3)
// {
// 	char	*prompt_trimmed;
// 	int		x;

// 	if (!main || !main->token || !main->token->parameters)
// 		return (0);
// 	prompt_trimmed = ft_strtrim(main->prompt, " ");
// 	if (!prompt_trimmed)
// 		return (0);
// 	x = ft_print_fd(prompt_trimmed, 2);
// 	ft_free_single_array(prompt_trimmed);
// 	x *= ft_print_fd(": cd:", 2);
// 	x *= ft_print_fd(main->token->parameters[1], 2);
// 	x *= ft_print_fd(": ", 2);
// 	x *= ft_print_fd(s3, 2);
// 	x *= ft_print_fd("\n", 2);
// 	return (x);
// }

static void	ft_create_old_pwd(t_main *main)
{
	t_env	*tmp;

	if (!main)
		return ;
	tmp = malloc(sizeof(t_env));
	if (!tmp)
		return ;
	tmp->next = NULL;
	tmp->key = ft_strdup("OLDPWD");
	tmp->value = ft_strdup(main->cwd);
	ft_add_env_var(main, tmp);
}

static void	ft_change_pwd_oldpwd(t_main *main, char **cmd)
{
	if (!main)
		return ;
	if (cmd && cmd[1] && !ft_strcmp(cmd[1], "-"))
	{
		if (chdir(ft_get_key_value(main, "OLDPWD")) == -1)
		{
			ft_print_fd(" cd: OLDPWD not set\n", 2);
			main->exit_code = 1;
			return ;
		}
		else
		{
			ft_print_fd(ft_get_key_value(main, "OLDPWD"), main->fd[1]);
			ft_print_fd("\n", main->fd[1]);
		}
	}
	if (ft_check_if_key_exist(main, "OLDPWD", NULL) == 0)
		ft_create_old_pwd(main);
	else
		ft_update_env_value(main, "OLDPWD", main->cwd);
	getcwd(main->cwd, PATH_MAX);
	ft_update_env_value(main, "PWD", main->cwd);
	main->path = main->cwd;
	ft_struct_to_char_double(main);
}

void	ft_change_dir(t_main *main, char **cmd)
{
	if (!main || !cmd)
		return (ft_exit_code_change(main, 1));
	if (cmd[0] && cmd[1] && cmd[2])
	{
		ft_print_fd(" too many arguments\n", 2);
		main->exit_code = 1;
		return ;
	}
	if (!cmd[1] || (cmd[1] && !ft_strcmp(cmd[1], "~")))
	{
		if (chdir(ft_get_key_value(main, "HOME")) == -1)
		{
			ft_print_fd(" cd: HOME not set\n", 2);
			main->exit_code = 1;
			return ;
		}
	}
	if (cmd[1] && chdir(cmd[1]) == -1 && ft_strcmp(cmd[1], "-"))
	{
		ft_print_fd(" No such file or directory\n", 2);
		main->exit_code = 1;
		return ;
	}
	ft_change_pwd_oldpwd(main, cmd);
}
