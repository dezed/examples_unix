#include "stdio.h"

#include "mac/list.h"
#include "mac/dlist.h"
#include "mac/queue.h"

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

int main()
{
	TF tf;

	TF_init( &tf );

	test_list(&tf);

	test_dlist(&tf);

	test_queue(&tf);

	TF_finish( &tf );

	return 0;
}
