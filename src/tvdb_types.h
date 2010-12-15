#ifndef TVDB_TYPES_H_INCLUDED
#define TVDB_TYPES_H_INCLUDED

/** \brief tvdb context handle
 */
typedef long htvdb_t;

/** \brief Holds data received from TVDB
 */
typedef struct tvdb_buffer {
   char *memory;
   size_t size;
} tvdb_buffer_t;

/** \brief Allocates a buffer with default size
 */
tvdb_buffer_t *tvdb_alloc_buffer();

/** \brief Frees a buffer and any memory it has reserved
 */
void tvdb_free_buffer(tvdb_buffer_t *);

/** \brief Data for one mirror
 */
typedef struct tvdb_mirror {
   int   id;
   char  path[1024];
   int   type;
} tvdb_mirror_t;

/** \brief Allocates a mirror struct and zeros it
 */
tvdb_mirror_t *tvdb_alloc_mirror();

/** \brief Time from the TVDB server
 */
typedef char tvdb_time_t[16];

/** \brief Allocates a tvdb_time_t struct and zeros it
 */
tvdb_time_t *tvdb_alloc_time();

/** \brief Data for one series
 */
typedef struct tvdb_series {
   int   id;
   int   series_id;
   char  lang[16];
   char  name[128];
   char  banner[128];
   char  overview[2048];
   char  first_aired[16];
   char  imdb_id[16];
   char  zap2it_id[16];
} tvdb_series_t;

/** \brief Allocates a series struct and zeros it
 */
tvdb_series_t *tvdb_alloc_series();

#endif /* TVDB_TYPES_H_INCLUDED */
