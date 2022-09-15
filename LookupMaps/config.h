#ifndef config_h
#define config_h

// define class name and unique id
#define MODEL_IDENTIFIER LookupMaps
#define INSTANTIATION_TOKEN "{8c4e810f-3df3-4a03-8276-176fa3c9f008}"

#define CO_SIMULATION

#define NX 0
#define NZ 0

#define GET_FLOAT64
#define SET_FLOAT64

#define FIXED_SOLVER_STEP 0.001

#define DEFAULT_STOP_TIME 10

typedef enum {
    vr_x,
    vr_y,
    vr_v,

    vr_d,
    vr_cd,

    vr_map_x,
    vr_map_y,
    vr_map_out,

    vr_curve_x,
    vr_curve_out
} ValueReference;

typedef struct {
    double x[2];
    double y[3];
    double v[2][3];
    double d[4];
    double cd[4];
    double map_x;
    double map_y;
    double map_out;
    double curve_x;
    double curve_out;
} ModelData;

#endif /* config_h */
