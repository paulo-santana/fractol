/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 22:28:27 by psergio-          #+#    #+#             */
/*   Updated: 2021/05/22 22:28:27 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	str_len;
	size_t	max_size;

	str_len = ft_strlen(s);
	if (str_len > start)
		max_size = ft_umin(ft_strlen(s + start), len);
	else
		return (ft_strdup(""));
	sub = ft_calloc(max_size + 1, 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, max_size + 1);
	return (sub);
}
