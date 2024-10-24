/*
#include<iostream>
#include<cstdio>
#include<string>

struct Vector3 {
    Vector3(double x,double y,double z=0):x(x),y(y),z(z){}
    std::string toString(const char* fmt="(%.2f,%.2f,%.2f)"){
        char buf[1000];
        std::sprintf(buf,fmt,x,y,z); 
        return std::string(buf);
    } 
    
    double x,y,z; 
};

struct Ray {
    Ray (Vector3 origin, Vector3 direction):
       origin(origin),direction(direction) {};
    
    Vector3 origin;     //射线的原点。
    Vector3 direction;	//射线的方向。 
};

int main() {
    Vector3 vo(0,0,0), v(1,1,1);
    Ray ray(vo,v);
    std::cout << ray.direction.toString() << std::endl;
} */
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
struct Vector{
    double x, y, z;
    Vector(double x, double y, double z = 0) : x(x), y(y), z(z){

    }
};
class Ray{
    Vector a, b;
public:
    Ray(Vector a, Vector b) : a(a), b(b){
    
    }
    double getlength(Vector a, Vector b){
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
    }
};
int main(){
    Vector v1(0, 0, 0), v2(1, 1, 1);
    Ray ray(v1, v2);
    cout << ray.getlength(v1, v2);
    return 0;
}