/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 10:49:27 by fcaval            #+#    #+#             */
/*   Updated: 2026/04/30 14:27:27 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
# define HEAP_H

# include <stddef.h>

typedef struct s_heap_entry
{
	long			priority;
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

/// faire un tri dans qui est dans quel fichier + faire norm 

int		heap_init(t_heap *heap, int capacity);
void	heap_destroy(t_heap *heap);
int		heap_push(t_heap *heap, long pritority, int coder_id);
int		heap_pop(t_heap *heap, t_heap_entry *out);
int		heap_peek(t_heap *heap, t_heap_entry *out);
int		heap_empty(t_heap *heap);

#endif
