#include "stdio.h"
#include "string.h"

#include "mac/list.h"
#include "mac/dlist.h"
#include "mac/queue.h"
#include "mac/cvector.h"
#include "mac/avl-tree.h"

typedef struct TF
{
	int passed;
	int failed;
} TF;

int TF_init( TF* self )
{
	int err = 0;;

	self->passed = 0;
	self->failed = 0;

	return err;
}

int TF_finish( TF* self )
{
	printf( "%d/%d tests passed\n", self->passed, self->passed+self->failed );
	printf( "%d/%d tests failed\n", self->failed, self->passed+self->failed );
	return 0;
}

#define TF_TEST(tf, val) _TF_test( tf, val, __FILE__, __LINE__ )

int _TF_test( TF* tf , int val, const char* pszfile, unsigned int lineno )
{
	int err = 0;
	if( val )
	{
		printf( "%s(%d): PASS\n", pszfile, lineno );
		tf->passed += 1;
	}
	else
	{
		printf( "%s(%d): FAIL\n", pszfile, lineno );
		tf->failed += 1;
	}
	return err;
}

int test_dlist(TF* tf)
{
	int i = 0;
	mac_dlist_t list;

	mac_dlist_init( &list, sizeof( int ), NULL );

	for( i = 0; i < 10; ++i )
		mac_dlist_ins_next( &list, mac_dlist_tail( &list ), &i );

	TF_TEST( tf, 10 == mac_dlist_size( &list ) );

	mac_dlist_node_t* node = mac_dlist_head( &list );

	i = 0;
	while( node )
	{
		int* val = (int*)mac_dlist_data( node );

		TF_TEST( tf, i == *val );

		node = mac_dlist_next( node );

		i++;
	}

	mac_dlist_destroy( &list );

	return 0;
}


int test_queue( TF* tf )
{
	int i = 0;
	mac_queue_t q;

	mac_queue_init( &q, sizeof( int ), NULL );

	for( i = 0; i < 10; ++i )
		mac_queue_enqueue( &q, &i );

	TF_TEST( tf, 10 == mac_queue_size( &q ) );

	mac_queue_destroy( &q );

	return 0;
}


int test_list(TF* tf)
{
	int i = 0;
	mac_list_t list;

	mac_list_init( &list, sizeof( int ), NULL );

	for( i = 0; i < 10; ++i )
		mac_list_ins_next( &list, mac_list_tail( &list ), &i );

	TF_TEST( tf, 10 == mac_list_size( &list ) );

	mac_list_node_t* node = mac_list_head( &list );

	i = 0;
	while( node )
	{
		int* val = (int*)mac_list_data( node );
		TF_TEST( tf, i == *val );

		node = mac_list_next( node );

		i++;
	}

	mac_list_destroy( &list );

	return 0;
}

int test_cvector( TF* tf )
{

	size_t i;
	cvector_t v;

	cvector_init( &v, sizeof(int) );

	for( i = 0; i < 50; ++i )
	{
		cvector_push_back( &v, &i );
	}


	for( i = 0; i < 50; ++i )
	{
		int* tmp = NULL;

		tmp = cvector_element_at( &v, i );

		TF_TEST( tf, i==*tmp );
	}


	cvector_finish( &v );
	return 0;
}


int string_compare( void* string1, void* string2 );
int string_compare( void* string1, void* string2 )
{
	int result = 0;

	result = strcmp((char *) string1, (char *) string2);

	if (result < 0) 
		result = -1; 
	else if (result > 0) 
		result = 1;   
	else 
		result = 0;

	return result;	 
}
int int_compare( void* val1, void* val2 )
{
	int result = 0;

	int* int1 = (int*)val1;
	int* int2 = (int*)val2;

	if ( *int1 < *int2 ) 
		result = -1; 
	else if ( *int1 > *int2 ) 
		result = 1;   
	else 
		result = 0;

	return result;	 
}

mac_avltree_t* _create_avl_tree()
{
	int i = 0;
	mac_avltree_t* tree = avl_tree_new( sizeof(int), sizeof(int), (AVLTreeCompareFunc) int_compare);

	for( i = 0; i < 10; ++i )
		avl_tree_insert( tree, &i, &i );

	return tree;
}

int test_avltree(TF* tf )
{
	int i;
#if 1
	mac_avltree_t* tree = _create_avl_tree();
#else
	mac_avltree_t* tree = avl_tree_new( sizeof(int), sizeof(int), (AVLTreeCompareFunc) int_compare);
	for( i = 0; i < 10; ++i )
		avl_tree_insert( tree, &i, &i );

#endif
	TF_TEST( tf, 10 == avl_tree_num_entries(tree) );

	int keys[] = {1,2,3};
	int vals[] = {1,2,3};

	for( i = 0; i < 3; ++i )
	{
		int key = keys[i];
		
		mac_avltree_node_t* node = avl_tree_lookup_node( tree, &key );

		TF_TEST( tf, NULL != node );

		if( node )
		{
			int* node_key = avl_tree_node_key( node );
			int* node_val = avl_tree_node_value( node );

			TF_TEST(tf, *node_key == keys[i] );
			TF_TEST(tf, *node_val == vals[i] );
		}
	}

	avl_tree_free( tree );
	return 0;
}

int main()
{
	TF tf;

	TF_init( &tf );

	if( 1 )
		test_list(&tf);

	if( 1 )
		test_dlist(&tf);

	if( 1 )
		test_queue(&tf);


	if( 1 )
		test_cvector( &tf );


	if( 1 )
		test_avltree( &tf );

	TF_finish( &tf );

	return 0;
}
