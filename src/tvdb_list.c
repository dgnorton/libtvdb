#define libtvdb_EXPORTS

#include <stdlib.h>
#include "tvdb_list.h"

TVDB_API tvdb_list_node_t *tvdb_list_add(tvdb_list_node_t **p, void *data, size_t len) {
   tvdb_list_node_t *n;

   if (p == 0)
      return 0;

   n = (tvdb_list_node_t *)malloc(sizeof(tvdb_list_node_t));

   if (n == 0)
      return 0;

   n->next = *p;
   *p = n;
   n->data = data;
   n->size = len;

   return *p;
}

TVDB_API void tvdb_list_remove(tvdb_list_node_t **p) {
   if (p != 0 && *p != 0) {
      tvdb_list_node_t *n = *p;
      *p = (*p)->next;
      free(n);
   }
}

TVDB_API tvdb_list_node_t **tvdb_list_find(tvdb_list_node_t **n, tvdb_list_node_t *data, cmpfn_t compare) {
   if (n == 0)
      return 0;

   while (*n != 0) {
      if (compare(data, *n) == 0)
         return n;
      n = &(*n)->next;
   }

   return 0;
}

TVDB_API tvdb_list_node_t *tvdb_list_new() {
   tvdb_list_node_t *node;
   node = (tvdb_list_node_t *)malloc(sizeof(tvdb_list_node_t));
   node->next = 0;
   node->data = 0;
   node->size = 0;

   return node;
}

TVDB_API void tvdb_list_free(tvdb_list_node_t *node) {
   tvdb_list_node_t *tmp;

   while (node) {
      tmp = node->next;
      if (node->data)
         free(node->data);
      free(node);
      node = tmp;
   }
}
