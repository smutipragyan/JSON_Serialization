#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include "data_model.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    JSON_OK = 0,
    JSON_ERR_NULL_INPUT,
    JSON_ERR_BUFFER_TOO_SMALL
} JsonError;

JsonError serialize_to_json(const MeterInputModel *input,
                            char *output_buffer,
                            int buffer_size,
                            int *required_size);

#ifdef __cplusplus
}
#endif

#endif
