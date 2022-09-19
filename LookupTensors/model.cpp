#include "model.h"
#include "config.h"

void setStartValues(ModelInstance * comp) {
    M(static_vector) = std::vector<double> { 1.0, 2.0, 3.0 };
    M(dynamic_vector) = std::vector<double> { 1.0, 2.0, 3.0 };
    M(dynamic_vector_dim) = 3U;
    M(static_matrix) = std::vector<double> { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    M(dynamic_matrix) = std::vector<double> { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    M(dynamic_matrix_dim1) = 2U;
    M(dynamic_matrix_dim2) = 3U;
    M(static_vector_idx) = 0U;
    M(static_vector_out) = 1.0;
    M(dynamic_vector_idx) = 0U;
    M(dynamic_vector_out) = 1.0;
    M(static_matrix_idx1) = 0U;
    M(static_matrix_idx2) = 0U;
    M(static_matrix_out) = 1.0;
    M(dynamic_matrix_idx1) = 0U;
    M(dynamic_matrix_idx2) = 0U;
    M(dynamic_matrix_out) = 1.0;
}

Status calculateValues(ModelInstance * comp) {
    M(static_vector_out) = M(static_vector)[M(static_vector_idx)];
    M(dynamic_vector_out) = M(dynamic_vector)[M(dynamic_vector_idx)];

    M(static_matrix_out) = M(static_matrix)[M(static_matrix_idx1) * 3 + M(static_matrix_idx2)];
    M(dynamic_matrix_out) = M(dynamic_matrix)[M(dynamic_matrix_idx1) * M(dynamic_matrix_dim2) + M(dynamic_matrix_idx2)];

    return OK;
}

Status getFloat64(ModelInstance * comp, ValueReference vr, double * value, size_t * index) {
    switch (vr) {
        case vr_static_vector:
            for (const auto& elem : M(static_vector)) {
                value[(*index)++] = elem;
            }
            break;
        case vr_dynamic_vector:
            for (const auto& elem : M(dynamic_vector)) {
                value[(*index)++] = elem;
            }
            break;
        case vr_static_matrix:
            for (const auto& elem : M(static_matrix)) {
                value[(*index)++] = elem;
            }
            break;
        case vr_dynamic_matrix:
            for (const auto& elem : M(dynamic_matrix)) {
                value[(*index)++] = elem;
            }
            break;
        case vr_static_vector_out:
            value[(*index)++] = M(static_vector_out);
            break;
        case vr_dynamic_vector_out:
            value[(*index)++] = M(dynamic_vector_out);
            break;
        case vr_static_matrix_out:
            value[(*index)++] = M(static_matrix_out);
            break;
        case vr_dynamic_matrix_out:
            value[(*index)++] = M(dynamic_matrix_out);
            break;
        default:
            logError(comp, "Get Float64 is not allowed for value reference %u.", vr);
            return Error;
    }

    return OK;
}

Status getUInt64(ModelInstance * comp, ValueReference vr, uint64_t * value, size_t * index) {
    switch (vr) {
        case vr_dynamic_vector_dim:
            value[(*index)++] = M(dynamic_vector_dim);
            break;
        case vr_dynamic_matrix_dim1:
            value[(*index)++] = M(dynamic_matrix_dim1);
            break;
        case vr_dynamic_matrix_dim2:
            value[(*index)++] = M(dynamic_matrix_dim2);
            break;
        case vr_static_vector_idx:
            value[(*index)++] = M(static_vector_idx);
            break;
        case vr_dynamic_vector_idx:
            value[(*index)++] = M(dynamic_vector_idx);
            break;
        case vr_static_matrix_idx1:
            value[(*index)++] = M(static_matrix_idx1);
            break;
        case vr_static_matrix_idx2:
            value[(*index)++] = M(static_matrix_idx2);
            break;
        case vr_dynamic_matrix_idx1:
            value[(*index)++] = M(dynamic_matrix_idx1);
            break;
        case vr_dynamic_matrix_idx2:
            value[(*index)++] = M(dynamic_matrix_idx2);
            break;
        default:
            logError(comp, "Get UInt64 is not allowed for value reference %u.", vr);
            return Error;
    }

    return OK;
}

Status setFloat64(ModelInstance * comp, ValueReference vr, const double * value, size_t * index) {
    switch (vr) {
        case vr_static_vector:
            for (auto& elem : M(static_vector)) {
                elem = value[(*index)++];
            }
            break;
        case vr_dynamic_vector:
            for (auto& elem : M(dynamic_vector)) {
                elem = value[(*index)++];
            }
            break;
        case vr_static_matrix:
            for (auto& elem : M(static_matrix)) {
                elem = value[(*index)++];
            }
            break;
        case vr_dynamic_matrix:
            for (auto& elem : M(dynamic_matrix)) {
                elem = value[(*index)++];
            }
            break;
        case vr_static_vector_out:
            M(static_vector_out) = value[(*index)++];
            break;
        case vr_dynamic_vector_out:
            M(dynamic_vector_out) = value[(*index)++];
            break;
        case vr_static_matrix_out:
            M(static_matrix_out) = value[(*index)++];
            break;
        case vr_dynamic_matrix_out:
            M(dynamic_matrix_out) = value[(*index)++];
            break;
        default:
            logError(comp, "Set Float64 is not allowed for value reference %u.", vr);
            return Error;
    }

    return OK;
}

Status setUInt64(ModelInstance * comp, ValueReference vr, const uint64_t * value, size_t * index) {
    switch (vr) {
        case vr_dynamic_vector_dim:
            M(dynamic_vector_dim) = value[(*index)++];
            M(dynamic_vector).resize(M(dynamic_vector_dim));
            break;
        case vr_dynamic_matrix_dim1:
            {
                uint64_t old_dim = M(dynamic_matrix_dim1);
                M(dynamic_matrix_dim1) = value[(*index)++];
                auto old_vector = M(dynamic_matrix);
                M(dynamic_matrix).resize(M(dynamic_matrix_dim1) * M(dynamic_matrix_dim2));
                for (auto i = 0; i < M(dynamic_matrix_dim1); i++) {
                    for (auto j = 0; j < M(dynamic_matrix_dim2); j++) {
                        if (i < old_dim) {
                            M(dynamic_matrix)[i * M(dynamic_matrix_dim2) + j] = old_vector[i * M(dynamic_matrix_dim2) + j];
                        } else {
                            M(dynamic_matrix)[i * M(dynamic_matrix_dim2) + j] = 0.0;
                        }
                    }
                }
                break;
            }
        case vr_dynamic_matrix_dim2:
            {
                uint64_t old_dim = M(dynamic_matrix_dim2);
                M(dynamic_matrix_dim2) = value[(*index)++];
                auto old_vector = M(dynamic_matrix);
                M(dynamic_matrix).resize(M(dynamic_matrix_dim1) * M(dynamic_matrix_dim2));
                for (auto i = 0; i < M(dynamic_matrix_dim1); i++) {
                    for (auto j = 0; j < M(dynamic_matrix_dim2); j++) {
                        if (j < old_dim) {
                            M(dynamic_matrix)[i * M(dynamic_matrix_dim2) + j] = old_vector[i * M(dynamic_matrix_dim2) + j];
                        } else {
                            M(dynamic_matrix)[i * M(dynamic_matrix_dim2) + j] = 0.0;
                        }
                    }
                }
                break;
            }
        case vr_static_vector_idx:
            {
                uint64_t idx = value[(*index)++];
                if (idx >= 3) {
                    logError(comp, "Vector index %u out of range (vector size: 3)", vr);
                    return Error;
                }
                M(static_vector_idx) = idx;
                break;
            }
        case vr_dynamic_vector_idx:
            {
                uint64_t idx = value[(*index)++];
                if (idx >= M(dynamic_vector_dim)) {
                    logError(comp, "Vector index %u out of range (vector size: %u)", vr, M(dynamic_vector_dim));
                    return Error;
                }
                M(dynamic_vector_idx) = idx;
                break;
            }
        case vr_static_matrix_idx1:
            {
                uint64_t idx = value[(*index)++];
                if (idx >= 2) {
                    logError(comp, "Index of dimension 1 (vr: %u) out of range (dimension size: 2)", vr);
                    return Error;
                }
                M(static_matrix_idx1) = idx;
                break;
            }
        case vr_static_matrix_idx2:
            {
                uint64_t idx = value[(*index)++];
                if (idx >= 3) {
                    logError(comp, "Index of dimension 2 (vr: %u) out of range (dimension size: 3)", vr);
                    return Error;
                }
                M(static_matrix_idx2) = idx;
                break;
            }
        case vr_dynamic_matrix_idx1:
            {
                uint64_t idx = value[(*index)++];
                if (idx >= M(dynamic_matrix_dim1)) {
                    logError(comp, "Index of dimension 1 (vr: %u) out of range (dimension size: %u)", vr, M(dynamic_matrix_dim1));
                    return Error;
                }
                M(dynamic_matrix_idx1) = idx;
                break;
            }
        case vr_dynamic_matrix_idx2:
            {
                uint64_t idx = value[(*index)++];
                if (idx >= M(dynamic_matrix_dim2)) {
                    logError(comp, "Index of dimension 2 (vr: %u) out of range (dimension size: %u)", vr, M(dynamic_matrix_dim2));
                    return Error;
                }
                M(dynamic_matrix_idx2) = idx;
                break;
            }
        default:
            logError(comp, "Set Float64 is not allowed for value reference %u.", vr);
            return Error;
    }

    return OK;
}
