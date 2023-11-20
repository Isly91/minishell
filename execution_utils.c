/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/09 16:05:56 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/15 15:40:25 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_struct_to_char_double(t_main *main)
{
	char	*tmp;
	t_env	*current;
	char	**buf;
	int		i;

	i = 0;
	if (!main)
		return ;
	current = *main->env_parameters;
	buf = (char **)malloc(sizeof(char *) * (main->env_size + 1));
	if (!buf)
		return (ft_exit_code_change(main, 1));
	while (current)
	{
		tmp = ft_strjoin(current->key, "=");
		buf[i++] = ft_strjoin(tmp, current->value);
		ft_free_single_array(tmp);
		current = current->next;
	}
	buf[i] = NULL;
	ft_free_double_array(main->double_array_env_char);
	main->double_array_env_char = buf;
}

char	*ft_strjoin_path(char *executable_str, char *str)
{
	int		i;
	int		e;
	char	*str_joined;

	if (!executable_str || !str)
		return (NULL);
	e = (int)ft_strlen(executable_str) + (int)ft_strlen(str) + 1;
	str_joined = (char *)malloc((e + 1) * sizeof(char));
	if (!str_joined)
		return (ft_free_single_array(executable_str), NULL);
	e = 0;
	while (executable_str && executable_str[e])
	{
		str_joined[e] = executable_str[e];
		e++;
	}
	str_joined[e++] = '/';
	i = 0;
	while (str && str[i])
		str_joined[e++] = str[i++];
	str_joined[e] = '\0';
	ft_free_single_array(executable_str);
	return (str_joined);
}

static	char	*ft_create_path(char **executable_str, char *str, t_main *main)
{
	int		i;
	char	*final_path;

	i = 0;
	final_path = NULL;
	while (executable_str && executable_str[i])
	{
		executable_str[i] = ft_strjoin_path(executable_str[i], str);
		if (!executable_str[i])
		{
			ft_free_double_array(executable_str);
			ft_exit_code_change(main, 2);
			break ;
		}
		if (access(executable_str[i], F_OK) == 0)
		{
			final_path = ft_strdup(executable_str[i]);
			break ;
		}
		i++;
	}
	return (final_path);
}

char	*ft_create_ex_path(char *str, t_main *main)
{
	char	**executable_str;
	char	*final_path;

	final_path = NULL;
	main->path = ft_get_key_value(main, "PATH");
	if (main->path)
		executable_str = ft_split(main->path, ':');
	else
		return (NULL);
	final_path = ft_create_path(executable_str, str, main);
	ft_free_double_array(executable_str);
	if (!final_path)
		final_path = ft_strdup(str);
	return (final_path);
}
