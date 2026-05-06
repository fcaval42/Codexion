/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_sort_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 14:24:37 by fcaval            #+#    #+#             */
/*   Updated: 2026/05/06 13:29:15 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	has_higher_priority(t_heap_entry a, t_heap_entry b)
{
	if (a.priority < b.priority)
		return (1);
	if (a.priority > b.priority)
		return (0);
	return (a.seq < b.seq);
}

int	parent_index(int index)
{
	return ((index - 1) / 2);
}

int	left_index(int index)
{
	return (2 * index + 1);
}

int	right_index(int index)
{
	return (2 * index + 2);
}

void	swap_entries(t_heap *heap, int a, int b)
{
	t_heap_entry	tmp;

	tmp = heap->data[a];
	heap->data[a] = heap->data[b];
	heap->data[b] = tmp;
}
