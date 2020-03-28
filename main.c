#include "mem.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool test(memory_ctx_t* mem_ctx)
{
    uint32_t offset = 0x10;
    uint32_t input = 0xDEADBEEF;
    uint32_t output = 0;
    mem_ctx->write(mem_ctx, offset, &input, sizeof(input));
    mem_ctx->read(mem_ctx, &output, offset, sizeof(output));
    return output == input;
}

int main()
{
    memory_ctx_t mem_ctx;
    mem1_init(&mem_ctx, 1024);

    bool success = test(&mem_ctx);
    printf("%s\n", success ? "success" : "fail");

    mem_ctx.close(&mem_ctx);
}
