// ** YORK UNIVERSITY EECS3431 Assignment3 **
// Group Members: KyongRok Kim - 215813413 , Arian Quader - 218070607

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "raytracer.h"
#include "vector.h"
#include "ray.h"

// Output in P6 format, a binary file containing:
// P6
// ncolumns nrows
// Max colour value
// colours in binary format thus unreadable


void invert_matrix (double A[4][4], double Ainv[4][4]);
void adjoint( double in[4][4], double out[4][4] );
double det4x4( double m[4][4] );
double det3x3( double a1, double a2, double a3, double b1, double b2, double b3, double c1, double c2, double c3 );
double det2x2( double a, double b, double c, double d);

/*------------------------------------------------------*/
/*
 * Invert a 4x4 matrix.  Changed slightly from Richard Carling's code
 * in "Graphics Gems I".
 */

#define SMALL_NUMBER    1.e-8
void invert_matrix (double A[4][4], double Ainv[4][4]) {
  int i, j;
  double det ;

  adjoint( A, Ainv );

  det = det4x4( A );

  // if ( fabs( det ) < SMALL_NUMBER) {
  //   fprintf(stderr,"invert_matrix: matrix is singular!");
  //   return;
  // }

  for (i=0; i<4; i++)
    for(j=0; j<4; j++)
      Ainv[i][j] = Ainv[i][j] / det;
}

void adjoint( double in[4][4], double out[4][4] ) {
  double a1, a2, a3, a4, b1, b2, b3, b4;
  double c1, c2, c3, c4, d1, d2, d3, d4;


  a1 = in[0][0]; b1 = in[0][1]; 
  c1 = in[0][2]; d1 = in[0][3];

  a2 = in[1][0]; b2 = in[1][1]; 
  c2 = in[1][2]; d2 = in[1][3];

  a3 = in[2][0]; b3 = in[2][1];
  c3 = in[2][2]; d3 = in[2][3];

  a4 = in[3][0]; b4 = in[3][1]; 
  c4 = in[3][2]; d4 = in[3][3];

  out[0][0]  =   det3x3( b2, b3, b4, c2, c3, c4, d2, d3, d4);
  out[1][0]  = - det3x3( a2, a3, a4, c2, c3, c4, d2, d3, d4);
  out[2][0]  =   det3x3( a2, a3, a4, b2, b3, b4, d2, d3, d4);
  out[3][0]  = - det3x3( a2, a3, a4, b2, b3, b4, c2, c3, c4);
        
  out[0][1]  = - det3x3( b1, b3, b4, c1, c3, c4, d1, d3, d4);
  out[1][1]  =   det3x3( a1, a3, a4, c1, c3, c4, d1, d3, d4);
  out[2][1]  = - det3x3( a1, a3, a4, b1, b3, b4, d1, d3, d4);
  out[3][1]  =   det3x3( a1, a3, a4, b1, b3, b4, c1, c3, c4);
        
  out[0][2]  =   det3x3( b1, b2, b4, c1, c2, c4, d1, d2, d4);
  out[1][2]  = - det3x3( a1, a2, a4, c1, c2, c4, d1, d2, d4);
  out[2][2]  =   det3x3( a1, a2, a4, b1, b2, b4, d1, d2, d4);
  out[3][2]  = - det3x3( a1, a2, a4, b1, b2, b4, c1, c2, c4);
        
  out[0][3]  = - det3x3( b1, b2, b3, c1, c2, c3, d1, d2, d3);
  out[1][3]  =   det3x3( a1, a2, a3, c1, c2, c3, d1, d2, d3);
  out[2][3]  = - det3x3( a1, a2, a3, b1, b2, b3, d1, d2, d3);
  out[3][3]  =   det3x3( a1, a2, a3, b1, b2, b3, c1, c2, c3);
}

double det4x4( double m[4][4] ) 
{
  double ans;
  double a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;
 

  a1 = m[0][0]; b1 = m[0][1]; 
  c1 = m[0][2]; d1 = m[0][3];

  a2 = m[1][0]; b2 = m[1][1]; 
  c2 = m[1][2]; d2 = m[1][3];

  a3 = m[2][0]; b3 = m[2][1]; 
  c3 = m[2][2]; d3 = m[2][3];

  a4 = m[3][0]; b4 = m[3][1]; 
  c4 = m[3][2]; d4 = m[3][3];

  ans = a1 * det3x3( b2, b3, b4, c2, c3, c4, d2, d3, d4)
    - b1 * det3x3( a2, a3, a4, c2, c3, c4, d2, d3, d4)
    + c1 * det3x3( a2, a3, a4, b2, b3, b4, d2, d3, d4)
    - d1 * det3x3( a2, a3, a4, b2, b3, b4, c2, c3, c4);
  return ans;
}

//double det3x3( a1, a2, a3, b1, b2, b3, c1, c2, c3 )
  //   double a1, a2, a3, b1, b2, b3, c1, c2, c3;
double det3x3( double a1, double a2, double a3, double b1, double b2, double b3, double c1, 
			  double c2, double c3 )
{
  double ans;

  ans = a1 * det2x2( b2, b3, c2, c3 )
    - b1 * det2x2( a2, a3, c2, c3 )
    + c1 * det2x2( a2, a3, b2, b3 );
  return ans;
}

//double det2x2( a, b, c, d)
  //   double a, b, c, d; 
double det2x2( double a, double b, double c, double d)
{
  double ans;
  ans = a * d - b * c;
  return ans;
}

void save_imageP6(int Width, int Height, char* fname,unsigned char* pixels) {
  FILE *fp;
  const int maxVal=255; 
  
  printf("Saving image %s: %d x %d\n", fname,Width,Height);
  fp = fopen(fname,"wb");
  if (!fp) {
        printf("Unable to open file '%s'\n",fname);
        return;
  }
  fprintf(fp, "P6\n");
  fprintf(fp, "%d %d\n", Width, Height);
  fprintf(fp, "%d\n", maxVal);

  for(int j = 0; j < Height; j++) {
		  fwrite(&pixels[j*Width*3], 3,Width,fp);
  }

  fclose(fp);
}

// Output in P3 format, a text file containing:
// P3
// ncolumns nrows
// Max colour value (for us, and usually 255)
// r1 g1 b1 r2 g2 b2 .....
void save_imageP3(int Width, int Height, char* fname,unsigned char* pixels) {
	FILE *fp;
	const int maxVal=255;
	
	printf("Saving image %s: %d x %d\n", fname,Width,Height);
	fp = fopen(fname,"w");
	if (!fp) {
		printf("Unable to open file '%s'\n",fname);
		return;
	}
	fprintf(fp, "P3\n");
	fprintf(fp, "%d %d\n", Width, Height);
	fprintf(fp, "%d\n", maxVal);
	
	int k = 0 ;
	for(int j = 0; j < Height; j++) {
		
		for( int i = 0 ; i < Width; i++)
		{
			fprintf(fp," %d %d %d", pixels[k],pixels[k+1],pixels[k+2]) ;
			k = k + 3 ;
		}
		fprintf(fp,"\n") ;
	}
	fclose(fp);
}

float dotProduct(float x1, float y1,float z1, float x2, float y2, float z2){
  return x1*x2 + y1*y2 + z1*z2;
}
float vecLength(float x1, float y1,float z1){
  return sqrt(x1*x1 + y1*y1+ z1*z1);
}
float vecLengthSquared(float x1, float y1,float z1){
  return x1*x1 + y1*y1+ z1*z1;
}
vec* crossProduct(float x1, float y1,float z1, float x2, float y2, float z2){
  vec * result = (vec*) malloc(sizeof(vec));
  result->x = y1*z2 - z1*y2;
  result->y = z1*x2 - x1*z2;
  result->z = x1*y2 - y1*x2;
  return result;
}
vec* unitVec(float x1, float y1,float z1){
  vec * result = (vec*) malloc(sizeof(vec));
  result->x = x1/vecLength(x1, y1, z1);
  result->y = y1/vecLength(x1, y1, z1);
  result->z = z1/vecLength(x1, y1, z1);
  return result;
}
point* at(ray* r, float t){
  point * result = (point*) malloc(sizeof(point));
  result->x = r->origin->x + t*(r->direction->x);
  result->y = r->origin->y + t*(r->direction->y);
  result->z = r->origin->z + t*(r->direction->z);
  return result;
}

void setFaceNormal(hitRecord* h, ray* r, vec* outNorm){
  h->frontFace = dotProduct(r->direction->x, r->direction->y, r->direction->z, outNorm->x, outNorm->y, outNorm->z) > 0;
 if(h->frontFace){
  h->normal = outNorm;
 }else{
  outNorm -> x = -(outNorm -> x);
  outNorm -> y = -(outNorm -> y);
  outNorm -> z = -(outNorm -> z);
  h->normal = outNorm;
 }
}

vec* randomUnitS() {
  while (1) {
    srand(time(0)); 
    vec* p = (point*) malloc(sizeof(point));
    p -> x = (float) (rand() % 2)-1;
    p -> y = (float) (rand() % 2)-1;
    p -> z = (float) (rand() % 2)-1;
    if(vecLengthSquared(p->x, p->y, p->z) >= 1){
      continue;
    } 
    return p;
  }
}

int hitSphere(point* center, float radius1, float radius2, float radius3,ray* r, float tMin, float tMax, hitRecord* rec, color* colors) {
  vec oc = {r->origin->x - center->x, r->origin->y - center->y, r->origin->z - center->z};
  float a = vecLengthSquared(r->direction->x, r->direction->y, r->direction->z);
  float b2 = dotProduct(oc.x,oc.y,oc.z, r->direction->x, r->direction->y, r->direction->z);
  float c = vecLengthSquared(oc.x,oc.y,oc.z) - radius1*radius2;
  float d = b2*b2 - a*c;
  if(d < 0){
    return 0;
  }
  float sd = sqrt(d);
  float root = (-b2 - sd)/a;
  if(root < tMin || tMax < root){
    //root = (-b2 + sd) / a;
  }
  rec->t = root;
  rec->p = (point*) malloc(sizeof(point));
  rec->normal = (vec*) malloc(sizeof(vec));
  rec->p = at(r, rec->t);
  vec * outNormal = (vec*) malloc(sizeof(vec));
  outNormal -> x= (rec->p->x - center->x)/radius1;
  outNormal -> y= (rec->p->y - center->y)/radius2;
  outNormal -> z= (rec->p->z - center->z)/radius3;
  setFaceNormal(rec, r, outNormal);
  rec->c = colors;

  rec->normal->x = (rec->p->x - center->x) / radius1;
  rec->normal->y = (rec->p->y - center->y) / radius2;
  rec->normal->z = (rec->p->z - center->z) / radius3;
  return 1;
}

int hitAll(struct sphere spheres[], int sphereCount, ray* r, float tMin, float tMax, hitRecord* rec) {
  hitRecord* tempR = (hitRecord*) malloc(sizeof(hitRecord));
  int hitAny = 0;
  float closestSoFar = tMax;

  for(int i = 0; i < sphereCount; i++){
    point* center = (point*) malloc(sizeof(point));
    color* col = (color*) malloc(sizeof(color));
    center->x = spheres[i].position[0];
    center->y = spheres[i].position[1];
    center->z = spheres[i].position[2];
    col->x = spheres[i].color[0];
    col->y = spheres[i].color[1];
    col->z = spheres[i].color[2];
    float ra1 = spheres[i].scale[0];
    float ra2 = spheres[i].scale[1];
    float ra3 = spheres[i].scale[2];
    if(hitSphere(center, ra1, ra2, ra3, r, tMax, tMin, rec, col)){
      hitAny = 1;
      closestSoFar = tempR->t;
      rec = tempR;
    }
  }

  return hitAny;
}

color* rayColor(ray* r, float background[], struct sphere spheres[], int sphereCount){
  color* result = (color*) malloc(sizeof(color));
  hitRecord* rec = (hitRecord*) malloc(sizeof(hitRecord));
  float inf = 100000;
  if (hitAll(spheres, sphereCount, r, 0.0001, inf, rec)){
    result->x = rec->c->x;
    result->y = rec->c->y;
    result->z = rec->c->z;
    return result;
  }
  result->x = background[0];
  result->y = background[1];
  result->z = background[2];
  return result;
}


int main(int argc , char* argv[]){
  float near;
  float left;
  float right;
  float bottom;
  float top;
  int res[2];
  float background[3];
  float ambient[3];
  char output_name[20];
  struct sphere spheres[14]; //array of sphere struct
  int sphere_counter = 0; //number of spheres given by the file
  struct light lights[9]; //array of light struct
  int light_counter = 0; //number of lights given by the file
  

  FILE* fp = fopen(argv[1] , "r");
  if(fp == NULL){
    perror("failed to open file");
    exit(1);
  }
  // ** READ INPUT FROM FILE **
  // strtok tokenizes the line by detected white space 
  // goes through if else statement to detect which keyword it is to seperate the informations
  char buffer[255];
  while(fgets(buffer, sizeof(buffer) , fp)){
    char* piece = strtok(buffer, " ");

    if(strcmp(piece , "NEAR") == 0){

      piece = strtok(NULL, " ");
      near = strtof(piece ,NULL);

    }else if(strcmp(piece, "LEFT") == 0){

      piece = strtok(NULL , " ");
      left = strtof(piece , NULL);

    }else if(strcmp(piece , "RIGHT") == 0){

      piece = strtok(NULL , " ");
      right = strtof(piece , NULL);

    }else if (strcmp(piece , "BOTTOM") == 0){

      piece = strtok(NULL , " ");
      bottom = strtof(piece , NULL);

    }else if(strcmp(piece , "TOP") == 0){
      
      piece = strtok(NULL , " ");
      top = strtof(piece , NULL);

    }else if(strcmp(piece , "RES")== 0){

      for(int i = 0; i < 2; i++){
        piece = strtok(NULL , " ");
        res[i] = strtod(piece , NULL);
      }
     
    }else if(strcmp(piece , "SPHERE") == 0){
      int pos_counter = 0;
      int scale_counter = 0;
      int color_counter = 0;
      int k_counter = 0;

      for(int i = 0; i < 15; i++){
        piece = strtok(NULL , " ");
        if(i == 0){
          //name
          strcpy(spheres[sphere_counter].name , piece);

        }else if(i > 0 && i <= 3){
          //3 position values
          spheres[sphere_counter].position[pos_counter] = strtof(piece , NULL);
          pos_counter++;

        }else if(i > 3 && i <= 6){
          //3 scale factors
          spheres[sphere_counter].scale[scale_counter] = strtof(piece , NULL);
          scale_counter++;

        }else if(i > 6 && i <= 9){
          //3 color factors
          spheres[sphere_counter].color[color_counter] = strtof(piece , NULL);
          color_counter++;

        }else if(i > 9 && i <= 13){
          //4 k coefficents
          spheres[sphere_counter].k[k_counter] = strtof(piece ,NULL);
          k_counter++;

        }else if(i == 14){
          //n exp value
          spheres[sphere_counter].n = strtod(piece , NULL);

        }
      }
       sphere_counter++;

    }else if(strcmp(piece , "LIGHT") == 0){
      int lpos_counter = 0;
      int intensity_counter = 0;

      for(int j = 0; j < 7; j++){
        piece = strtok(NULL , " ");
        if(j == 0){
          //name
          strcpy(lights[light_counter].name , piece);

        }else if(j > 0 && j <= 3){
          //3 position values
          lights[light_counter].postition[lpos_counter] = strtof(piece , NULL);
          lpos_counter++;

        }else if(j > 3 && j <= 6){
          //3 intensity factors
          lights[light_counter].intensity[intensity_counter] = strtof(piece, NULL);
          intensity_counter++;

        }
      }
      light_counter++;

    }else if(strcmp(piece , "BACK") == 0){
      for(int i = 0; i < 3; i++){
        //3 background values
        piece = strtok(NULL , " ");
        background[i] = strtof(piece , NULL);
      }
    }else if(strcmp(piece , "AMBIENT") == 0){
      for(int i = 0; i < 3; i++){
        //3 ambient factors
        piece = strtok(NULL , " ");
        ambient[i] = strtof(piece , NULL); 
      }
    }else if(strcmp(piece,"OUTPUT") == 0){
      //output file name
      piece = strtok(NULL , " ");
      strcpy(output_name , piece);
    }
  }
  fclose(fp);

  //spheres[0].position[0] = 0;
  //spheres[0].position[1] = 0;
  //spheres[0].position[2] = -1;

  unsigned char* pixels;
  unsigned char px[3*res[0]*res[1]];
  pixels = px;

  float aspectRatio = (float)(res[0])/(float)(res[1]);
  float viewportHeight = 2.0;
  float viewportWidth = aspectRatio * viewportHeight;
  float focal = 1.0;

  point origin = {0.0, 0.0, 0.0};
  vec horizontal = {viewportWidth, 0, 0};
  vec vertical = {0, viewportHeight, 0};
  vec lowerLeft;
  lowerLeft.x = origin.x - horizontal.x/2.0 - vertical.x/2.0 - 0;
  lowerLeft.y = origin.y - horizontal.y/2.0 - vertical.y/2.0 - 0;
  lowerLeft.z = origin.z - horizontal.z/2.0 - vertical.z/2.0 - focal;

  int k = 0;
  for (int j = res[1]-1; j >= 0; --j) {
    for (int i = 0; i < res[0]; ++i) {
      float u = (float)(i) / (res[0]-1);
      float v = (float)(j) / (res[1]-1);
      vec dir;
      dir.x = lowerLeft.x + u*horizontal.x + v*vertical.x - origin.x;
      dir.y = lowerLeft.y + u*horizontal.y + v*vertical.y - origin.y;
      dir.z = lowerLeft.z + u*horizontal.z + v*vertical.z - origin.z;
      ray r = {&origin, &dir};
      color* pixel = rayColor(&r, background, spheres, sphere_counter);
      pixels[k] = pixel->x * 255.0;
      pixels[k+1] = pixel->y * 255.0;
      pixels[k+2] = pixel->z * 255.0;
      k = k + 3;
    }
  }
  
  save_imageP6(res[0], res[1], output_name, pixels);
}


/**
// This main function is meant only to illustrate how to use the save_imageXX functions.
// You should get rid of this code, and just paste the save_imageXX functions into your
// raytrace.cpp code. 
int main() {
	int Width = 128;	// Move these to your setup function. The actual resolution will be
	int Height= 128;	// specified in the input file
    char fname3[20] = "sceneP3.ppm"; //This should be set based on the input file
	char fname6[20] = "sceneP6.ppm"; //This should be set based on the input file
	unsigned char *pixels;
	// This will be your image. Note that pixels[0] is the top left of the image and
	// pixels[3*Width*Height-1] is the bottom right of the image.
    unsigned char px[3*Width*Height];
    pixels = px;

	// This loop just creates a gradient for illustration purposes only. You will not use it.
	float scale = 128.0 / (float) Width ;
	int k = 0 ;
	for(int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			int c = (i+j)*scale ;
			pixels[k] = c;
			pixels[k+1] = c;
			pixels[k+2] = c;
			k = k + 3 ;
		}
	}
	save_imageP3(Width, Height, fname3, pixels);
	save_imageP6(Width, Height, fname6, pixels);
}
**/

// ** END OF READING FROM FILE **

  // ** TESTING THE READING **
  // printf("NEAR %f\n LEFT %f\n RIGHT %f\n BOTTOM %f\n TOP %f\n RES %d %d\n", near,left,right,bottom,top,res[0],res[1]);
  // for(int i = 0; i < sphere_counter; i++){
  //   printf("%s %f %f %f %f %f %f %f %f %f %f %f %f %f %d\n" , spheres[i].name , spheres[i].position[0], spheres[i].position[1] , spheres[i].position[2] ,
  //   spheres[i].scale[0] , spheres[i].scale[1] , spheres[i].scale[2] , spheres[i].color[0], spheres[i].color[1], spheres[i].color[2]
  //   , spheres[i].k[0],  spheres[i].k[1],spheres[i].k[2],spheres[i].k[3], spheres[i].n);
  // }
  
  // for(int i = 0; i < light_counter; i++){
  //   printf("%s %f %f %f %f %f %f\n", lights[i].name,lights[i].postition[0], lights[i].postition[1], lights[i].postition[2] , lights[i].intensity[0],
  //   lights[i].intensity[1],lights[i].intensity[2]);
  // }
  // printf("background %f %f %f\n" , background[0] , background[1], background[2]);
  // printf("ambient %f %f %f\n" , ambient[0], ambient[1], ambient[2]);
  // printf("OUTPUT NAME %s" , output_name);
  // ** END OF TESTING READING ** you can comment this out its for my own tester and also to make sure i dont make weird mistakes...
  // to run , gcc - o raytracer raytracer.c 
  // then , raytracer.exe testAmbient.txt
  // header file contains the struct