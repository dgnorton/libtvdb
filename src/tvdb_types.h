#ifndef TVDB_TYPES_H_INCLUDED
#define TVDB_TYPES_H_INCLUDED

#define TVDB_TNY_STR_SZ 16
#define TVDB_SML_STR_SZ 128
#define TVDB_MED_STR_SZ 1024
#define TVDB_LRG_STR_SZ 4096

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
   char  path[TVDB_MED_STR_SZ + 1];
   int   type;
} tvdb_mirror_t;

/** \brief Allocates a mirror struct and zeros it
 */
tvdb_mirror_t *tvdb_alloc_mirror();

/** \brief Time from the TVDB server
 */
typedef char tvdb_time_t[TVDB_TNY_STR_SZ + 1];

/** \brief Allocates a tvdb_time_t struct and zeros it
 */
//tvdb_time_t *tvdb_alloc_time();

/** \brief Data for one series
 */
typedef struct tvdb_series {
   int   id;
   int   series_id;
   char  lang[TVDB_TNY_STR_SZ + 1];
   char  name[TVDB_SML_STR_SZ + 1];
   char  banner[TVDB_SML_STR_SZ + 1];
   char  overview[TVDB_LRG_STR_SZ + 1];
   char  first_aired[TVDB_TNY_STR_SZ + 1];
   char  imdb_id[TVDB_TNY_STR_SZ + 1];
   char  zap2it_id[TVDB_TNY_STR_SZ + 1];
} tvdb_series_t;

/** \brief Allocates a series struct and zeros it
 */
tvdb_series_t *tvdb_alloc_series();

typedef struct tvdb_banner {
   int id;
   char path[TVDB_MED_STR_SZ + 1];
   char type[TVDB_TNY_STR_SZ + 1];
   char type2[TVDB_TNY_STR_SZ + 1];
   char lang[TVDB_TNY_STR_SZ + 1];
   char rating[TVDB_TNY_STR_SZ + 1];
   int ratingCnt;
} tvdb_banner_t;

/** \brief Allocates a banner struct and zeros it
 */
tvdb_banner_t *tvdb_alloc_banner();

#endif /* TVDB_TYPES_H_INCLUDED */
