//
// Created by vik on 6/30/25.
//

#ifndef CHUNK_H
#define CHUNK_H
#define CHUNK_H
#define BLOCK_AIR       0
#define BLOCK_GRASS     1
#define BLOCK_WOOD      2
#define BLOCK_STONE      3
#define BLOCK_CANVAS    4
#include <raylib.h>
#include <raylib/raymath.h>
typedef char*** chunk_t;
typedef struct {
    int x,y,z;
} Vector3_t;

constexpr Vector3 camera_position {4.304f, 5.292f, 16.295f};
constexpr Vector3 camera_target {4.608f, -0.151f, -0.496f};
#define CAMERA_POSITION_X 4.304f
#define CAMERA_POSITION_Y 5.292f
#define CAMERA_POSITION_Z 16.295f

#define CAMERA_TARGET_X 4.608f
#define CAMERA_TARGET_Y -0.151f
#define CAMERA_TARGET_Z -0.496f
typedef struct Plane {
    float a, b, c, d;
} Plane;
//----------------------------------------------------------------------------------------------------------------------
// CHUNK.C
//----------------------------------------------------------------------------------------------------------------------
void free_chunk(chunk_t chunk, const Vector3_t size);
chunk_t allocate_chunk(const Vector3_t size);
chunk_t init_chunk(Vector3_t *size);
chunk_t read_chunk_file(Vector3_t *chunkSize);
void print_block_chunk(chunk_t chunk, const Vector3_t chunk_size, const  Vector3_t block_position);
void print_chunk(chunk_t chunk, Vector3_t size);
Vector3 intToFloatVec3(const Vector3_t x);
Vector3_t floatToIntVec3(const Vector3 x);
//----------------------------------------------------------------------------------------------------------------------
//CHUNK FILL.C
//----------------------------------------------------------------------------------------------------------------------
chunk_t place_block( chunk_t chunk, const Vector3_t size, const Vector3_t position, char block);
chunk_t chunk_fill_cuboid(chunk_t chunk, const Vector3_t chunk_size,
    const Vector3_t p1, const Vector3_t p2, char block);
chunk_t chunk_fill_sphere(chunk_t chunk, const Vector3_t chunk_size,
    const Vector3_t position, double radius, char block);
//----------------------------------------------------------------------------------------------------------------------
//CHUNK RENDERER.C
//----------------------------------------------------------------------------------------------------------------------
Camera3D InitCamera();
void render_chunk(const chunk_t chunk, const Vector3_t size, Camera3D camera);
chunk_t chunk_place_block(chunk_t chunk, int width, int height, int depth, int x, int y, int z, char block);




#endif //CHUNK_H
