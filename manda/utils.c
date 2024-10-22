/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkaid <fbelkaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 02:54:02 by fbelkaid          #+#    #+#             */
/*   Updated: 2024/10/22 00:48:48 by fbelkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *a, int c, size_t len)
{
	size_t			i;
	unsigned char	*b;

	i = 0;
	b = (unsigned char *)a;
	while (i < len)
	{
		b[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
char *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == c)
            return ((char *)s);
        s++;
    }
    if (c == '\0')
        return ((char *)s);
    return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	len;

	len = size * count;
	if (size != 0 && count != len / size)
		return (NULL);
	ptr = malloc(len);
	if (ptr != NULL)
	{
		if (ft_memset(ptr, 0, len) == ptr)
			return (ptr);
		else
			free(ptr);
	}
	return (NULL);
}

char *ft_strdup(char *s1)
{
    size_t len;
    size_t i;
    void *ptr;
    char *res;

    i = 0;
    len = ft_strlen(s1);
    ptr = ft_calloc(len + 1, sizeof(char));
    if(ptr != NULL)
    {
        res = (char *)ptr;
        while (*s1 && i < len)
        {
            *res = *s1;
            i++;
            s1++;
            res++;
        }
        return ((char *)ptr);
    }
    else
        return (NULL);
}

void ft_putstr(char *str ,int fd )
{
    int i;

    i = 0;
    while (str[i])
    {
        write(1, &str[i], fd);
        i++;
    }
}

char *ft_strtrim (char *s1, char *set)
{
    char *str;
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
    if (!str)
        return (NULL);
    while (s1[i] && ft_strchr(set, s1[i]))
        i++;
    while (s1[i])
    {
        str[j] = s1[i];
        i++;
        j++;
    }
    str[j] = '\0';
    i = ft_strlen(str) - 1;
    while (i >= 0 && ft_strchr(set, str[i]))
    {
        i--;
        k++;
    }
    str[ft_strlen(str) - k] = '\0';
    return (str);
}
