/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 10:49:27 by fcaval            #+#    #+#             */
/*   Updated: 2026/04/30 10:55:46 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_heap_entry
{
	long		priority;
	unsigned long	seq;
	int				coder_id;
}	t_heap_entry;

typedef struct s_heap
{
	t_heap_entry	*data;
	int				size;
	int				capacity;
	unsigned long	next_seq;
}	t_heap;

