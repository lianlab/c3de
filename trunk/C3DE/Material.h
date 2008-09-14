#ifndef MATERIAL_H
#define MATERIAL_H

struct Material
{	
	Material(){r = 0.0f; g = 0.0f;b=0.0f;a=0.0f;}
	Material(float a_r, float a_g, float a_b, float a_a){r= a_r;g=a_g;b=a_b;a=a_a;}
	
	float r;
	float g;
	float b;
	float a;
};



#endif