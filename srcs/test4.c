#include "malloc.h"
#include <time.h>

#define CANARY 0xDEADBEEFCAFEBABEULL
#define SLOTS 1000
#define ITERATIONS 1000

typedef struct {
    void *ptr;
    size_t size;
    uint64_t *before;
    uint64_t *after;
} block_t;

block_t blocks[SLOTS];

static size_t rnd(size_t max)
{
    return (size_t)rand() % max;
}

static void check_block(block_t *b)
{
    if (!b->ptr)
        return;

    if (*b->before != CANARY) {
        fprintf(stderr, "UNDERFLOW détecté\n");
        abort();
    }

    if (*b->after != CANARY) {
        fprintf(stderr, "OVERFLOW détecté taille=%zu\n", b->size);
        // show_alloc_mem_ex();
        abort();
    }
}

static void create_block(int i, size_t size)
{
    size_t total = size + 16;

    uint8_t *raw = malloc(total);

    if (!raw)
        return;

    uint64_t *left = (uint64_t *)raw;
    uint8_t *data = raw + 8;
    uint64_t *right = (uint64_t *)(data + size);

    *left = CANARY;
    *right = CANARY;

    memset(data, 0xAA, size);

    blocks[i].ptr = data;
    blocks[i].size = size;
    blocks[i].before = left;
    blocks[i].after = right;
}

static void destroy_block(int i)
{
    check_block(&blocks[i]);

    free(blocks[i].before);

    memset(&blocks[i], 0, sizeof(block_t));
}

static void realloc_block(int i, size_t new_size)
{
    block_t *b = &blocks[i];

    if (!b->ptr)
        return;

    check_block(b);

    uint8_t *old = b->ptr;

    void *tmp = realloc(b->before, new_size + 16);

    if (!tmp)
        return;

    uint8_t *raw = tmp;

    uint64_t *left = (uint64_t *)raw;
    uint8_t *data = raw + 8;
    uint64_t *right = (uint64_t *)(data + new_size);

    *left = CANARY;
    *right = CANARY;

    b->ptr = data;
    b->size = new_size;
    b->before = left;
    b->after = right;

    // Vérifie que l'ancien contenu n'a pas été massacré
    (void)old;
}

int main(void)
{
    srand(time(NULL));

    memset(blocks, 0, sizeof(blocks));

    for (size_t n = 0; n < 10000; n++) {

        int i = rnd(SLOTS);
        int op = rnd(100);

        if (op < 40) {
            // allocations petites
            if (!blocks[i].ptr)
                create_block(i, rnd(512) + 1);
        }
        else if (op < 70) {
            // allocations grosses
            if (!blocks[i].ptr)
                create_block(i, rnd(1024 * 1024) + 1);
        }
        else if (op < 85) {
            // realloc sauvage
            realloc_block(i, rnd(1024 * 1024));
        }
        else {
            // free aléatoire
            if (blocks[i].ptr)
                destroy_block(i);
        }

        // scan périodique
        if ((n % 1000) == 0) {
            for (int j = 0; j < SLOTS; j++)
                check_block(&blocks[j]);

            printf("\r%d/%d", (int)n, ITERATIONS);
            fflush(stdout);
        }
    }

    printf("\nOK\n");

    return 0;
}