/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <elee@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 10:45:06 by elee              #+#    #+#             */
/*   Updated: 2017/06/28 10:45:06 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ball.h"

int *heap, size, count;
int initial_size = 4;

t_heap	heap_init(void)
{
	t_heap	h;

	h = (t_heap*)malloc(sizeof(t_heap));
	if (!h)
	{
		printf("Error allocating for heap data structure\n");
		exit(-1);
	}
	h->count = 0;
	h->size = HEAP_INITIAL_SIZE;
	h->heaparr = (double*)malloc(sizeof(double) * HEAP_INITAL_SIZE);
	if (!h->heapparr)
	{
		printf("Error allocating for heaparr in heap data structure\n");
		exit(-1);
	}
	return (h);
}

void	max_heapify(double *data, int loc, int count)
{
	int	left, right, largeset, temp;

	left = 2 * loc + 1;
	right = left + 1;
	largest = loc;

}
void max_heapify(int *data, int loc, int count) {
	int left, right, largest, temp;
	left = 2*(loc) + 1;
	right = left + 1;
	largest = loc;
	

	if (left <= count && data[left] > data[largest]) {
		largest = left;
	} 
	if (right <= count && data[right] > data[largest]) {
		largest = right;
	} 
	
	if(largest != loc) {
		temp = data[loc];
		data[loc] = data[largest];
		data[largest] = temp;
		max_heapify(data, largest, count);
	}

}

void heap_push(struct heap *h, int value)
{
	int index, parent;
 
	// Resize the heap if it is too small to hold all the data
	if (h->count == h->size)
	{
		h->size += 1;
		h->heaparr = realloc(h->heaparr, sizeof(int) * h->size);
		if (!h->heaparr) exit(-1); // Exit if the memory allocation fails
	}
 	
 	index = h->count++; // First insert at last of array

 	// Find out where to put the element and put it
	for(;index; index = parent)
	{
		parent = (index - 1) / 2;
		if (h->heaparr[parent] >= value) break;
		h->heaparr[index] = h->heaparr[parent];
	}
	h->heaparr[index] = value;
}

void heap_display(struct heap *h) {
	int i;
	for(i=0; i<h->count; ++i) {
		printf("|%d|", h->heaparr[i]);
	}
	printf("\n");
}

int heap_delete(struct heap *h)
{
	int removed;
	int temp = h->heaparr[--h->count];
 	
	
	if ((h->count <= (h->size + 2)) && (h->size > initial_size))
	{
		h->size -= 1;
		h->heaparr = realloc(h->heaparr, sizeof(int) * h->size);
		if (!h->heaparr) exit(-1); // Exit if the memory allocation fails
	}
 	removed = h->heaparr[0];
 	h->heaparr[0] = temp;
 	max_heapify(h->heaparr, 0, h->count);
 	return removed;
}


int emptyPQ(struct heap *pq) {
	int i;
	while(pq->count != 0) {
		printf("<<%d", heap_delete(pq));
	}
}
int main() {
	struct heap h;
	heap_init(&h);
	heap_push(&h,1);
	heap_push(&h,5);
	heap_push(&h,3);
	heap_push(&h,7);
	heap_push(&h,9);
	heap_push(&h,8);
	heap_display(&h);
	heap_display(&h);
	emptyPQ(&h);
	return 0;

}
