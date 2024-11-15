/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:21:35 by omartela          #+#    #+#             */
/*   Updated: 2024/10/21 10:21:36 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char    *ft_string_replace(char *str, char *delimiter, char *insert)
{
    size_t  i;
    char    *result;
    char    *temp;

    i = 0;
	result = NULL;
    while (str[i])
    {
        if (ft_strncmp(&str[i], delimiter, ft_strlen(delimiter)) == 0)
        {
            result = ft_strndup(str, i);
            if (!result)
                return (NULL);
            temp = ft_strjoin(result, insert);
            if (!temp)
            {
                free(result);
                return (NULL);
            }
            free(result);
            result = temp;
            temp = ft_strjoin(result, &str[i] + ft_strlen(delimiter));
            if (!temp)
            {
                free(result);
                return (NULL);
            }
            free(result);
            result = temp;
			return (result);
        }
        ++i;
    }
    return (NULL);
}