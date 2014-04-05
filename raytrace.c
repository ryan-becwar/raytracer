//Ryan Becwar, Section 3, 2/26/14

/*  raytrace.c  */

/*  find_closest_object() function
    arguments:
       model_t *model - the model structure
       vect_t *base - base of the ray (viewpoint)
       vect_t *dir - unit direction vector of the ray
       object_t *last_hit - the last hit object
       double *retdist - store distance to the hit point here

     	 if no object is hit, then retdist will have the value -1, 
	       and NULL will be returned 
		 if an object is hit, retdist will end up with the mindist
		    and minobj will be a non-NULL object that is returned 
*/


#include "ray.h"


object_t *find_closest_object(model_t *model, vec_t base, vec_t dir,
                              object_t *last_hit, double *retdist)     {
	object_t *minobj = NULL;
	double mindist = -1.0;


	// other declarations
	object_t *curobj;


	// process entire list of objects to see if any are hit by the ray
	// how do you process a list??
	list_reset(model->objs);

	while(list_not_end(model->objs)){
		curobj = (object_t *)list_get_entity(model->objs);


		// 	if current object from the list is not the last_hit,
		//			get the distance
		if(curobj != last_hit){
			*retdist = curobj->hits(curobj, &base, &dir);

			if((*retdist >= 0) && ((mindist <= 0) || (*retdist < mindist))){
				mindist = *retdist;
				minobj = curobj;
			}
		}
		// 		and if that distance is smaller than the last mindist
		//			i.e. the ray hits that object at a smaller distance
		//				- - then remember that distance in mindist
		// 			- - and remember that object in minobj

		list_next_link(model->objs); 

	}



	// save the mindist to retdist 
	*retdist = mindist;

	// and return the minobj
	return minobj;


}


