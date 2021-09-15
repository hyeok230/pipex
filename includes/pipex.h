/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junylee <junylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:29:41 by junylee           #+#    #+#             */
/*   Updated: 2021/09/15 15:22:49 by junylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*
** =============================================================================
** Dependencies
** =============================================================================
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

/*
** =============================================================================
** Utils
** =============================================================================
*/

void	ft_fail(char **ret);
int	ft_isdeli(char c, char deli);
int	ft_count(char *s, char c);
char	*ft_cpy(char *s, char c, int *offset, int i);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
int	ft_strlen(const char *str);

#endif
