#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "priority-queue.h"

void free_generic_heap(generic_heap *h)
{
    if (h->data)
    {
        free(h->data); h->data = NULL;
    }
    h->size = 0; h->memory_size = 0;
}

void local_heapify_generic(u64 *a, u64 size, u64 cur_root, bool (*better)(u64, u64))
{
    while (2*cur_root+1 < size)
    {
        u64 left = 2*cur_root+1, right = 2*cur_root+2;
        u64 best = left;
        if (right < size && better(a[right], a[best])) best = right;
        if (!better(a[cur_root], a[best])) swap(a + cur_root, a + best);
        else break;
        cur_root = best;
    }
}

generic_heap heapify_generic(u64 *a, u64 size, bool (*better)(u64, u64))
{
    generic_heap h;
    h.size = size; h.memory_size = size;
    u64 *tmp = malloc(size*sizeof(*tmp));
    if (!tmp)
    {
        h.data = NULL; h.size = 0; h.memory_size = 0;
        return h;
    }
    h.data = tmp;
    memcpy(h.data, a, size*sizeof(*a));
    for (long long i = ((long long)size - 1)/2; i >= 0; i--)
    {
        local_heapify_generic(h.data, size, (u64)i, better);
    }
    return h;
}