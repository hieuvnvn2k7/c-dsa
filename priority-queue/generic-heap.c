#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "priority-queue.h"

void free_heap(heap *h)
{
    if (h->data)
    {
        free(h->data); h->data = NULL; h->better = NULL;
    }
    h->size = 0; h->memory_size = 0;
}

heap create_empty_heap(u64 memory_size, bool (*better)(u64, u64))
{
    heap h;
    h.size = 0, h.memory_size = memory_size, h.better = better, h.data = NULL;
    u64 *tmp = malloc(memory_size*sizeof(*tmp));
    if (!tmp)
    {
        free_heap(&h); return h;
    }
    h.data = tmp; return h;
}

void local_heapify(heap *h, u64 cur_root)
{
    u64 size = h->size;
    bool (*better)(u64, u64) = h->better;
    u64 *a = h->data;
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

void heapify(heap *h)
{
    u64 size = h->size;
    for (long long i = ((long long)size - 1)/2; i >= 0; i--)
    {
        local_heapify(h, (u64)i);
    }
}

heap initialize_heap(u64 *a, u64 size, bool(*better)(u64, u64))
{
    heap h;
    h.size = size, h.memory_size = size, h.better = better, h.data = NULL;
    u64 *tmp = malloc(size*sizeof(*tmp));
    if (!tmp)
    {
        free_heap(&h); return h;
    }
    h.data = tmp;
    memcpy(h.data, a, size*sizeof(*a));
    heapify(&h);
    return h;
}

u64 pop_heap(heap *h)
{
    if (h->size == 0) return -1;
    h->size--;
    u64 *d = h->data, sz = h->size, res = d[0];
    swap(d, d + sz);
    local_heapify(h, 0);
    return res;
}

void push_heap(heap *h, u64 data)
{
    if (h->size == h->memory_size)
    {
        u64 new_cap = 2 * h->memory_size + 1;
        u64 *tmp = realloc(h->data, new_cap*sizeof(*tmp));
        if (!tmp) return;
        h->data = tmp; h->memory_size = new_cap;
    }
    u64 *d = h->data, cur = h->size;
    d[cur] = data;
    bool (*better)(u64, u64) = h->better;
    h->size++;
    while (cur != 0)
    {
        u64 parent = (cur-1)/2;
        if (better(d[cur], d[parent])) swap(d + cur, d + parent);
        else break;
        cur = parent;
    }
}