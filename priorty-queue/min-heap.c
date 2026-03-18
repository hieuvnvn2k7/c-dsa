#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned long long u64;

typedef struct
{
    u64 size;
    u64 *data;
} min_heap;

void swap(u64 *a, u64 *b)
{
    u64 c = *a; *a = *b; *b = c;
}

void heaping(u64 *a, u64 size, u64 cur)
{
    while (2*cur+1 < size)
    {
        u64 left = 2*cur+1, right = 2*cur+2;
        u64 smallest = left;
        if (right < size && a[smallest] > a[right]) smallest = right;
        if (a[smallest] < a[cur]) swap(a + smallest, a + cur);
        else break;
        cur = smallest;
    }
}

min_heap heapify(u64 *a, u64 size)
{
    min_heap h;
    h.size = size;
    for (long long i = (size-1)/2; i >= 0; i--) heaping(a, size, (u64)i);
    h.data = a;
    return h;
}

u64 pop_min(min_heap *h)
{
    u64 *d = h->data, sz = h->size, res = d[0];
    swap(d + sz-1, d);
    u64 cur = 0;
    sz--;
    while (2*cur+1 < sz)
    {
        u64 right = 2*cur+2, left = 2*cur+1;
        u64 smallest = left;
        if (right < sz && d[smallest] > d[right]) smallest = right;
        if (d[cur] > d[smallest]) swap(d + cur, d + smallest);
        else break;
        cur = smallest;
    }
    h->size--;
    return res;
}