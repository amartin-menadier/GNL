/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:04:20 by amartin-          #+#    #+#             */
/*   Updated: 2019/11/22 18:30:41 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*gnl_ft_strjoin(char **s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*gnl_save_line(char *str, char **line);
char	*gnl_cut_str(char *str);
char	*gnl_final_str(char *str);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42

#endif
