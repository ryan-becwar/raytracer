/* William Black
	CPSC1020-2
	Lab 1
	--vector.c implementation--

	**cleaned Mar-2-2014**
*/	 

#include "vector.h"

/* Compute the sum of two vectors */
/* v3 = v2 + v1; */
void vec_sum(
vec_t *v1,   /* addend */
vec_t *v2,   /* addend */
vec_t *v3)   /* result */
{
	v3->x = v2->x + v1->x;
	v3->y = v2->y + v1->y;
	v3->z = v2->z + v1->z;
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
/* v3.c = v2.c * v1.c */
void vec_mult( 
vec_t *v1,   /* Input vector 1 */
vec_t *v2,   /* Input vector 2 */
vec_t *v3)   /* result         */
{
	v3->x = v2->x * v1->x;
	v3->y = v2->y * v1->y;
	v3->z = v2->z * v1->z;
}

/* Return the (dot) inner product of two input vectors */
double vec_dot(
vec_t *v1,   /* Input vector 1 */
vec_t *v2)   /* Input vector 2 */
{
	double product;
	product = (v1->x * v2->x) + 
				 (v1->y * v2->y) + 
				 (v1->z * v2->z);
	return product;
}

/* Return length of a 3d vector */
double vec_len(
vec_t *v1)  /* Vector whose length is desired */
{
//in 3D, length of vector v is |v| = sqrt(x^2 + y^2 + z^2)
	double length;
	length = 		sqrt(
						pow(v1->x, 2.0) + 
						pow(v1->y, 2.0) +
						pow(v1->z, 2.0));
	//if length is negative, make it positive
	if (length < 0) {
		length *= -1;
		return length;
	}
	else
		return length;
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
	double scale = 1.0 / vec_len(v1);
	vec_scale(scale, v1, v2);
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
   int numOfItemsRead = 0;

	if (in == NULL)
	{
		printf("Error: the input file does not exist.\n");
		exit(EXIT_FAILURE);
	}
	
	numOfItemsRead = fscanf(in, "%lf%lf%lf", &v1->x, &v1->y, &v1->z);
	
	if (numOfItemsRead < 3)
	{
		fprintf(stderr, "Did not read 3 values.\n");
		exit(EXIT_FAILURE);
	} else {
		return numOfItemsRead;
	}
	
	fclose(in);
}

/* Print values of vector to file */
void vec_print(
FILE *out,     /* output file */
char *label,   /* label string */
vec_t *v1)      /* vector to print */
{	
	char buffer[100];
	sprintf(buffer, "%s %8.3f %8.3f %8.3f\n", label, v1->x, v1->y, v1->z);
	fputs(buffer, out);
}
