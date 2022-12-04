// ** YORK UNIVERSITY EECS3431 Assignment3 **
// Group Members: KyongRok Kim - 215813413 , Arian Quader - 218070607
// #include "vector.h"
typedef struct ray ray;
typedef struct hitRecord hitRecord;

struct ray{
    point* origin;
    vec* direction;
};

struct hitRecord{
    point* p;
    vec* normal;
    float t;
    int frontFace;
};

point* at(ray* r, float t);
void setFaceNormal(hitRecord* h, ray* r, vec*outNorm);