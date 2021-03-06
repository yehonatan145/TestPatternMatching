#ifndef CONF_H
#define CONF_H

#include "PatternsTree.h"
#include "mps.h"
#include "measure.h"

/* This configuration file should include other headers, while headers should not include that file
   (instead, use struct _Conf in other headers, and include this header in their source file) */

typedef struct _Conf {
	char** dictionary_files;
	size_t n_dictionary_files;
	char** stream_files;
	size_t n_stream_files;
	size_t max_pat_len;
	MpsInstance* mps_instances;
	InstanceStats* mps_instances_stats;
	MpsInstance reliable_mps_instance;
	size_t n_mps_instances;
	PatternsTree* patterns_tree;
	char* output_file_name;
} Conf;

#endif