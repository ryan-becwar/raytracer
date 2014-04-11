/* list.c */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

link_t::link_t(void)
{
	next = NULL;
	entity = NULL;

}

link_t::link_t(void *newentity)
{
	next = NULL;
	entity = newentity;

}

link_t::~link_t(void)
{
   fprintf(stderr, "in link destructor \n");
}

void link_t::set_next(link_t *new_next)
{
	next = new_next;
}

link_t * link_t::get_next()
{
	return(next);


}

void * link_t::get_entity()
{
	return entity;
}


list_t::list_t()
{
	first = NULL;
	last = NULL;
	current = NULL;
}


void list_t::add(void *entity)
{
	link_t *link = new link_t(entity);

	if(first == NULL){
		first = link;
	} else {
		last->set_next(link);
	}

	current = link;
	last = link;

/* Create a new link passing it the entity pointer */




/* Now add the link to the list using generally the */
/* same approach as the C version                   */

}

void list_t::reset(void)
{
	current = first;
}

int list_t::not_end(void)
{
	if(current == NULL){
		return 0;
	} else {
		return 1;
	}
}

void list_t::next_link(void)
{
   assert(current != NULL);
	current = current->get_next();
}

void *list_t::get_entity(void)
{
   assert(current != NULL);

	return(current->get_entity());

}

list_t::~list_t()
{
	reset();
   link_t *kill;
   fprintf(stderr, "in list destructor \n");

/* Delete each link_t in the list */
	reset();

	while(not_end()){
		kill = current;
		first = first->get_next();
		delete(kill);
		reset();
	}


}

//Commenting out these functions as not included in ray.h
/*
void list_t::insert(void *entity){

	link_t * link = new link_t(entity);

	//list is empty
	if(first == NULL){

		first = link;
		current = link;
		last = link;

	//current is first link
	} else if (current == first){

		link->set_next(current);
		first = link;
		current = link;

	//current is not first link
	} else {

		link_t *traverse = first;

		while(traverse->get_next() != current){
			traverse = traverse->get_next();
		}
		traverse->set_next(link);
		link->set_next(current);
		current = link;
	}
}

void list_t::remove(void){

	//List is empty
	if(current == NULL){

		//Does nothing
	//List has one element
	} else if(first == last){

		delete(current);

		first = NULL;
		last = NULL;
		current = NULL;

	//Deleting first element of mutli element list
	} else if((first == current) && (current != last)){

		first = current->get_next();
		delete(current);
		current = first;

	//Deleting not the first element
	} else {

		link_t *traverse = first;

		while(traverse->get_next() != current){
			traverse = traverse->get_next();
		}
		//deleting last link
		if(last == current){

			last = traverse;
			delete(current);
			last->set_next(NULL);
			current = last;

		//Deleting a middle link
		} else {

			traverse->set_next(current->get_next());
			delete(current);
			current = traverse;
		}
	}
}
*/
