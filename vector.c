/**  vector.c   **/

//Written by Ryan Becwar in section 3 of CPSC 102 at Clemson University
//January 15, 2014
//Updated 3/5/14

#include "vector.h"

/*  This file contains function definitions for    */
/*  for 3D vector operations                       */

/* Compute the sum of two vectors */
/* v3 = v2 + v1; */
void vec_sum(
vec_t *v1,   /* addend */
vec_t *v2,   /* addend */
vec_t *v3)   /* result */
{
	v3->x = v1->x + v2->x;
	v3->y = v1->y + v2->y;
	v3->z = v1->z + v2->z;

//	fprintf(stderr, "v1 x: %f\nv1 y: %f\nv1 z: %f\n", v1->x, v1->y, v1->z);
}

/* Compute the difference of two vectors */
/* v3 = v2 - v1 */
void vec_diff(
vec_t *v1,   /* subtrahend */
vec_t *v2,   /* minuend    */
vec_t *v3)   /* result     */
{
	v3->x = v2->x - v1->x;
	v3->y = v2->y - v1->y;
	v3->z = v2->z - v1->z;

}

/* Compute the componentwise product of two vectors */
/* v3 = v2 * v1; */
void vec_mult( 
vec_t *v1,   /* Input vector 1 */
vec_t *v2,   /* Input vector 2 */
vec_t *v3)   /* result         */
{
	v3->x = v1->x * v2->x;
	v3->x = v1->y * v2->y;
	v3->x = v1->z * v2->z;
}

/* Return the (dot) inner product of two input vectors     */
double vec_dot(
vec_t *v1,   /* Input vector 1 */
vec_t *v2)   /* Input vector 2 */
{
	return(v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

/* Return length of a 3d vector */
double vec_len(
vec_t *v1)  /* Vector whose length is desired */
{
	return(sqrt(pow(v1->x, 2) + pow(v1->y, 2) + pow(v1->z, 2)));
}

/* Scale a 3d vector by multiplying each element by scale factor */
void vec_scale(
double fact,   /* Scale factor */
vec_t *v1,      /* Input vector */
vec_t *v2)      /* Output vector */
{
	v2->x = v1->x * fact;
	v2->y = v1->y * fact;
	v2->z = v1->z * fact;
}

/* Construct a unit vector v2 in direction of input vector v1 */
void vec_unit(
vec_t *v1,    /* Input vector      */
vec_t *v2)    /* output unit vec   */
{
double mult = 1 / vec_len(v1);
vec_scale(mult, v1, v2);
}

/* Copy vector v1 to v2 another */
void vec_copy(
vec_t *v1,   /* input vector */
vec_t *v2)   /* output vector */
{
	v2->x = v1->x;
	v2->y = v1->y;
	v2->z = v1->z;
}

/* Read in values of vector from file */
/* Return the # of items read	*/
int vec_read(
FILE *in,     /* input file  */
vec_t *v1)    /* vector from input file */
{
	int numRead = fscanf(in, "%lf %lf %lf", &v1->x, &v1->y, &v1->z);

	if(numRead != 3){
		fprintf(stderr, "Values not read successfully\n");
		exit(EXIT_FAILURE);
	}

	return(numRead);
}

/* Print values of vector to file */
void vec_print(
FILE *out,     /* output file */
char *label,   /* label string */
vec_t *v1)      /* vector to print */
{
fprintf(out, "%s %lf, %lf, %lf\n", label, v1->x, v1->y, v1->z);
}

//Compute the cross product
void vec_cross(vec_t *v1, vec_t *v2, vec_t *v3){

	vec_t v4;

	v4.x = v1->y * v2->z - v1->z * v2->y;
	v4.y =v1->z * v2->x - v1->x * v2->z;
	v4.z =v1->x * v2->y - v1->y * v2->x;

	*v3 = v4;
}

//project a vector onto a plane
void vec_project(vec_t *n, vec_t *v, vec_t *p){

	vec_t *r = (vec_t *)malloc(sizeof(vec_t));
	vec_scale(vec_dot(n, v), n, r);
	vec_diff(r, v, p);

	free(r);
}

//reflect a vector from a surface plane]
void vec_reflect(vec_t *n, vec_t *w, vec_t *v){

	vec_t *u = (vec_t *)malloc(sizeof(vec_t));

	vec_unit(w, u);
	vec_scale(-1, u, u);

	vec_scale((2*vec_dot(u, n)), n, v);
	vec_diff(u, v, v);

	free(u);
}

//Apply transform matrix to a vector
//v2 out
void vec_xform(mtx_t *m, vec_t *v1, vec_t *v2){

	vec_t v3;

	v3.x = vec_dot(&(m->row[0]), v1);
	v3.y = vec_dot(&(m->row[1]), v1);
	v3.z = vec_dot(&(m->row[2]), v1);

	*v2 = v3;
}


//transpose a matrix
//m2 out
void mtx_transpose(mtx_t *m1, mtx_t *m2){

	mtx_t m3;

	m3.row[0].x = m1->row[0].x;
	m3.row[0].y = m1->row[1].x;
	m3.row[0].z = m1->row[2].x;

	m3.row[1].x = m1->row[0].y;
	m3.row[1].y = m1->row[1].y;
	m3.row[1].z = m1->row[2].y;

	m3.row[2].x = m1->row[0].z;
	m3.row[2].y = m1->row[1].z;
	m3.row[2].z = m1->row[2].z;

	*m2 = m3;
}
