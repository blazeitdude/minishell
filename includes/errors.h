/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:45:57 by ldione            #+#    #+#             */
/*   Updated: 2022/10/11 19:43:34 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <errno.h>
# include <stdio.h>

# define ERR_OF_CONSOL_READ "unexpected error of console read"
# define ERR_OF_ALLOC       "error of allocation memmory"
# define ERR_OF_ENV			"error with environment variables"

void	terminate(char *s);

#endif
