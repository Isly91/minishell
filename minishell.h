/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 14:47:51 by jvorstma      #+#    #+#                 */
/*   Updated: 2023/11/17 13:51:01 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include "./libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_tokens
{
	char			*input_pipe;
	char			**parameters;
	char			*redirection;
	char			*file;
	int				fd_buf;
	struct s_tokens	*next_token;
}	t_tokens;

typedef struct s_main
{
	char		*prompt;
	char		*path;
	int			shlvl;
	char		cwd[PATH_MAX];
	t_env		**env_parameters;
	int			env_size;
	char		**double_array_env_char;
	int			exit_code;
	int			old_exit_code;
	int			num_p;
	int			fd[2];
	t_tokens	*token;
}	t_main;

//rl
void	rl_clear_history(void);
void	rl_replace_line(const char *text, int clear_undo);

//utils
int		ft_print_fd(char *str, int fd);
int		ft_strcmp(char *s1, char *s2);
char	*ft_create_ex_path(char *str, t_main *main);
int		ft_equal_in_a_str(char *str);
void	ft_print_char_double(t_main *main, char **env_parameters);
void	ft_struct_to_char_double(t_main *main);
void	ft_print_list(t_env *env_parameters, int size, t_main *main);

//signals
void	ft_signal(void);
void	ft_child_signal(void);
void	ft_sigign(void);
char	*ft_signal_buf(t_main *main);

//commands
void	ft_execute_other_commands(t_main *main, char **cmd);
void	ft_exit_command(t_main *main, char **cmd);
void	ft_env_command(t_main *main, char **cmd);
void	ft_unset_command(t_main *main, char **cmd);
void	ft_export_command(t_main *main, char **cmd);
void	ft_echo_command(t_main *main, char **cmd);
void	ft_change_dir(t_main *main, char **cmd);
void	ft_pwd_command(t_main *main);
void	ft_which_command(t_main *main, char **cmd);
void	ft_no_pipes(t_main *main);
void	ft_here_doc(t_main *main);
void	ft_redirections(t_main *main);
void	other_command_status(t_main *main, int status);

//sizes
int		ft_executable_path_size(char	**executable_path);
int		ft_two_d_arr_len(char	**str);
int		ft_len_param(char **str, t_main *main, int i, int x);

//init
t_main	*ft_init_main(char **envp);

//env
void	ft_search_remove_key_value(t_main *main, char	*key);
int		ft_check_if_key_exist(t_main *main, char *keys, char *values);
char	*ft_get_key_value(t_main *main, char *key);
void	ft_add_env_var(t_main *main, t_env *new_struct);
void	ft_update_env_key(t_main *main, char **keys_values);
void	ft_update_env_value(t_main *main, char *key, char *new_value);
int		ft_valid_key_name(char *key);

//free and error
void	ft_free_single_array(char *arr);
void	ft_free_double_array(char **arr);
void	ft_free_main(t_main *main);
void	ft_exit_code_change(t_main *main, int x);
void	ft_free_double_int(int **x);
void	ft_free_token_struct(t_main	*main);
void	which_error(t_main *main);
void	ft_error_is_dir(char *s);
void	ft_error_file_permis(char *s);
void	ft_error_no_file_dir(char *s);
void	ft_error_token_msg(char s);
void	ft_check_arg(char **argv);
int		ft_last_clean_out(char *input, t_main *main);

//parse
int		ft_check_trim(char *input, t_main *main);
char	*ft_expand_check(char *str, int *j, t_main *main);
int		ft_f_next_quote(char *input, int c, int i);
void	ft_make_pipe_list(char *buf, t_main *main, int p);
void	ft_make_red_structs(t_main *main);
char	*ft_expander(char *str, t_main *main);
char	*ft_parse_quotes(char *str);
char	**ft_parse_params(char **str, t_main *main);
char	*ft_exp_pars(char *str, t_main *main);
int		ft_is_red(char *str);
int		ft_check_for_var(char *str);
int		ft_check_for_quotes(char *str);
int		ft_check_quotes_closing(char *input);
int		ft_check_smaller_bigger(char *buf, int i);
int		ft_get_var_brac(char *cmd, int i);

//redirections and pipes
void	ft_execute(t_main *main);
void	ft_input_redirection(t_main *main);
void	ft_output_redirection(t_main *main);
void	ft_here_document(t_main *main);
void	ft_here_document_pipe(t_main *main);
void	ft_append_output(t_main *main);

#endif
