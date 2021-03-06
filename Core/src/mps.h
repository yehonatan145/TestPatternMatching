#ifndef MPS_H
#define MPS_H

/******************************************************************************
*		INCLUDES
******************************************************************************/


#include "PatternsTree.h"


/******************************************************************************
*		DEFINITIONS
******************************************************************************/


struct _Conf;

// Multi-Pattern Search Algorithms
enum {
	MPS_AC = 0,   // Multi-Pattern Aho-Corasick
	MPS_LMAC,     // Multi-Pattern Low-Memory Aho-Corasick
	MPS_BG,       // Multi-Pattern Brausler-Galil
	MPS_SIZE
};

/**
* struct for holding an algorithm for multi-pattern search (hold its functions)
*
* All multi-pattern search algorithm should have this interface:
*
* 1. creating the data object (of type void*) using "create" function
*   
* 2. adding patterns to the data object using "add_pattern". note that each given pattern
*    have id (of type pattern_id_t) so that whoever call the algorithm can know what pattern
*    have a match. assume the id type pattern_id_t is of primitive type (e.g. int/long/pointer etc.)
*    so it can be compared using '==' and copied with '='
* 
* 3. compiling the data object when done adding patterns using "compile"
*
* 4. read the next character from the stream and return the id of the LONGEST pattern that
*    had a match using "read char" (from longest patterns matches, we can get the other patterns)
*
* 5. get the total memory that the object uses (not include memory that was freed before compilation)
*    using "total_mem" (this function should be used on the object only after compilation).
*
* 6. reset the state of the object to the initial state using "reset".
*    this function can be used only after compilation, and should put the object in
*    a state in which it is like the object was just compiled (no character was already seen)
* 
* 7. free the data object using "free" (only used after compilation)
*
* example:
*
*   MpsElem mps; // initialized to some algorithm
*   void* obj = mps->create();
*   mps->add_pattern(obj, "first pattern", 13, some_id);
*   mps->add_pattern(obj, "some other pattern", 18, other_id);
*   mps->compile();
*   pattern_id_t match;
*   match = mps->read_char(obj, 'S');
*   match = mps->read_char(obj, 't');
*   match = mps->read_char(obj, 'r');
*   mps->reset(obj);
*   match = mps->read_char(obj, 'e');
*   match = mps->read_char(obj, 'a');
*   match = mps->read_char(obj, 'm');
*   printf("total memory used: %lu\n", mps->total_mem(obj));
*   mps->free(obj);
*/
typedef struct {
	char* name;
	void* (*create)(void);
	void (*add_pattern)(void*, char*, size_t, pattern_id_t);
	void (*compile)(void*);
	pattern_id_t (*read_char)(void*, char);
	size_t (*total_mem)(void*);
	void (*reset)(void*);
	void (*free)(void*);
} MpsElem;

/**
* mps instance.
*
* In the configuration struct there is a list of mps instances, and on them we do the tests.
* note that there can be more than one instance per algorithm, or algorithms without instances.
* (the init_mps function is currently responsible for creating the instances according to the algorithms)
*/
typedef struct {
	void *obj;
	int   algo;
} MpsInstance;

extern MpsElem mps_table[MPS_SIZE]; // definition in .c file


/******************************************************************************
*		API FUNCTIONS
******************************************************************************/


void mps_table_setup();
void init_mps(struct _Conf* conf);


#endif /* MPS_H */