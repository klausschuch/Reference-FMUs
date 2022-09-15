#ifndef cosimulation_h
#define cosimulation_h

#include "model.h"

#define EPSILON (FIXED_SOLVER_STEP * 1e-6)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void doFixedStep(ModelInstance * comp, bool * stateEvent, bool * timeEvent);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* cosimulation_h */
