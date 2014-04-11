/*  image.c  */

#include "ray.h"
#include "rayfuns.h"

//=============================================================================
// ******* ray_trace( ) *******
// 
// 
//=============================================================================
void ray_trace (
   model_t *model,
   vec_t *base,                // view point
   vec_t *dir,                 // unit direction vector
   drgb_t *pix,                // pixel return location
   double total_dist,          // distance ray has travelled so far
   object_t *last_hit)         // most recently hit object
{
	object_t *closest = NULL;
	double mindist;
	drgb_t thispix = {0.0, 0.0, 0.0};
	
	closest = find_closest_object(model, *base, *dir, last_hit, &mindist);

	if (closest != NULL)
		//get ambient and store in thispix
		closest->getambient(&thispix);



	if(mindist > 0){
		total_dist += mindist;
		pix_scale((1/total_dist), &thispix, &thispix);
		pix_sum(&thispix, pix, pix);
	}
}


//=============================================================================
// ******* make_pixel( ) *******
//
//
//=============================================================================
void make_pixel(model_t  *model, int  x, int  y) {
	vec_t raydir;
	drgb_t pix = {0.0, 0.0, 0.0};
	vec_t *viewpt = NULL;
	camera_t *cam = model->cam;

	cam->getviewpt(viewpt);

	cam->getdir(x, y, &raydir);
	//	fprintf(stderr, "camera get dir ran in makepixel\n");


	/*  The ray_trace function determines the pixel color in */
	/*  d_rgb units.   The last two parameters are used ONLY */
	/*  in the case of specular (bouncing) rays              */
	ray_trace(model, viewpt, &raydir, &pix, 0.0, NULL);
	//	fprintf(stderr, "ray trace ran in make pixel\n");

	cam->store_pixel(x, y, &pix);
	//	fprintf(stderr, "camera store pixel ran in make pixel\n");

	return;
}


//=============================================================================
// ******* make_row( ) *******
// 
// 
//=============================================================================
void make_row(model_t  *model, int  y) 
{
	int x;
	camera_t *cam = model->cam;

	/*  for each pixel in the row, invoke make_pixel() */
	/*  to paint the pixel.                            */
	for (x = 0; x < cam->getxdim(); x++) {
		make_pixel(model, x, y);
	}
}


//=============================================================================
// ******* image_create( ) *******
// 
// 
//=============================================================================
void image_create(model_t  *model, FILE  *out) 
{
	int y;
	camera_t *cam = model->cam;

	/*  fire rays through each pixel in the window; */
	/*  for each row, invoke make_row() to paint    */
	/*  the row of pixels.                          */
	for (y = 0; y < cam->getydim(); y++) {
		make_row(model, y);
	}


	fprintf(stderr, "for loop in image create ran\n");
	/*  write the image                           */
	cam->camera_write_image(out);
}

