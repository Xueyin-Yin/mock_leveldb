#ifndef STORAGE_LEVELDB_INCLUDE_C_H_
#define STORAGE_LEVELDB_INCLUDE_C_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "leveldb/export.h"

typedef struct leveldb_t leveldb_t;
typedef struct leveldb_cache_t leveldb_cache_t;
typedef struct leveldb_comparator_t leveldb_comparator_t;
typedef struct leveldb_env_t leveldb_env_t;
typedef struct leveldb_filelock_t leveldb_filelock_t;
typedef struct leveldb_filterpolicy_t leveldb_filterpolicy_t;
typedef struct leveldb_iterator_t leveldb_iterator_t;
typedef struct leveldb_logger_t leveldb_logger_t;
typedef struct leveldb_options_t leveldb_options_t;
typedef struct leveldb_randomfile_t leveldb_randomfile_t;
typedef struct leveldb_readoptions_t leveldb_readoptions_t;
typedef struct leveldb_seqfile_t leveldb_seqfile_t;
typedef struct leveldb_snapshot_t leveldb_snapshot_t;
typedef struct leveldb_writablefile_t leveldb_writablefile_t;
typedef struct leveldb_writebatch_t leveldb_writebatch_t;
typedef struct leveldb_writeoptions_t leveldb_writeoptions_t;

LEVELDB_EXPORT leveldb_t* leveldb_open(const leveldb_options_t* options, 
                                        const char* name, char** errptr);

LEVELDB_EXPORT void leveldb_close(leveldb_t* db);
LEVELDB_EXPORT void leveldb_put(leveldb_t* db,
                                const leveldb_writeoptions_t* options,
                                const char* key, size_t keylen, const char* val,
                                size_t vallen, char** errptr);

LEVELDB_EXPORT void leveldb_delete(leveldb_t* db,
                                    const leveldb_writeoptions_t* options,
                                    const char* key, size_t keylen,
                                    char** errptr);

LEVELDB_EXPORT void leveldb_write(leveldb_t* db,
                                    const leveldb_writeoptions_t* options,
                                    const leveldb_writebatch_t* batch,
                                    char** errptr);

LEVELDB_EXPORT char* leveldb_get(leveldb_t* db,
                                const leveldb_readoptions_t* options,
                                const char* key, size_t keylen, size_t* vallen,
                                char** errptr);

LEVELDB_EXPORT leveldb_iterator_t* leveldb_create_iterator(leveldb_t* db, const leveldb_readoptions_t* options);

LEVELDB_EXPORT const leveldb_snapshot_t* leveldb_create_snapshot(leveldb_t *db);

LEVELDB_EXPORT void leveldb_release_snapshot(leveldb_t* db, const leveldb_snapshot_t* snapshot);

LEVELDB_EXPORT char* leveldb_property_value(leveldb_t* db, const char* propname);

LEVELDB_EXPORT void leveldb_approximate_sizes(leveldb_t* db, int num_ranges, const char* const* range_start_key,
                                                const size_t* range_start_key_len, const char* const* range_limit_key,
                                                const size_t* range_limit_key_len, uint64_t* sizes);

LEVELDB_EXPORT void leveldb_compact_range(leveldb_t* db, const char* start_key,
                                            size_t start_key_len,
                                            const char* limit_key,
                                            size_t limit_key_len);

LEVELDB_EXPORT void leveldb_destroy_db(const leveldb_options_t* options,
                                        const char* name, char** errptr);

LEVELDB_EXPORT void leveldb_repair_db(const leveldb_options_t* options,
                                        const char* name, char** errptr);

LEVELDB_EXPORT void leveldb_iter_destory(leveldb_iterator_t*);
LEVELDB_EXPORT uint8_t leveldb_iter_valid(const leveldb_iterator_t*);
LEVELDB_EXPORT void leveldb_iter_seek_to_first(leveldb_iterator_t*);
LEVELDB_EXPORT void leveldb_iter_seek_to_last(leveldb_iterator_t*);
LEVELDB_EXPORT void leveldb_iter_seek(leveldb_iterator_t*, const char* k, size_t klen);
LEVELDB_EXPORT void leveldb_iter_next(leveldb_iterator_t*);
LEVELDB_EXPORT void leveldb_iter_prev(leveldb_iterator_t*);
LEVELDB_EXPORT const char* leveldb_iter_key(const leveldb_iterator_t*, size_t* klen);
LEVELDB_EXPORT const char* leveldb_iter_value(const leveldb_iterator_t*, size_t* vlen);
LEVELDB_EXPORT void leveldb_iter_get_error(const leveldb_iterator_t*, char** errptr);

LEVELDB_EXPORT leveldb_writebatch_t* leveldb_writebatch_create(void);
}