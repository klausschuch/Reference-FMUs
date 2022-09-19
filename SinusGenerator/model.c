#define _USE_MATH_DEFINES
#include <math.h>
#undef _USE_MATH_DEFINES

#include "config.h"
#include "model.h"

void setStartValues(ModelInstance * comp) {
    M(amplitude) = 10.0;
    M(frequency) = 5.0;
    M(phase) = 0.0;
    M(offset) = 0.0;
    M(start_time) = 0.0;

    M(sinus_out) = 0.0;
}

Status calculateValues(ModelInstance * comp) {
    M(sinus_out) = M(offset);
    if (comp->time >= M(start_time)) {
        M(sinus_out) += M(amplitude) * sin(2.0 * M_PI * M(frequency) * (comp->time - M(start_time)) + M(phase));
    }

    return OK;
}

Status getFloat64(ModelInstance * comp, ValueReference vr, double * value, size_t * index) {
    switch (vr) {
        case vr_amplitude:
            value[(*index)++] = M(amplitude);
            return OK;
        case vr_frequency:
            value[(*index)++] = M(frequency);
            return OK;
        case vr_phase:
            value[(*index)++] = M(phase);
            return OK;
        case vr_offset:
            value[(*index)++] = M(offset);
            return OK;
        case vr_start_time:
            value[(*index)++] = M(start_time);
            return OK;
        case vr_sinus_out:
            value[(*index)++] = M(sinus_out);
            return OK;
        default:
            logError(comp, "Get Float64 is not allowed for value reference %u.", vr);
            return Error;
    }
}

Status setFloat64(ModelInstance * comp, ValueReference vr, const double * value, size_t * index) {
    switch (vr) {
        case vr_amplitude:
            M(amplitude) = value[(*index)++];
            break;
        case vr_frequency:
            M(frequency) = value[(*index)++];
            break;
        case vr_phase:
            M(phase) = value[(*index)++];
            break;
        case vr_offset:
            M(offset) = value[(*index)++];
            break;
        case vr_start_time:
            M(start_time) = value[(*index)++];
            break;
        case vr_sinus_out:
            M(sinus_out) = value[(*index)++];
            break;
        default:
            logError(comp, "Set Float64 is not allowed for value reference %u.", vr);
            return Error;
    }

    return OK;
}
