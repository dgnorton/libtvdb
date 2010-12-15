//#define LIBTVDB_STATIC

#include <stdio.h>
#include "tvdb.h"

/* Change <MY_API_KEY> to the key provided to you by TVDB.com */
#define MY_API_KEY "<MY_API_KEY>"

void print_mirrors(const tvdb_list_node_t *mirrors) {
   const tvdb_list_node_t *n;
   tvdb_mirror_t *m;

   printf("\nMirrors:\n");

   for (n = mirrors; n; n = n->next) {
      m = (tvdb_mirror_t *)n->data;
      printf("  id [%i], path [%s], type [%i]\n", m->id, m->path, m->type);
   }
}

void print_series(const tvdb_list_node_t *series) {
   const tvdb_list_node_t *n;
   tvdb_series_t *s;

   printf("\nSeries:\n");

   for (n = series; n; n = n->next) {
      s = (tvdb_series_t *)n->data;
      printf("\n  id [%i], seriesid [%i], name [%s], overview: %s\n", s->id, s->series_id, s->name, s->overview);
   }
}

int main() {
   tvdb_list_node_t *mirrors;
   tvdb_buffer_t *mirrors_xml;

   tvdb_time_t time;
   tvdb_buffer_t *time_xml;

   tvdb_list_node_t *series;
   tvdb_buffer_t *series_xml;

   /* init libtvdb and get a handle */
   htvdb_t tvdb = tvdb_init(MY_API_KEY);

   /* get mirrors XML from TVDB and parse it */
   mirrors = 0;
   mirrors_xml = tvdb_alloc_buffer();
   tvdb_mirrors(tvdb, mirrors_xml);
   tvdb_parse_mirrors(mirrors_xml, 0, &mirrors);
   print_mirrors(mirrors);
   tvdb_free_buffer(mirrors_xml);

   /* get server time XML from TVDB and parse it */
   time_xml = tvdb_alloc_buffer();
   tvdb_time(tvdb, time_xml);
   tvdb_parse_time(time_xml, 0, &time);
   printf("\nServer Time [%s]\n", time);
   tvdb_free_buffer(time_xml);

   /* get series XML and parse it */
   series = 0;
   series_xml = tvdb_alloc_buffer();
   tvdb_series(tvdb, "xfiles", series_xml);
   tvdb_parse_series(series_xml, 0, &series);
   print_series(series);
   tvdb_free_buffer(series_xml);

   tvdb_uninit(tvdb);
}
