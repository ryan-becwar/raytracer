//Ryan Becwar

#include "ray.h"

//What is the function of the private material_t rot variable?

tplane_t::tplane_t(FILE *in, model_t *model, int attrmax):plane)_t(in, model, attrmax){}

//Call's plane's printer and then prints tplane information
virtual void tplane_t::printer(FILE *out){
	plane_t::printer(out);

	cout << "Dimensions: " << dims[0] << " " << dims[1] << endl;

}

virtual void tplane_t::getambient(drgb_t *){

	int foreground = select();

	if(foreground){
		//I'm not quite sure what to do here
		//C code is:
		//material_getambient(obj, obj->mat, drgb_t);

		//Not sure if scope is needed
		material_getambient(drgb_t);
	} else {
		//even less clear here
		//Probably uses alt material
	}
}

virtual void tplane_t::getdiffuse(drgb_t *){}

//Function to determine whether point is in primary or secondary tile
int tplane_t::select(){

	//Indexes the tiles
	int x_index = (10000 + x) / x;
	int z_index = (10000 + z) / z;

	//All primary material tiles will have even sums,
	//all secondary material tiles will have odd sums
	if((x_index + z_index) % 2 == 0){
		return(1);
	} else {
		return(0);
	}
}
