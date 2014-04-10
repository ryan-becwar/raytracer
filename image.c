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
	object_t *obj;
	double mindist;
	drgb_t thispix = {0.0, 0.0, 0.0};
	
	/*ryans old code
	
	//* Get the object (plane or sphere).        
	//* Later we will use find_closest_object()  
	//* to get the closest object                
	//	list_reset(model->objs);
	//	assert(list_get_entity(model->objs) != NULL);

	//	fprintf(stderr, "before obj assignment from objs listran\n");
	obj = (object_t *)list_get_entity(model->objs);
	//	fprintf(stderr, "after obj assignment\n");

	//	obj = (object_t *)find_closest_object(model, *base, *dir, last_hit, &dist);
	//	fprintf(stderr, "after obj assignment\n");
	assert(obj != NULL);

	// get the distance and the color
	dist = obj->hits(obj, base, dir);  
	obj->ambient(obj, obj->mat, &thispix);
	
	*/
	
	closest = find_closest_object(model->objs, base, dir, last_hit, &mindist);
	
	if (closest == NULL)
		return;
	
	//get ambient and store in thispix
	obj->getambient(&thispix);

	if(mindist > 0){
		total_dist += dist;
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
	camera_t *cam = model->cam;

	camera_getdir(cam, x, y, &raydir);
	//	fprintf(stderr, "camera get dir ran in makepixel\n");


	/*  The ray_trace function determines the pixel color in */
	/*  d_rgb units.   The last two parameters are used ONLY */
	/*  in the case of specular (bouncing) rays              */
	ray_trace(model, &cam->view_point, &raydir, &pix, 0.0, NULL);
	//	fprintf(stderr, "ray trace ran in make pixel\n");

	camera_store_pixel(cam, x, y, &pix);
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
	for (x = 0; x < cam->pixel_dim[0]; x++) {
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
	for (y = 0; y < cam->pixel_dim[1]; y++) {
		make_row(model, y);
	}


	fprintf(stderr, "for loop in image create ran\n");
	/*  write the image                           */
	camera_write_image(model->cam, out);
}

