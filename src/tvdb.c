#define libtvdb_EXPORTS

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <libxml/parser.h>
#include "tvdb.h"
#include "tvdb_xml.h"

#define member_size(type, member) sizeof(((type *)0)->member)

typedef struct tvdb_context {
   char key[17];
   CURLcode curl_global;
   CURL *curl;
} tvdb_context_t;

#define URL_SZ 1024
typedef char URL[URL_SZ + 1];

TVDB_API htvdb_t tvdb_init(const char* key) {
   tvdb_context_t *tvdb;
   int key_len;

   xmlInitParser();
   LIBXML_TEST_VERSION

   key_len = strlen(key);

   if (key_len > member_size(tvdb_context_t, key) - 1)
      return TVDB_E_INVALID_KEY;

   tvdb = (tvdb_context_t *)malloc(sizeof(tvdb_context_t));
   
   if (!tvdb)
      return TVDB_E_MEMORY;
      
   memcpy(tvdb->key, key, key_len);
   tvdb->key[key_len] = 0;

   if ((tvdb->curl_global = curl_global_init(CURL_GLOBAL_ALL))) {
      free(tvdb);
      return TVDB_E_CURL_GLOBAL_INIT;
   }

   if ((tvdb->curl = curl_easy_init()) == 0) {
      curl_global_cleanup();
      free(tvdb);
      return TVDB_E_CURL_EASY_INIT;
   }

   return (htvdb_t)tvdb;
}

TVDB_API void tvdb_uninit(htvdb_t htvdb) {
   tvdb_context_t *tvdb;

   if (htvdb) {
      tvdb = (tvdb_context_t *)htvdb;

      if (tvdb->curl)
         curl_easy_cleanup(tvdb->curl);

      if (tvdb->curl_global == 0)
         curl_global_cleanup();

      xmlCleanupParser();

      free(tvdb);
   }
}

/*******************************************************************
 * stuff that probably needs to be in another file
 *******************************************************************/

size_t write_buf_cb(void *ptr, size_t size, size_t nmemb, void *data)
{
   size_t realsize = size *nmemb;
   tvdb_buffer_t *buf = (tvdb_buffer_t*)data;

   buf->memory = (char*)realloc(buf->memory, buf->size + realsize + 1);
   if (buf->memory == NULL) {
      /* out of memory! */ 
      printf("not enough memory (realloc returned NULL)\n");
      exit(EXIT_FAILURE);
   }

   memcpy(&(buf->memory[buf->size]), ptr, realsize);
   buf->size += realsize;
   buf->memory[buf->size] = 0;

   return realsize;
}

size_t write_file_cb(void *ptr, size_t size, size_t nmemb, void *stream) {
   return fwrite(ptr, size, nmemb, (FILE*)stream);;
}

CURLcode get_XML(CURL *curl, const char *url, tvdb_buffer_t *buf) {
   CURLcode cc;

   if ((cc = curl_easy_setopt(curl, CURLOPT_URL, url)) != CURLE_OK)
      return cc;

   if ((cc = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_buf_cb)) != CURLE_OK)
      return cc;

   if ((cc = curl_easy_setopt(curl, CURLOPT_WRITEDATA, buf)) != CURLE_OK)
      return cc;

   if ((cc = curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0")) != CURLE_OK)
      return cc;

   cc = curl_easy_perform(curl);

   return cc;
}

CURLcode get_file(CURL *curl, const char *url, FILE *stream) {
   CURLcode cc;

   if ((cc = curl_easy_setopt(curl, CURLOPT_URL, url)) != CURLE_OK)
      return cc;

   if ((cc = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_file_cb)) != CURLE_OK)
      return cc;

   if ((cc = curl_easy_setopt(curl, CURLOPT_WRITEDATA, stream)) != CURLE_OK)
      return cc;

   if ((cc = curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0")) != CURLE_OK)
      return cc;

   cc = curl_easy_perform(curl);

   return cc;
}

/*******************************************************************/

TVDB_API int tvdb_mirrors(htvdb_t htvdb, tvdb_buffer_t *buf)  {
   tvdb_context_t *tvdb;
   URL url;
   CURLcode cc;

   if (htvdb <= 0)
      return TVDB_E_INVALID_HANDLE;

   tvdb = (tvdb_context_t *)htvdb;

   sprintf(url, "http://www.thetvdb.com/api/%s/mirrors.xml", tvdb->key);

   if ((cc = get_XML(tvdb->curl, url, buf)) != CURLE_OK)
      return TVDB_E_CURL;

   return TVDB_OK;
}

TVDB_API int tvdb_time(htvdb_t htvdb, tvdb_buffer_t *buf) {
   tvdb_context_t *tvdb;
   URL url;
   CURLcode cc;

   if (htvdb <= 0)
      return TVDB_E_INVALID_HANDLE;

   tvdb = (tvdb_context_t *)htvdb;

   sprintf(url, "http://www.thetvdb.com/api/Updates.php?type=none");

   if ((cc = get_XML(tvdb->curl, url, buf)) != CURLE_OK)
      return TVDB_E_CURL;

   return TVDB_OK;
}

TVDB_API int tvdb_series(htvdb_t htvdb, const char *name, tvdb_buffer_t *buf) {
   tvdb_context_t *tvdb;
   URL url;
   CURLcode cc;

   if (htvdb <= 0)
      return TVDB_E_INVALID_HANDLE;

   tvdb = (tvdb_context_t *)htvdb;

   sprintf(url, "http://www.thetvdb.com/api/GetSeries.php?seriesname=%s", name);

   if ((cc = get_XML(tvdb->curl, url, buf)) != CURLE_OK)
      return TVDB_E_CURL;

   return TVDB_OK;
}

TVDB_API int tvdb_series_info(htvdb_t htvdb, const char *mirror, int series_id, const char *lang, const char *outfile) {
   tvdb_context_t *tvdb;
   URL url;
   CURLcode cc;
   FILE *stream;
   int result = TVDB_OK;

   if (htvdb <= 0)
      return TVDB_E_INVALID_HANDLE;

   stream = fopen(outfile, "wb");

   if (!stream)
      return TVDB_E_FILE_OPEN;

   tvdb = (tvdb_context_t *)htvdb;

   sprintf(url, "%s/api/%s/series/%i/all/%s.zip", mirror, tvdb->key, series_id, lang);

   if ((cc = get_file(tvdb->curl, url, stream)) != CURLE_OK)
      result = TVDB_E_CURL;

   fclose(stream);

   return result;
}

TVDB_API int tvdb_banner(htvdb_t htvdb, const char *path, const char *outfile) {

}

TVDB_API const char* tvdb_error_text(int err) {
   switch (err) {
      case TVDB_OK:
         return "TVDB_OK";
      case TVDB_E_ERROR:
         return "TVDB_E_ERROR";
      case TVDB_E_MEMORY:
         return "TVDB_E_MEMORY";
      case TVDB_E_INVALID_HANDLE:
         return "TVDB_E_INVALID_HANDLE";
      case TVDB_E_INVALID_KEY:
         return "TVDB_E_INVALID_KEY";
      case TVDB_E_FILE_OPEN:
         return "TVDB_E_FILE_OPEN";
      case TVDB_E_CURL_GLOBAL_INIT:
         return "TVDB_E_CURL_GLOBAL_INIT";
      case TVDB_E_CURL_EASY_INIT:
         return "TVDB_E_CURL_EASY_INIT";
      case TVDB_E_CURL:
         return "TVDB_E_CURL";
      case TVDB_E_PARSE_MIRRORS_XML:
         return "TVDB_E_PARSE_MIRRORS_XML";
      case TVDB_E_PARSE_TIME_XML:
         return "TVDB_E_PARSE_TIME_XML";
      case TVDB_E_PARSE_SERIES_XML:
         return "TVDB_E_PARSE_SERIES_XML";
      case TVDB_E_XML_DOC:
         return "TVDB_E_XML_DOC";
      case TVDB_E_XML_NODE:
         return "TVDB_E_XML_NODE";
      default:
         break;
   }
   return "UNRECOGNISED ERROR CODE";
}

TVDB_API void tvdb_free(void *mem) {
   free(mem);
}
