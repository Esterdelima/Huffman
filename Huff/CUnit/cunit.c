#include "CUnit/Basic.h"
#include "data_structs.h"
#include <stdlib.h>
#include <stdbool.h>

void is_leaf()
{
	bool result;
	NODE* current = (NODE*) malloc(sizeof(NODE));

    if (current -> left == NULL && current -> right == NULL) result = true;
    else result = false;

	CU_ASSERT(current -> left == NULL);
	CU_ASSERT(current -> right == NULL);
	CU_ASSERT(result == true);
}

void dequeue()
{
	PRIORITY_QUEUE* queue = (PRIORITY_QUEUE*) malloc(sizeof(PRIORITY_QUEUE));
	NODE* new_node = (NODE*) malloc(sizeof(NODE));

	queue -> head = new_node;
	queue -> size = 10;

    if (queue -> head == NULL)
    {
        printf("QUEUE UNDERFLOW\n");
    }

    queue -> size -= 1;
    NODE* first_node = queue -> head;
    queue -> head = queue -> head -> next;
    first_node -> next = NULL;
    
    CU_ASSERT(queue -> size == 9);
	CU_ASSERT(queue -> head == NULL);
	CU_ASSERT(first_node -> next == NULL);

}

void create_hash()
{
    HASH* new_hash = (HASH*) malloc(sizeof(HASH));

    for (int i = 0; i < 256; i++)
    {
        new_hash -> array[i] = NULL;
    }

	CU_ASSERT(new_hash -> array[46] == NULL);

}

void create_node()
{
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    // parte do cast do caracter *void
    uchar* aux = (uchar*) malloc(sizeof(uchar)); // aloco para nao ser uma variavel temporaria na funcao.
    *aux = 'x';
    new_node -> caracter = aux; // representacao do caracter na ASCII.

    new_node -> priority = 0;
    new_node -> left = NULL;
    new_node -> right = NULL;
    new_node -> next = NULL;

	CU_ASSERT(*aux == 'x');
    CU_ASSERT(new_node -> priority == 0);
    CU_ASSERT(new_node -> left == NULL);
    CU_ASSERT(new_node -> right == NULL);
    CU_ASSERT(new_node -> next == NULL);

}

void create_priority_queue()
{
    PRIORITY_QUEUE* queue = (PRIORITY_QUEUE*) malloc(sizeof(PRIORITY_QUEUE));

    queue -> head = NULL; 
    queue -> size = 0;

    CU_ASSERT(queue -> head == NULL);
	CU_ASSERT(queue -> size == 0);
}

int main()
{
	// Initialize the CUnit test registry
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

   // Sets the basic run mode, CU_BRM_VERBOSE will show maximum output of run details
   // Other choices are: CU_BRM_SILENT and CU_BRM_NORMAL

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_pSuite pSuite = NULL, pSuite2 = NULL;

	// Add a suite to the registry

	pSuite = CU_add_suite("TEST", 0, 0);

	// Always check if add was successful

	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	// Add the test to the suite

	if (NULL == CU_add_test(pSuite, "test_queue - 1", create_priority_queue)) 
    {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite, "test_node  - 1", create_node)) 
    {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite, "test_hash  - 1", create_hash)) 
    {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite, "test_queue - 2", dequeue)) 
    {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite, "test_tree  - 1", is_leaf)) 
    {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	// Run the tests and show the run summary
	CU_basic_run_tests();
	return CU_get_error();
}