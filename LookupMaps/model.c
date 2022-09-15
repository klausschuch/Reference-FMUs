#include "config.h"
#include "model.h"


void setStartValues(ModelInstance *comp) {
    M(x)[0] = 2.0;
    M(x)[1] = 3.0;
    M(y)[0] = 10.0;
    M(y)[1] = 25.0;
    M(y)[2] = 30.0;    
    M(v)[0][0] = 11.0;
    M(v)[0][1] = 12.0;
    M(v)[0][2] = 13.0;
    M(v)[1][0] = 21.0;
    M(v)[1][1] = 22.0;
    M(v)[1][2] = 23.0;

    M(d)[0] = 10.0;
    M(d)[1] = 20.0;
    M(d)[2] = 25.0;
    M(d)[3] = 30.0;
    M(cd)[0] = 10.0;
    M(cd)[1] = 20.0;
    M(cd)[2] = 30.0;
    M(cd)[3] = 40.0;

    M(map_x) = 2.0;
    M(map_y) = 10.0;
    M(map_out) = 11.0;

    M(curve_x) = 10.0;
    M(curve_out) = 10.0;
}

Status calculateValues(ModelInstance *comp) {
    double z = 0;
    double out = 0;

    double in = M(curve_x);

    double x = M(map_x);
    double y = M(map_y);

    if (in >= M(d)[0]) {
        out = M(cd)[0];
        if (in >= M(d)[1]) {
            out = M(cd)[1];
            if (in >= M(d)[2]) {
                out = M(cd)[2];
                if (in >= M(d)[3]) {
                    out = M(cd)[3];
                }
            }
        }
    }

    if (x >= M(x)[0]) {
        if (y >= M(y)[0])
            z = M(v)[0][0];
        if (y >= M(y)[1])
            z = M(v)[0][1];
        if (y >= M(y)[2])
            z = M(v)[0][2];
    }
    if (x >= M(x)[1]) {
        if (y >= M(y)[0]) 
            z = M(v)[1][0];
        if (y >= M(y)[1])
            z = M(v)[1][1];
        if (y >= M(y)[2])
            z = M(v)[1][2];
    }

    M(curve_out) = out;

    M(map_out) = z;

    return OK;
}

Status getFloat64(ModelInstance* comp, ValueReference vr, double *value, size_t *index) {
    size_t i = 0;
    size_t j = 0;

    switch (vr) {
        case vr_x:
            for (i = 0; i < 2; i++) {
                value[(*index)++] = M(x)[i];
            }
            break;
        case vr_y:
            for (i = 0; i < 3; i++) {
                value[(*index)++] = M(y)[i];
            }
            break;
        case vr_v:
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    value[(*index)++] = M(v)[i][j];
                }
            }
            break;
        case vr_d:
            for (i = 0; i < 4; i++) {
                value[(*index)++] = M(d)[i];
            }
            break;
        case vr_cd:
            for (i = 0; i < 4; i++) {
                value[(*index)++] = M(cd)[i];
            }
            break;
        case vr_map_x:
            value[(*index)++] = M(map_x);
            break;
        case vr_map_y:
            value[(*index)++] = M(map_y);
            break;
        case vr_map_out:
            value[(*index)++] = M(map_out);
            break;
        case vr_curve_x:
            value[(*index)++] = M(curve_x);
            break;
        case vr_curve_out:
            value[(*index)++] = M(curve_out);
            break;
        default:
            logError(comp, "Get Float64 is not allowed for value reference %u.", vr);
            return Error;
    }

    return OK;
}

Status setFloat64(ModelInstance* comp, ValueReference vr, const double *value, size_t *index) {
    size_t i = 0;
    size_t j = 0;

    switch (vr) {
        case vr_x:
            for (i = 0; i < 2; i++) {
                M(x)[i] = value[(*index)++];
            }
            break;
        case vr_y:
            for (i = 0; i < 3; i++) {
                M(y)[i] = value[(*index)++];
            }
            break;
        case vr_v:
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    M(v)[i][j] = value[(*index)++];
                }
            }
            break;
        case vr_d:
            for (i = 0; i < 4; i++) {
                M(d)[i] = value[(*index)++];
            }
            break;
        case vr_cd:
            for (i = 0; i < 4; i++) {
                M(cd)[i] = value[(*index)++];
            }
            break;
        case vr_map_x:
            M(map_x) = value[(*index)++];
            break;
        case vr_map_y:
            M(map_y) = value[(*index)++];
            break;
        case vr_map_out:
            M(map_out) = value[(*index)++];
            break;
        case vr_curve_x:
            M(curve_x) = value[(*index)++];
            break;
        case vr_curve_out:
            M(curve_out) = value[(*index)++];
            break;
        default:
            logError(comp, "Set Float64 is not allowed for value reference %u.", vr);
            return Error;
    }

    return OK;
}
