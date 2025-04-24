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

static char	*ft_get_var_value(t_main *main, char *key)
{
	t_env	*current;
	char	*value;
	char	*buf;

	value = NULL;
	if (!key || !main)
		return (NULL);
	if (key[0] == '?')
	{
		buf = ft_signal_buf(main);
		value = ft_strjoin(buf, ++key);
		ft_free_single_array(buf);
	}
	current = *main->env_parameters;
	while (current && !value)
	{
		if (ft_strcmp(current->key, key) == 0)
			value = ft_strtrim(current->value, " 	");
		current = current->next;
	}
	if (!value)
		value = ft_strdup("");
	return (value);
}

static char	*ft_get_new_str(char *str, int start, int end, char *var)
{
	char	*new_str;
	int		i;
	int		j;

	if (!str || !var)
		return (NULL);
	j = start + ft_strlen(var) + (ft_strlen(str) - end);
	new_str = (char *)malloc((j + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < start && str[j])
		new_str[i++] = str[j++];
	j = 0;
	while (var[j])
		new_str[i++] = var[j++];
	j = end;
	while (str[j])
		new_str[i++] = str[j++];
	new_str[i] = '\0';
	if (str)
		free (str);
	return (new_str);
}

static char	*ft_get_key(char *str)
{
	char	*key;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	if (!str)
		return (NULL);
	if (str[i] && str[i] == '$')
		i++;
	j = ft_strlen(str);
	if (str[i] && str[i] == '{' && str[j - 1] && str[j - 1] == '}')
	{
		i++;
		j--;
	}
	key = (char *)malloc((j - i + 1) * sizeof(char));
	if (!key)
		return (NULL);
	while (i < j)
		key[k++] = str[i++];
	key[k] = '\0';
	return (key);
}

static char	*ft_handle_var(char *str, int *j, char *buf, t_main *main)
{
	char	*var;
	char	*key;

	if (!str || !buf)
		return (NULL);
	key = ft_get_key(buf);
	if (ft_valid_key_name(key) || (key[0] && key[0] == '?' && !key[1]))
		var = ft_get_var_value(main, key);
	else
		var = ft_strdup("");
	if (!var)
		return (ft_free_single_array(key), NULL);
	str = ft_get_new_str(str, *j, (*j + ft_strlen(buf)), var);
	*j += ft_strlen(var) - 1;
	ft_free_single_array(var);
	ft_free_single_array(key);
	return (str);
}

char	*ft_expand_check(char *str, int *j, t_main *main)
{
	int		i;
	char	*buf;

	if (!main || !str)
		return (NULL);
	i = *j + 1;
	if (str[i] && str[i] == '$')
		while (str[*j + 1] && str[*j + 1] == '$')
			*j += 1;
	if (str[i] && (str[i] == '$' || str[i] == ' ' || str[i] == '	'))
		return (str);
	else if (str[i] && str[i] == '{')
		while (str[i] && str[i] != '}')
			i++;
	else if (str[i] && (str[i] == '_' || ft_isalpha(str[i])))
		while (str[i + 1] && (ft_isalpha(str[i + 1]) || ft_isdigit(str[i + 1])
				|| str[i + 1] == '_'))
			i++;
	else if (str[i] && (str[i] == '"' || str[i] == '\''))
		i--;
	buf = ft_substr(str, *j, (i - *j + 1));
	str = ft_handle_var(str, j, buf, main);
	return (ft_free_single_array(buf), str);
}
