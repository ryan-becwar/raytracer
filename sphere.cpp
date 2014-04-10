//sphere.cpp
//wrblack

#include "ray.h"

pparm_t sphere_parse[] =
{
	{"center", 3, sizeof(double), "%lf", 0}
	{"radius", 1, sizeof(double), "%lf", 0}
}

#define NUM_ATTRS (sizeof(sphere_parse) / sizeof(pparm_t))

//overloaded constructor
sphere_t::sphere_t(FILE *in, model_t *model, int attrmax): object_t(in, model)
{
	//this is for the parser
	int mask;
	
	//set "sphere" to obj_type in the object_t object.
	//char   obj_name[NAME_LEN];  /* left_wall, center_sphere */
	strcpy(obj_type, "sphere");
	
	//akin to camera.cpp's constructor
	//
	//
	
	sphere_parse[0].loc = &center;
	sphere_parse[1].loc = &radius;
	mask = parser(in, sphere_parse, NUM_ATTRS, attrmax);
	assert(mask == 3);
	
	//vec_unit(radius, radius)
	//vec_copy(radius, hitnorm)
}

double sphere_t::hits(vec_t *base, vec_t *dir)
{

	//Brought over from C code, this should work
        double a, b, c, discrim, dist;

        vec_t newBase, hit, normal;
        vec_diff(base, &center, &newBase);

        a = vec_dot(dir, dir);
        b = 2 * vec_dot(&newBase, dir);
        c = vec_dot(&newBase, &newBase) - (radius * radius);

        discrim = ((b * b) - (4*a*c));
        if(discrim <= 0)
                return -1;

        dist = ((-1 * b) - sqrt(discrim)) / (2 * a);

        vec_scale(dist, dir, &hit);
        vec_sum(base, &hit, &hit);

        obj->last_hit = hit;

        vec_diff(&center, &hit, &normal);
        vec_unit(&normal, &normal);

        last_normal = normal;

        // extract sph pointer from object structure
        // see notes for sphere_hits function

        // return distance
        return(dist);



	//WIP!!
	/*
	vec_t hit, sdir, hitdir, vloc;
	
	double a, b, c, t, d;
	
	//steps from unit_6.pdf
	//1. Set center of sphere to origin
	//c' = c - c which is (0, 0, 0)
	//v' = v- c viewpoint minus sphere center
	vec_diff(&center, base, &vloc);
	
	//2. calc D dot D
	//a = D dot D
	a = vec_dot(dir, dir);
	
	//3. b = 2 (V' dot D)
	b = 2.0 * vec_dot(&vloc, dir);
	//4. c = V' dot V' - r^2
	c = vec_dot(&vloc, &vloc) - (radius * radius);
	//5. (b^2-4ac)
	d = b * b - 4 * a * c;
	
	//7.  if ray hits sphere
	if (d > 0.0)
		t = (b * (-1.0) - sqrt(d)) / ( 2 * a );
	//6. if ray doesn't hit or hits tangent
	else
		return -1;
	
	//8. H = V + t-hit * D
	//t (aka t-hit) * D = t*Dir
	vec_scale(t, dir, &sdir);
	//V+ tD = hit
	vec_sum(base, &sdir, &hit);
	
	//9. copy hit into obj->last_hit
	vec_copy(&hit, &last_hit);
	
	//10. determine surface normal at hitpoint
	//Normal Vector
	
	if (hit.z < 0.0) {
		vec_copy(&hit, &last_hit);
		vec_diff(&center, &hit, &hitdir);
		vec_unit(&hitdir, &hitnorm);
		return t;
	} else if (d > 0.0) {
		t = (b * (-1.0) - sqrt(d)) / (2 * a);
		return t;
	} else {
		return -1;
	}
	*/
}

void sphere_t::printer(FILE *out)
{
	//any need to call object_t's printer?
	//format taken from camera.cpp
	fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n", "center",
			center.x, center.y, center.z);
	fprintf(out, "%-12s %5.1lf \n", "radius", radius);
	//scale output if needed
	fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n", "scale",
			scale.x, scale.y, scale.z);
}
