// ** YORK UNIVERSITY EECS3431 Assignment3 **
// Group Members: KyongRok Kim - 215813413 , Arian Quader - 218070607
typedef struct vec vec;
typedef struct vec color;
typedef struct vec point;

struct vec{
    float x;
    float y;
    float z;
};

float dotProduct(float x1, float y1,float z1, float x2, float y2, float z2);
vec* crossProduct(float x1, float y1,float z1, float x2, float y2, float z2);
vec* unitVec(float x1, float y1,float z1);
float vecLength(float x1, float y1,float z1);