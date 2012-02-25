//#define LIBTVDB_STATIC

#include <stdio.h>
#include "tvdb.h"

/* You must copy tvdb_key_template.h to tvdb_key.h and edit */
/* See instructions in tvdb_key_template.h.                 */
#include "tvdb_key.h"

void print_mirrors(const tvdb_list_node_t *mirrors) {
   const tvdb_list_node_t *n;
   tvdb_mirror_t *m;

   if (!mirrors)
      return;

   printf("\nMirrors:\n");

   for (n = mirrors; n; n = n->next) {
      m = (tvdb_mirror_t *)n->data;
      printf("  id [%i], path [%s], type [%i]\n", m->id, m->path, m->type);
   }
}

void print_series(const tvdb_list_node_t *series) {
   const tvdb_list_node_t *n;
   tvdb_series_t *s;

   if (!series)
      return;

   printf("\nSeries:\n");

   for (n = series; n; n = n->next) {
      s = (tvdb_series_t *)n->data;
      printf("\n  id [%i], seriesid [%i], name [%s], overview: %s\n", s->id, s->series_id, s->name, s->overview);
   }
}

void print_banners(const tvdb_list_node_t *banners) {
   const tvdb_list_node_t *n;
   tvdb_banner_t *b;

   if (!banners)
      return;

   printf("\nBanners:\n");

   for (n = banners; n; n = n->next) {
      b = (tvdb_banner_t *)n->data;
      printf("  id [%i], path [%s], type [%s]\n", b->id, b->path, b->type);
   }
}
void show_result(const char *function, int result) {
   printf("[%-25s]  %s\n", tvdb_error_text(result), function);
}

int main() {
   int result;

   tvdb_list_node_t *mirrors;
   tvdb_buffer_t *mirrors_xml;

   tvdb_time_t time;
   tvdb_buffer_t *time_xml;

   tvdb_list_node_t *series;
   tvdb_buffer_t *series_xml;

   tvdb_list_node_t *banners;

   /* init libtvdb and get a handle */
   htvdb_t tvdb = tvdb_init(MY_API_KEY);

   /* get mirrors XML from TVDB and parse it */
   mirrors = 0;
   mirrors_xml = tvdb_alloc_buffer();
   result = tvdb_mirrors(tvdb, mirrors_xml);
   show_result("tvdb_mirrors", result);
   result = tvdb_parse_mirrors(mirrors_xml, 0, &mirrors);
   show_result("tvdb_parse_mirrors", result);
   print_mirrors(mirrors);
   tvdb_free_buffer(mirrors_xml);

   /* get server time XML from TVDB and parse it */
   time_xml = tvdb_alloc_buffer();
   result = tvdb_time(tvdb, time_xml);
   show_result("tvdb_time", result);
   result = tvdb_parse_time(time_xml, 0, &time);
   show_result("tvdb_parse_time", result);
   if (result == TVDB_OK) {
      printf("\nServer Time [%s]\n", time);
   }
   tvdb_free_buffer(time_xml);

   /* get series XML and parse it */
   series = 0;
   series_xml = tvdb_alloc_buffer();
   result = tvdb_series(tvdb, "dog", series_xml);
   show_result("tvdb_series", result);
   result = tvdb_parse_series(series_xml, 0, &series);
   show_result("tvdb_parse_series", result);
   print_series(series);
   tvdb_free_buffer(series_xml);

   /* get series info (episodes, etc.) for the first series found above */
   if (mirrors && series) {
      result = tvdb_series_info(tvdb, ((tvdb_mirror_t*)mirrors->data)->path, ((tvdb_series_t*)series->data)->id, "en", "series_info.zip");
      show_result("tvdb_series_info", result);
   }

   if (mirrors)
      tvdb_list_free(mirrors);

   if (series)
      tvdb_list_free(series);

   /* Temporary hack of a test for banner xml parsing.                       */
   /* Requires that the zip file from the previous test be manually unzipped */
   /* and banners.xml be copied to the build folder.                         */
   /* The whole test has to be run twice to make this work.                  */
   banners = 0;
   result = tvdb_parse_banners("banners.xml", &banners);
   show_result("tvdb_parse_banners", result);
   if (banners)
      print_banners(banners);

   if (tvdb > 0)
      tvdb_uninit(tvdb);
}
