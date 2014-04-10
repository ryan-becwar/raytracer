//Ryan Becwar

#include "ray.h"

pparm_t plane_parse[] =
{
	{"point", 3, sizeof(double), "%lf", 0},
	{"normal", 3, sizeof(double), "%lf", 0}
};

#define NUM_ATTRS (sizeof(plane_parse) / sizeof(pparm_t));

plane_t::plane_t(FILE *in, model_t *model, int attrmax):object_t(in, model){

	int mask;

	strcpy(obj_type, "plane");

	plane_parse[0].loc = &point;
	plane_parse[1].loc = &normal;
	mask = parser(in, plane_parse, NUM_ATTRS, attrmax);
	assert(mask == 3);

	vec_unit(&normal, &normal);
	vec_copy(&normal, &last_normal);

	ndotq = vec_dot(&point, &normal);
}


double plane_t::hits(vec_t *base, vec_t* dir){

	double ndotd;
	double t;
	double ndotb;

	ndotq = vec_dot(&normal, &point);
	ndotd = vec_dot(dir, &normal);

	/* ndotd = 0 -> ray is parallel to the plane */
	if (ndotd == 0)
		return(-1);

	ndotb = vec_dot(&normal, base);

	t = (ndotq - ndotb) / ndotd;

	if (t <= 0)
		return(-1);

	vec_scale(t, dir, &last_hitpt);
	vec_sum(&last_hit, base, &last_hitpt);

	if ((last_hit.z > 0.01) && (strcmp(obj_type, "projector")))
		return(-1);

	return(t);
}

void plane_t::printer(FILE *out){

	fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "normal", normal.x, normal.y, normal.z);
	fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "point", point.x, point.y, point.z);
}

//plane_t::~plane_t(){
//}

