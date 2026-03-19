#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority-queue.h"

void free_min_heap(min_heap *h)
{
    if (h->data)
    {
        free(h->data); h->data = NULL;
    }
    h->size = 0; h->memory_size = 0;
}

min_heap create_empty_min_heap(u64 memory_size)
{
    min_heap h;
    h.size = 0; h.memory_size = 0; h.data = NULL;
    u64 *tmp = malloc(memory_size*sizeof(*tmp));
    if (!tmp)
    {
        free_min_heap(&h); return h;
    }
    h.data = tmp;
    return h;
}

void local_heapify_min(u64 *a, u64 size, u64 cur_root)
{
    while (2*cur_root+1 < size)
    {
        u64 left = 2*cur_root+1, right = 2*cur_root+2;
        u64 smallest = left;
        if (right < size && a[smallest] > a[right]) smallest = right;
        if (a[smallest] < a[cur_root]) swap(a + smallest, a + cur_root);
        else break;
        cur_root = smallest;
    }
}

min_heap heapify_min(u64 *a, u64 size)
{
    min_heap h;
    h.size = size, h.memory_size = size;
    u64 *tmp = malloc(size*sizeof(*tmp));
    if (tmp == NULL)
    {
        h.data = NULL; return h;
    }
    h.data = tmp;
    memcpy(h.data, a, size*(sizeof(*(h.data))));
    for (long long i = ((long long)size-1)/2; i >= 0; i--) local_heapify_min(h.data, size, (u64)i);
    return h;
}

u64 pop_min_heap(min_heap *h)
{
    if (h->size == 0) return -1;
    u64 *d = h->data, sz = h->size, res = d[0];
    swap(d + sz-1, d);
    u64 cur = 0;
    sz--;
    local_heapify_min(h->data, sz, 0);
    h->size--;
    return res;
}

void push_min_heap(min_heap *h, u64 number)
{
    if (h->size == h->memory_size)
    {
        u64 new_cap = 2 * h->memory_size + 1;
        u64 *tmp = realloc(h->data, new_cap * sizeof(*tmp));
        if (tmp == NULL) return;
        h->data = tmp;
        h->memory_size = new_cap;
    }
    u64 *d = h->data; h->size++;
    u64 cur = h->size - 1; d[cur] = number;
    while (cur != 0)
    {
        u64 parent = (cur-1)/2;
        if (d[cur] < d[parent]) swap(d + cur, d + parent);
        else break;
        cur = parent;
    }
}