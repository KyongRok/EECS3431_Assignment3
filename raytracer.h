// ** YORK UNIVERSITY EECS3431 Assignment3 **
// Group Members: KyongRok Kim - 215813413 , Arian Quader - 218070607 
void create_background(unsigned char** pixles , float background[],int width,int height);

struct sphere{
    char name[4];
    float position[3];
    float scale[3];
    float color[3];
    float k[4];
    int n;
};

struct light{
    char name[4];
    float postition[3];
    float intensity[4];
};