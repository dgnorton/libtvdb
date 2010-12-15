#include <libxml/parser.h>
#include "tvdb_types.h"
#include "tvdb_xml.h"
#include "tvdb_results.h"
#include "tvdb_types.h"

#ifdef __cplusplus
extern "C" {
#endif

TVDB_API int tvdb_parse_mirrors(const tvdb_buffer_t *xml, const char *url, tvdb_list_node_t **mirrors) {
   xmlDoc *doc;
   xmlNode *node, *elem;
   char *tmp;
   tvdb_mirror_t *mirror;
   int result;

   result = TVDB_E_PARSE_MIRRORS_XML;

   doc = xmlReadMemory(xml->memory, xml->size, url, 0, 0);
   node = xmlDocGetRootElement(doc);

   if (node->type == XML_ELEMENT_NODE && !xmlStrcmp(node->name, (const xmlChar *)"Mirrors")) {
      /* iterate Mirror nodes */
      for (node = node->children; node; node = node->next) {
         if (node->type == XML_ELEMENT_NODE && !xmlStrcmp(node->name, (const xmlChar *)"Mirror")) {
            mirror = tvdb_alloc_mirror();

            /* iterate child elements of each Mirror node */
            for (elem = node->children; elem; elem = elem->next) {
               if (elem->type == XML_ELEMENT_NODE) {
                  if (!xmlStrcmp(elem->name, (const xmlChar *)"id")) {
                     if ((tmp = xmlNodeGetContent(elem))) {
                        mirror->id = atoi(tmp);
                        xmlFree(tmp);
                     }
                  }
                  else if (!xmlStrcmp(elem->name, (const xmlChar *)"mirrorpath")) {
                     if ((tmp = xmlNodeGetContent(elem))) {
                        strcpy(mirror->path, tmp);
                        xmlFree(tmp);
                     }
                  }
                  else if (!xmlStrcmp(elem->name, (const xmlChar *)"typemask")) {
                     if ((tmp = xmlNodeGetContent(elem))) {
                        mirror->type = atoi(tmp);
                        xmlFree(tmp);
                     }
                  }
               }
            }

            tvdb_list_add(mirrors, mirror, sizeof(mirror));
         }
      }

      result = TVDB_OK;
   }

   return result;
}

TVDB_API int tvdb_parse_time(const tvdb_buffer_t *xml, const char *url, tvdb_time_t *server_time) {
   xmlDoc *doc;
   xmlNode *node, *elem;
   char *tmp;
   int len;
   int result;

   result = TVDB_E_PARSE_TIME_XML;

   doc = xmlReadMemory(xml->memory, xml->size, url, 0, 0);
   node = xmlDocGetRootElement(doc);

   if (node->type == XML_ELEMENT_NODE && !xmlStrcmp(node->name, (const xmlChar *)"Items")) {
      elem = node->children;

      while (elem && elem->type != XML_ELEMENT_NODE)
         elem = elem->next;

      if (elem && elem->type == XML_ELEMENT_NODE && !xmlStrcmp(elem->name, (const xmlChar *)"Time")) {
         if ((tmp = xmlNodeGetContent(elem))) {
            len = xmlStrlen(tmp);
            memcpy(*server_time, tmp, len);
            (*server_time)[len] = 0;
            xmlFree(tmp);
            result = TVDB_OK;
         }
      }
   }

   return result;
}

TVDB_API int tvdb_parse_series(const tvdb_buffer_t *xml, const char *url, tvdb_list_node_t **series) {
   xmlDoc *doc;
   xmlNode *node, *elem;
   char *tmp;
   tvdb_series_t *s;
   int result;

   result = TVDB_E_PARSE_SERIES_XML;

   doc = xmlReadMemory(xml->memory, xml->size, url, 0, 0);
   node = xmlDocGetRootElement(doc);

   if (node->type == XML_ELEMENT_NODE && !xmlStrcmp(node->name, (const xmlChar *)"Data")) {
      /* iterate Series nodes */
      for (node = node->children; node; node = node->next) {
         if (node->type == XML_ELEMENT_NODE && !xmlStrcmp(node->name, (const xmlChar *)"Series")) {
            s = tvdb_alloc_series();

            /* iterate child elements of each Series node */
            for (elem = node->children; elem; elem = elem->next) {
               if (elem->type == XML_ELEMENT_NODE) {
                  if (!xmlStrcmp(elem->name, (const xmlChar *)"id")) {
                     if ((tmp = xmlNodeGetContent(elem))) {
                        s->id = atoi(tmp);
                        xmlFree(tmp);
                     }
                  }
                  else if (!xmlStrcmp(elem->name, (const xmlChar *)"seriesid")) {
                     if ((tmp = xmlNodeGetContent(elem))) {
                        s->series_id = atoi(tmp);
                        xmlFree(tmp);
                     }
                  }
                  else if (!xmlStrcmp(elem->name, (const xmlChar *)"language")) {
                     if ((tmp = xmlNodeGetContent(elem))) {
                        strcpy(s->lang, tmp);
                        xmlFree(tmp);
                     }
                  }
                  else if (!xmlStrcmp(elem->name, (const xmlChar *)"SeriesName")) {
                     if ((tmp = xmlNodeGetContent(elem))) {
                        strcpy(s->name, tmp);
                        xmlFree(tmp);
                     }
                  }
                  else if (!xmlStrcmp(elem->name, (const xmlChar *)"banner")) {
                     if ((tmp = xmlNodeGetContent(elem))) {
                        strcpy(s->banner, tmp);
                        xmlFree(tmp);
                     }
                  }
                  else if (!xmlStrcmp(elem->name, (const xmlChar *)"Overview")) {
                     if ((tmp = xmlNodeGetContent(elem))) {
                        strcpy(s->overview, tmp);
                        xmlFree(tmp);
                     }
                  }
                  else if (!xmlStrcmp(elem->name, (const xmlChar *)"FirstAired")) {
                     if ((tmp = xmlNodeGetContent(elem))) {
                        strcpy(s->first_aired, tmp);
                        xmlFree(tmp);
                     }
                  }
                  else if (!xmlStrcmp(elem->name, (const xmlChar *)"IMDB_ID")) {
                     if ((tmp = xmlNodeGetContent(elem))) {
                        strcpy(s->imdb_id, tmp);
                        xmlFree(tmp);
                     }
                  }
                  else if (!xmlStrcmp(elem->name, (const xmlChar *)"zap2it_id")) {
                     if ((tmp = xmlNodeGetContent(elem))) {
                        strcpy(s->zap2it_id, tmp);
                        xmlFree(tmp);
                     }
                  }
               }
            }

            tvdb_list_add(series, s, sizeof(s));
         }
      }

      result = TVDB_OK;
   }

   return result;
}

#ifdef __cplusplus
}
#endif