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

static char	*ft_get_values(char **key_values)
{
	char	*buf;
	char	*buf2;

	if (!key_values || !key_values[1])
		return (NULL);
	if (key_values[1] && !key_values[2])
		return (ft_strdup(key_values[1]));
	if (key_values[1] && key_values[2])
	{
		buf = ft_strjoin(key_values[1], "=");
		buf2 = ft_strjoin(buf, key_values[2]);
		free(buf);
		return (buf2);
	}
	else
		return (NULL);
}

static void	ft_update_shlvl(t_main *main, int shlvl)
{
	char	*buf;

	buf = ft_itoa(shlvl);
	ft_update_env_value(main, "SHLVL", buf);
	ft_free_single_array(buf);
}

static void	ft_fill_env_stack(char **envp, t_main *main)
{
	int		i;
	int		j;
	char	**key_values;

	i = -1;
	j = -1;
	while (main && envp && envp[++i])
	{
		key_values = ft_split(envp[i], '=');
		if (key_values)
		{
			main->env_parameters[++j] = (t_env *)malloc(sizeof(t_env));
			if (!main->env_parameters[j])
				return (ft_free_double_array(key_values));
			main->env_parameters[j]->key = ft_strdup(key_values[0]);
			main->env_parameters[j]->value = ft_get_values(key_values);
			main->env_parameters[j]->next = NULL;
			if (j > 0)
				main->env_parameters[j - 1]->next = main->env_parameters[j];
		}
		ft_free_double_array(key_values);
	}
	ft_update_shlvl(main, main->shlvl);
}

static t_main	*ft_init_env(t_main *main, char **envp)
{
	int	i;

	i = 0;
	if (!envp || !main)
		return (main);
	main->env_size = ft_two_d_arr_len(envp);
	while (envp[i])
		i++;
	main->env_parameters = malloc((sizeof(t_env *) * main->env_size));
	if (!main->env_parameters)
		return (ft_free_main(main), NULL);
	ft_fill_env_stack(envp, main);
	ft_struct_to_char_double(main);
	return (main);
}

t_main	*ft_init_main(char **envp)
{
	t_main	*main;
	char	*buf;

	main = (t_main *)malloc(sizeof(t_main));
	if (!main)
		return (NULL);
	main->exit_code = 0;
	main->old_exit_code = 0;
	getcwd(main->cwd, PATH_MAX);
	main->path = main->cwd;
	buf = ft_strjoin("minishell:", main->cwd);
	main->prompt = ft_strjoin(buf, "$ ");
	ft_free_single_array(buf);
	main->shlvl = ft_atoi(getenv("SHLVL")) + 1;
	main->num_p = 0;
	main->fd[0] = 0;
	main->fd[1] = 1;
	main->double_array_env_char = NULL;
	main->token = NULL;
	main->env_size = 0;
	main->env_parameters = NULL;
	return (ft_init_env(main, envp));
}
