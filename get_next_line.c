/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:44:50 by amartin-          #+#    #+#             */
/*   Updated: 2019/11/18 18:17:42 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t
	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char
	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	str = (char*)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char
	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char*)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char*)(s + i));
	return (NULL);
}

char
	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char*)malloc(
		sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = 0;
	return (str);
}

char
	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char*)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

char	*gnl_save_line(char *str, char **line)
{
	int		len;

	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	*line = ft_substr(str, 0, len);
	free(str);
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
		str = ft_substr(tmp, len + 1, len2 - len);
	free(tmp);
	return (str);
}

char	*gnl_final_str(char *str)
{
	int		len;
	int		len2;
	char	*tmp;

	len = 0;
	while (str[len] && str[len] != '\n' && str[len] != '\0')
		len++;
	tmp = ft_substr(str, 0, ft_strlen(str));
	len2 = len;
	while (str[len2] != '\0')
		len2++;
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
	ret_read = 1;
	while (ret_read > 0)
	{
		if ((ret_read = read(fd, buf, BUFFER_SIZE)) == -1)
			return (-1);
		buf[ret_read] = '\0';
		if ((s && ft_strchr(s, '\n') != 0) && ret_read == 0)
		{
			*line = gnl_save_line(s, line);
			s = gnl_cut_str(s);
			return (1);
		}
		if (ret_read == 0 && ft_strlen(s) == 0)
			return (0);
		s = ft_strjoin(s, buf);
	}
	*line = gnl_save_line(s, line);
	s = gnl_final_str(s);
	return ((ret_read == 0 && !line) ? 0 : 1);
}
