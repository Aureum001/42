/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:11:11 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/12 11:30:54 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

long	current_time_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}
