#ifndef config_h
#define config_h

#include <cstdint>
#include <vector>

// define class name and unique id
#define MODEL_IDENTIFIER LookupTensors
#define INSTANTIATION_TOKEN "{8c4e810f-3df3-4a02-8276-176fa3c9f008}"

#define CO_SIMULATION

#define NX 0
#define NZ 0

#define GET_FLOAT64
#define SET_FLOAT64

#define GET_UINT64
#define SET_UINT64

#define FIXED_SOLVER_STEP 0.001

#define DEFAULT_STOP_TIME 10

typedef enum {
    vr_static_vector,
    vr_dynamic_vector,
    vr_dynamic_vector_dim,
    vr_static_matrix,
    vr_dynamic_matrix,
    vr_dynamic_matrix_dim1,
    vr_dynamic_matrix_dim2,
    vr_static_vector_idx,
    vr_static_vector_out,
    vr_dynamic_vector_idx,
    vr_dynamic_vector_out,
    vr_static_matrix_idx1,
    vr_static_matrix_idx2,
    vr_static_matrix_out,
    vr_dynamic_matrix_idx1,
    vr_dynamic_matrix_idx2,
    vr_dynamic_matrix_out
} ValueReference;

typedef struct {
    std::vector<double> static_vector;
    std::vector<double> dynamic_vector;
    uint64_t dynamic_vector_dim;
    std::vector<double> static_matrix;
    std::vector<double> dynamic_matrix;
    uint64_t dynamic_matrix_dim1;
    uint64_t dynamic_matrix_dim2;
    uint64_t static_vector_idx;
    double static_vector_out;
    uint64_t dynamic_vector_idx;
    double dynamic_vector_out;
    uint64_t static_matrix_idx1;
    uint64_t static_matrix_idx2;
    double static_matrix_out;
    uint64_t dynamic_matrix_idx1;
    uint64_t dynamic_matrix_idx2;
    double dynamic_matrix_out;
} ModelData;

#endif /* config_h */
