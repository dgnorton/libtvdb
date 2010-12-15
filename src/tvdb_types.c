#include <stdlib.h>
#include <string.h>
#include "tvdb_types.h"

tvdb_mirror_t *tvdb_alloc_mirror() {
   tvdb_mirror_t *mirror;
   mirror = (tvdb_mirror_t *)malloc(sizeof(tvdb_mirror_t));
   memset(mirror, 0, sizeof(mirror));
   return mirror;
}

tvdb_series_t *tvdb_alloc_series() {
   tvdb_series_t *series;
   series = (tvdb_series_t *)malloc(sizeof(tvdb_series_t));
   memset(series, 0, sizeof(series));
   return series;
}

tvdb_buffer_t *tvdb_alloc_buffer() {
   tvdb_buffer_t *buf;
   buf = (tvdb_buffer_t *)malloc(sizeof(tvdb_series_t));
   buf->memory = (char*)malloc(1); 
   buf->size = 0;
   return buf;
}

void tvdb_free_buffer(tvdb_buffer_t *buf) {
   free(buf->memory);
   free(buf);
}