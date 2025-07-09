//
// Created by vik on 6/30/25.
//
#include "chunk.h"
#include <cstdlib>
#include <cstdio>
//TODO: rewrite this function for the new block struct
void FreeChunk(const chunk_new &chunk) {
    for (int x = 0; x < chunk.size.x; x++) {
        for (int y = 0; y < chunk.size.y; y++) {
            free(chunk.chunkData[x][y]);
        }
        free(chunk.chunkData[x]);
    }
    free(chunk.chunkData);
}
void free_chunk(chunk_t chunk, const Vector3_t size) {
    for (int x = 0; x < size.x; x++) {
        for (int y = 0; y < size.y; y++) {
            free(chunk[x][y]);
        }
        free(chunk[x]);
    }
    free(chunk);
}

chunk_new AllocateChunk(const Vector3_t size) {
    chunk_new chunk;
    chunk.size = size;
    chunk.chunkData = static_cast<Block***>(calloc(chunk.size.x, sizeof(Block**)));
    for (int x = 0; x < chunk.size.x; x++) {
        chunk.chunkData[x] = static_cast<Block**>(calloc(chunk.size.y + 1, sizeof(Block*)));
        for (int y = 0; y < chunk.size.y; y++) {
            chunk.chunkData[x][y] = static_cast<Block*>(calloc(chunk.size.z, sizeof(Block)));
            for (int z = 0; z < chunk.size.z; z++) {
                chunk.chunkData[x][y][z].alpha = 0.0f;
            }
        }
    }
    for (int x = 0; x < chunk.size.x; x++) {
        for (int z = 0; z < chunk.size.z; z++) {
            chunk.chunkData[x][0][z].color[0] = 1.0f;
            chunk.chunkData[x][0][z].color[1] = 0.0f;
            chunk.chunkData[x][0][z].color[2] = 0.0f;
            chunk.chunkData[x][0][z].alpha = 255.0f;
        }
    }
    return chunk;
}
chunk_t allocate_chunk(const Vector3_t size) {
    chunk_t chunk = static_cast<chunk_t>(calloc(size.x , sizeof *chunk));
    for (int x = 0; x < size.x; x++) {
        chunk[x] = static_cast<char**>(calloc(size.y+ 1 , sizeof **chunk));
        for (int y = 0; y < size.y; y++) {
            chunk[x][y] = static_cast<char*>(calloc(size.z , sizeof ***chunk));
        }
    }
    for (int x = 0; x < size.x; x++) {
        for (int z = 0; z < size.z; z++) {
            chunk[x][0][z] = 10;
        }

    }
    return chunk;
}


//TODO: rewrite this function for the new block struct
chunk_new InitChunk(const Vector3_t size) {
    chunk_new chunk = AllocateChunk(size);
    return chunk;
}
chunk_t init_chunk(Vector3_t *size) {

    chunk_t chunk = allocate_chunk(*size);
    return chunk;

}
//TODO: rewrite this function for the new block struct
chunk_new ReadFromFile(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    //if (file == nullptr) return 0;
    chunk_new chunk;
    fscanf(file, "%d%d%d", &chunk.size.x, &chunk.size.y, &chunk.size.z);
    chunk.chunkData = static_cast<Block***>(malloc(chunk.size.x * sizeof(Block**)));
    for (int x = 0; x < chunk.size.x; x++) {
        chunk.chunkData[x] = static_cast<Block**>(malloc(chunk.size.y * sizeof(Block*)));
        for (int y = 0; y < chunk.size.y; y++) {
             chunk.chunkData[x][y] = static_cast<Block*>(malloc(chunk.size.z * sizeof(Block)));
            for (int z = 0; z < chunk.size.z; z++) {
                fscanf(file, "%f%f%f", &chunk.chunkData[x][y][x].color[0],&chunk.chunkData[x][y][x].color[1],&chunk.chunkData[x][y][x].color[2]);
            }
        }
    }
    return chunk;
}
chunk_t read_chunk_file(Vector3_t *chunkSize) {
    FILE *file = fopen("Chunks/1.in", "r");
    if (file == nullptr) return nullptr;
    fscanf(file,"%d%d%d", &chunkSize->x, &chunkSize->y, &chunkSize->z);


    chunk_t chunk = static_cast<chunk_t>(malloc(chunkSize->z * sizeof *chunk));

    for (int x = 0; x < chunkSize->x; x++) {
        chunk[x] = static_cast<char**>(malloc(chunkSize->y * sizeof **chunk));
        for (int y = chunkSize->y-1; y >= 0; y--) {
            chunk[x][y] = static_cast<char*>(malloc(chunkSize->z * sizeof ***chunk));

            for (int z = 0; z < chunkSize->z; z++)
                fscanf(file,"%hhd", &chunk[x][y][z]);
        }
    }

    return chunk;
}
//TODO: rewrite this function for the new block struct
void PrintBlockChunk(const chunk_new chunk, const Vector3_t block_position) {
    if (block_position.x < 0 || block_position.x >=chunk.size.x) {
        logger::error("%d is not a valid X coordinate", block_position.x);
        return;
    }
    if (block_position.y < 0 || block_position.y >= chunk.size.y) {
        logger::error("%d is not a valid Y coordinate", block_position.y);
        return;
    }
    if (block_position.z < 0 || block_position.z >= chunk.size.z) {
        logger::error("%d is not a valid Z coordinate", block_position.z);
        return;
    }
    Block block = chunk.chunkData[block_position.x][block_position.y][block_position.z];
    logger::info("Block:%f %f %f at X:%d Y:%d Z:%d", block.color[0], block.color[1], block.color[2],
        block_position.x, block_position.y, block_position.z);
}
void print_block_chunk(chunk_t chunk, const Vector3_t chunk_size, const  Vector3_t block_position) {
    if (block_position.x < 0 || block_position.x >= chunk_size.x) {
        printf("ERROR: X coordinate is not valid\n");
        return;
    }
    if (block_position.y < 0 || block_position.y >= chunk_size.y) {
        printf("ERROR: Y coordinate is not valid\n");
        return;
    }
    if (block_position.z < 0 || block_position.z >= chunk_size.z) {
        printf("ERROR: Z coordinate is not valid\n");
        return;
    }
    printf("Block %d at X:%d Y:%d Z:%d\n",chunk[block_position.x][block_position.y][block_position.z],
        block_position.x,block_position.y,block_position.z);
}
//TODO: rewrite this function for the new block struct
void print_chunk(chunk_t chunk, Vector3_t size) {
    printf("Chunk: width-%d, height-%d, depth-%d", size.x, size.y, size.z);
    for (int x  = 0; x < size.x; x++) {
        for (int y  = 0; y < size.y; y++) {
            for (int z  = 0; z < size.z; z++) {
                printf("%d ",chunk[x][y][z]);

            }
            printf("\n");
        }
        printf("\n");
    }

}
//TODO: rewrite this function for the new block struct
chunk_t read_chunk(int *width, int *height, int *depth) {
    scanf("%d%d%d", width, height, depth);

    chunk_t chunk = static_cast<chunk_t>(malloc(*width * sizeof *chunk));

    for (int x = 0; x < *width; x++) {
        chunk[x] = static_cast<char**>(malloc(*height * sizeof **chunk));
        for (int y = *height-1; y >= 0; y--) {
            chunk[x][y] = static_cast<char*>(malloc(*depth * sizeof ***chunk));

            for (int z = 0; z < *depth; z++)
                scanf("%hhd", &chunk[x][y][z]);
        }
    }

    return chunk;
}

Vector3 intToFloatVec3(const Vector3_t x) {
    Vector3 t;
    t.x = static_cast<float>(x.x);
    t.y = static_cast<float>(x.y);
    t.z = static_cast<float>(x.z);
    return t;
}

Vector3_t floatToIntVec3(const Vector3 x) {
    Vector3_t t;
    t.x = static_cast<int>(x.x);
    t.y = static_cast<int>(x.y);
    t.z = static_cast<int>(x.z);
    return t;
}
