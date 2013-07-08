#include <stdlib.h>
#include <string.h>
#include "tvdb_types.h"

tvdb_mirror_t *tvdb_alloc_mirror() {
   tvdb_mirror_t *mirror;
   mirror = (tvdb_mirror_t *)calloc(sizeof(tvdb_mirror_t), 1);
   return mirror;
}

tvdb_series_t *tvdb_alloc_series() {
   tvdb_series_t *series;
   series = (tvdb_series_t *)calloc(sizeof(tvdb_series_t), 1);
   return series;
}

tvdb_buffer_t *tvdb_alloc_buffer() {
   tvdb_buffer_t *buf;
   buf = (tvdb_buffer_t *)calloc(sizeof(tvdb_buffer_t), 1);
   buf->memory = (char*)calloc(1, 1); 
   buf->size = 0;
   return buf;
}

void tvdb_free_buffer(tvdb_buffer_t *buf) {
   free(buf->memory);
   free(buf);
}

tvdb_banner_t *tvdb_alloc_banner() {
   tvdb_banner_t *banner;
   banner = (tvdb_banner_t *)calloc(sizeof(tvdb_banner_t), 1);
   return banner;
}
