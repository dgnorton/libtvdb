#ifndef TVDB_H_INCLUDED
#define TVDB_H_INCLUDED

#include "tvdb_exports.h"
#include "tvdb_list.h"
#include "tvdb_results.h"
#include "tvdb_xml.h"
#include "tvdb_types.h"

TVDB_API htvdb_t tvdb_init(const char* key);
TVDB_API void tvdb_uninit(htvdb_t htvdb);
TVDB_API int tvdb_mirrors(htvdb_t htvdb, tvdb_buffer_t *buf);
TVDB_API int tvdb_time(htvdb_t htvdb, tvdb_buffer_t *buf);
TVDB_API int tvdb_series(htvdb_t htvdb, const char *name, tvdb_buffer_t *buf);
TVDB_API int tvdb_series_info(htvdb_t htvdb, const char *mirror, int series_id, const char *lang, const char *outfile);
TVDB_API int tvdb_banner(htvdb_t htvdb, const char *path, const char *outfile);
TVDB_API const char* tvdb_error_text(int err);
TVDB_API void tvdb_free(void *);

#endif /* TVDB_H_INCLUDED */
