#include "mem.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint8_t* memory;
    int some_other_data1;
    int some_other_data2;
} memory_opaque_t;

#define OPAQUE(ctx) ((memory_opaque_t*)(ctx)->opaque)

static void mem1_write(memory_ctx_t* ctx, int dst, void* src, int size)
{
    memcpy(OPAQUE(ctx)->memory + dst, src, size);
}

static void mem1_read(memory_ctx_t* ctx, void* dst, int src, int size)
{
    memcpy(dst, OPAQUE(ctx)->memory + src, size);
}

static void mem1_close(memory_ctx_t* ctx)
{
    // 2 malloc -> 2 free
    free(OPAQUE(ctx)->memory);
    free(OPAQUE(ctx));
}

void mem1_init(memory_ctx_t* ctx, int mem_size)
{
    ctx->write = mem1_write;
    ctx->read = mem1_read;
    ctx->close = mem1_close;
    ctx->opaque = malloc(sizeof(memory_opaque_t));
    OPAQUE(ctx)->memory = malloc(mem_size);
}

