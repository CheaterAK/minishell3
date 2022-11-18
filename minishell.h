/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:33:54 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 16:39:00 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <argv.h>
# include <stddef.h>

typedef struct s_info
{
	int	i;
	int	fd;
	int	*io;
	int	max_proc;
}		t_info;
/*
** utils.c
*/

int		ft_strcmp(const char *str1, const char *str2);
char	*ft_strncpy(char *des, const char *src, size_t n);
char	*str3join(char *s1, char *s2, char *s3);
int		ft_is_valid_env(const char *str);
int		ft_isequal(int c);
int		ft_isstring(const char *str);
int		is_builtin(t_argv *cmd);

/*
** builtins1.c
*/

int		ft_echo(t_argv *cmd);
int		ft_cd(t_argv *cmd);
int		ft_pwd(void);
int		ft_export(t_argv *cmd);
int		ft_unset(t_argv *cmd);

/*
** builtins2.c
*/

int		ft_env(void);
int		ft_exit(t_argv *cmd);

/*
** builtins3.c
*/

int		env_cmp(char *s1, char *s2);

/*
** builtins4.c
*/

char	*get_env(char *str);
void	env_print(t_argv *env);
int		compare_this(char *s1, char *s2);

/*
** builtins5.c
*/

int		compare_env(char *s1, char *s2);
int		compare_exp(char *s1, char *s2);

/*
** exec.c
*/
int		exec_this(t_argv *cmd);
int		exec_all(t_argv *exec, int max_proc);
int		builtin_exec(t_argv *cmd);
int		builtin_op(t_argv *cmd);

/*
** exec2.c
*/

int		find_procces_size(t_argv *exec);
char	*accessable(t_argv *path, char *cmd);
t_argv	*get_trgt(t_argv *exec);

/*
** redirects.c
*/

void	folder_operations(t_argv *cmd);

/*
** token.c
*/

int		lexer(t_argv *cmd, char *line, int status);
int		heredoc_check(t_argv *cmd);

/*
** main.c
*/

int		ft_isspace(char c);
void	signal_handler(int sig);

/*
** queto.c
*/

char	*lexer_word_plus_quote(t_argv *cmd, char *line, int status);

/*
** queto2.c
*/

char	*jump_to_single_quote(char *line);
char	*jump_to_double_quote(char *line);

/*
** dollar_sign.c
*/

char	*implement(char *line_s, int status);

/*
** control.c
*/

int		check_line(char *line);
char	*check_token(t_argv *cmd);
int		ft_isspace(char c);

t_argv	*g_et;

#endif
