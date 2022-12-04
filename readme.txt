** YORK UNIVERSITY EECS3431 Assignment3 **
Group Members: KyongRok Kim - 215813413 , Arian Quader - 218070607

This raytracer project has been written in C. raytracer.c contains all the functionality of this project and
header files, ray.h raytracer.h vector.h contains the definitions of struct data types used in this project.
No external libraries has been used in this project.

** Build/MakeFile **
For linux/Mac OS, go to command line and navigate to directory of the file and type "make" to build the executable file
and a execuatable file named raytracer.exe will be produced. Then within the command line, execute raytracer.exe with 
the appropriate txt file as the single argument
Example: raytracer.exe testExample.txt

For Windows, we were not able to generate MS VS build, hence please go to command line and navigate to the directory
and use the command gcc -o raytracer.exe raytracer.c -lm to compile c and create execuatable named raytracer.exe
then execute raytracer.exe with the appropriate txt file as the single argument
Example: raytracer.exe testExample.txt


** Report of Tests **
1. testAmbient.txt
2. testBackground.txt
3. testBehind.txt
4. testDiffuse.txt
5. testIllum.txt
6. testImgPlane.txt
7. testIntersection.txt
8. testRefelction.txt
9. testSample.txt
10. testShadow.txt
11. testSpecular.txt
