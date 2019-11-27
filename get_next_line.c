/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:44:50 by amartin-          #+#    #+#             */
/*   Updated: 2019/11/26 14:11:17 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_ft_strjoin(char **s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char*)malloc(
			sizeof(**s1) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while ((*s1)[i])
	{
		str[j++] = (*s1)[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = 0;
	free(*s1);
	*s1 = str;
	return (str);
}

char	*gnl_save_line(char *str, char **line)
{
	int		len;

	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	*line = ft_substr(str, 0, len);
	return (*line);
}

char	*gnl_cut_str(char *str)
{
	int		len;
	int		len2;
	char	*tmp;

	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	tmp = ft_substr(str, 0, ft_strlen(str));
	len2 = ft_strlen(tmp);
	if (str[len] && str[len] == '\n')
	{
		free(str);
		str = ft_substr(tmp, len + 1, len2 - len);
	}
	free(tmp);
	return (str);
}

char	*gnl_final_str(char *str)
{
	int		len;
	int		len2;
	char	*tmp;

	len = 0;
	while (str[len])
		len++;
	tmp = ft_substr(str, 0, ft_strlen(str));
	len2 = len;
	while (str[len2] != '\0')
		len2++;
	free(str);
	str = ft_substr(tmp, len + 1, len2);
	free(tmp);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	static char	*s;
	int			ret_read;
	char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || !line || BUFFER_SIZE < 1 || !(s = (!s ? ft_strdup("") : s)))
		return (-1);
	while ((ret_read = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		if (ret_read == -1)
			return (-1);
		buf[ret_read] = '\0';
		gnl_ft_strjoin(&s, buf);
		gnl_save_line(s, line);
		if (s && ft_strchr(s, '\n') != 0)
		{
			s = gnl_cut_str(s);
			return (1);
		}
		if (ret_read == 0 && (ft_strlen(s) == 0 || !ft_strchr(s, '\n')))
			s = gnl_final_str(s);
		if (ret_read == 0 && (ft_strlen(s) == 0 || !ft_strchr(s, '\n')))
			return (0);
		free(*line);
	}
	return (-1);
}
