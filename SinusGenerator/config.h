#ifndef config_h
#define config_h

// define class name and unique id
#define MODEL_IDENTIFIER SinusGenerator
#define INSTANTIATION_TOKEN "{8c4e810f-3df3-4a01-8276-176fa3c9f008}"

#define CO_SIMULATION

#define NX 0
#define NZ 0

#define GET_FLOAT64
#define SET_FLOAT64

#define FIXED_SOLVER_STEP 0.001

#define DEFAULT_STOP_TIME 10

typedef enum {
    vr_amplitude,
    vr_frequency,
    vr_phase,
    vr_offset,
    vr_start_time,
    vr_sinus_out
} ValueReference;

typedef struct {
    double amplitude;
    double frequency;
    double phase;
    double offset;
    double start_time;
    double sinus_out;
} ModelData;

#endif /* config_h */
