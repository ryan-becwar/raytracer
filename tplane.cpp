#include "ray.h"

tplane_t::tplane_t(FILE *in, model_t *model, int attrmax):plane)_t(in, model, attrmax){

virtual void tplane_t::printer(FILE *out){
	plane_t::printer(out);

	cout << "Dimensions: " << dims[0] << " " << dims[1] << endl;

}

virtual void tplane_t::getambient(drgb_t *){}

virtual void tplane_t::getdiffuse(drgb_t *){}

