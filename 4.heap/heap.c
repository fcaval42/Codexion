/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 14:17:50 by fcaval            #+#    #+#             */
/*   Updated: 2026/05/04 11:15:47 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	heap_init(t_heap *heap, int capacity)
{
	if (!heap || capacity <= 0)
		return (0);
	heap->data = malloc(sizeof(t_heap_entry) * capacity);
	if (!heap->data)
		return (0);
	heap->size = 0;
	heap->capacity = capacity;
	heap->next_seq = 0;
	return (1);
}

int	heap_push(t_heap *heap, long pritority, int coder_id)
{
	int	index;

	if (!heap || !heap->data)
		return (0);
	if (heap->size >= heap->capacity)
		return (0);
	index = heap->size;
	heap->data[index].priority = pritority;
	heap->data[index].seq = heap->next_seq;
	heap->data[index].coder_id = coder_id;
	heap->next_seq++;
	heap->size++;
	sift_up(heap, index);
	return (1);
}

int	heap_pop(t_heap *heap, t_heap_entry *out)
{
	if (!heap || !heap->data || !out)
		return (0);
	if (heap->size == 0)
		return (0);
	*out = heap->data[0];
	heap->size--;
	if (heap->size > 0)
	{
		heap->data[0] = heap->data[heap->size];
		sift_down(heap, 0);
	}
	return (1);
}
