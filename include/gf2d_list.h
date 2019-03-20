#ifndef __GF2D_LIST_H__
#define __GF2D_LIST_H__
#include <SDL.h>

typedef struct
{
	void *data;
}ListElementData;

typedef struct
{
	ListElementData *elements;
	Uint32 size;
	Uint32 count;
}List;

/***
@brief allocated a new empty list
@return Null on memory error or a new empty list
***/
List gf2d_list_new();

/***
@brief allocate a new empty list of size'count'
@param count how any elements you wish to support in this list
@return NULL on mem error or a new empty list
***/
List gf2d_list_new_size(Uint32 count);

/***
@brief deletes a list that has been previously allocated
@param list to delete
***/
void gf2d_list_delete(List *list);

/***
@brief get the data stored at the nth element
@param list the list to pull data from
@param n which element to look for
@return NULL on error(such as if n> the element count) or the address of the data otherwise
***/
void gf2d_list_get_nth(List *list, Uint32 n);

/***
@brief add an element to the end of the list
@note must catch the returned list to replace the list you had
@param list the list being added to
@param data the data assigned to the list
@return NULL on error or the list
***/
List gf2d_list_append(List *list, void *data);

/***
@brief insert a new element at the position provided
@param list the list being added to
@param data the data being placed
@param the location n that you want the data to go to
return -1 on error, 0 otherwise
***/
List gf2d_list_insert(List *list, void *data, Uint32 n);

/***
@brief delete the element at the nth position in the array
@param list the list being changed
@param the position of the data being deleted. this is no-op is the nth element is beyond the scope of the list
@return -1 on error, 0 otherwise
***/
List gf2d_list_delete_nth(List *list, Uint32 n);

/***
@brief delete the item at the end of the list
@note this does not clean up the information that the list is referring to
@param list the list to delete from
@return -1 on error, 0 otherwise
***/
List gf2d_list_delete_last(List *list);

/***
@brief delete the first element in the list point to the addressof data
@note does not delete the actual data
@param list the list to delete data from
@oaram data used to match against which element to delete
@return -1 on error, 0 otherwise
***/
List gf2d_list_delete_data(List *list, void *data);

/***
@brief get the number of tracked elements in this list
@param the list
@return the count in the list. Will be zero if list was NULL
***/
Uint32 gf2d_list_get_count(List *list);

/***
@brief iterate over each element in the array and call the function provided
@param list to iterate over
@param fucntion a pointer to a func that will be called. Data will be set to the list data element, context will be the contextData provided
@param contextData the data that will also be provided to the function pointer for each element
***/
void gf2d_list_foreach(List *list, void(*function)(void *data, void *context), *contextData);

/***
@brief add the lements from b into a 
@note the data is not duplicated and b will still point to the same data that is now also referenced in a
@note the new address of a is returned
@param a the list that will get new items added to it
@param b the list that will provide the new items for a
@return NULL on failure, a pointer to the new list otherwise
***/
List gf2d_list_concat(List *a, List *b);

/***
@brief same as gf2d_list_concat but b is freed when complete
@note the new address of a is returned
@param a the list to add items to
@param b the list to provide the items. This list is freed, but the data referenced is now referenced by a
@return null on fail, a pointer to the new list otherwise
***/
List gf2d_list_concat_free(List *a, List *b);

#endif
