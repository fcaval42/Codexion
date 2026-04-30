/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 14:22:08 by fcaval            #+#    #+#             */
/*   Updated: 2026/04/30 14:22:54 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

int	heap_peek(t_heap *heap, t_heap_entry *out)
{
	if (!heap || !heap->data || !out)
		return (0);
	if (heap->size == 0)
		return (0);
	*out = heap->data[0];
	return (1);
}

int	heap_empty(t_heap *heap)
{
	if (!heap)
		return (1);
	return (heap->size == 0);
}

void	heap_destroy(t_heap *heap)
{
	if (!heap)
		return ;
	free(heap->data);
	heap->data = NULL;
	heap->size = 0;
	heap->capacity = 0;
	heap->next_seq = 0;
}