#ifndef TVDB_LIST_H_INCLUDED
#define TVDB_LIST_H_INCLUDED

#include <string.h>
#include "tvdb_exports.h"

typedef struct tvdb_list_node {
   struct tvdb_list_node *next;
   void *data;
   size_t size;
} tvdb_list_node_t;

typedef int (*cmpfn_t)(tvdb_list_node_t *a, tvdb_list_node_t *b);

TVDB_API tvdb_list_node_t *tvdb_list_add(tvdb_list_node_t **p, void *data, size_t len);
TVDB_API void tvdb_list_remove(tvdb_list_node_t **n);
TVDB_API tvdb_list_node_t **tvdb_list_find(tvdb_list_node_t **n, tvdb_list_node_t *data, cmpfn_t compare);
TVDB_API tvdb_list_node_t *tvdb_list_new();
TVDB_API void tvdb_list_free(tvdb_list_node_t *node);

#endif /* TVDB_LIST_H_INCLUDED */
