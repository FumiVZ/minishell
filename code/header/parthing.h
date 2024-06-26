/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parthing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:44:21 by machrist          #+#    #+#             */
/*   Updated: 2024/06/26 16:43:40 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTHING_H
# define PARTHING_H

# include <dirent.h>
# include <libft.h>
# include <minishell.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>

# define MALLOC "minishell: malloc failed\n"
# define GETCWD "getcwd failed"
# define STAT "stat failed"
# define ERR_OPEN "open failed"
# define ERR_READ "read failed"
# define ERR_CLOSE "close failed"
# define ERR_PIPE "pipe failed"
# define ERR_FORK "fork failed"
# define ERR_EXECVE "execve failed"
# define ERR_WAITPID "waitpid failed"

# define ERR_PAR "minishell: syntax error near unexpected token `('\n"
# define ERR_UNDEFINE "syntax error undefine behavior\n"
# define ERR_TOKEN "minishell: syntax error near unexpected token "

char		**wildcard_match(const char *pattern, char **str, size_t i);
char		**ft_word_spliting(char const *s, char *arg);
char		**pattern_matching(char **str, t_pipex *pipex);
bool		is_space(char c, char *arg);
bool		is_special(char c);
bool		is_special_cpt(char const *c, size_t *i);
char		*crt_is_special(char const *s, size_t *j);
size_t		get_len_name(char *str);
char		*get_value(char *str, char **env, t_env *envp);
char		*add_var_env(char *str, char *value, size_t len, long long pos);
char		**sort_result(t_list **result, char **str, size_t i);
int			msg_err(char *err);
void		*msg_err_ptr(char *err);
int			count_word(char const *s, char *arg);
char		*ifs_value(char **env);
long long	pos_var(char *str, long long old_pos);
int			check_env_var(char *str, long long pos);
char		**check_pattern_word(char **str, size_t i);
char		**clean_str(char **str, size_t pos);
char		**check_str(char **str);
char		*quote_rm_world(char *str, char *tmp);
char		*full_str(char *str, char *value, size_t pos);
bool		is_special_no_par(char c);

#endif