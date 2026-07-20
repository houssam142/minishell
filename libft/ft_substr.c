/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounejja <hounejja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:00:30 by nafarid           #+#    #+#             */
/*   Updated: 2026/05/28 10:43:51 by hounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	char	*result;
	size_t	substr_len;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	substr_len = len;
	if (len_s - start < len)
		substr_len = len_s - start;
	result = ft_malloc(sizeof(char) * substr_len + 1);
	if (result == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}
