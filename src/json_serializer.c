#include "json_serializer.h"
#include <stdio.h>

static JsonError append(char *buf, int buf_size, int *used, const char *format, ...)
{
    if (*used >= buf_size)
        return JSON_ERR_BUFFER_TOO_SMALL;

    int remaining = buf_size - *used;

    va_list args;
    va_start(args, format);
    int written = vsnprintf(buf + *used, remaining, format, args);
    va_end(args);

    if (written < 0 || written >= remaining)
        return JSON_ERR_BUFFER_TOO_SMALL;

    *used += written;
    return JSON_OK;
}

JsonError serialize_to_json(const MeterInputModel *input,
                            char *output_buffer,
                            int buffer_size,
                            int *required_size)
{
    if (!input || !output_buffer)
        return JSON_ERR_NULL_INPUT;

    int used = 0;
    JsonError err;

    // Start JSON array
    err = append(output_buffer, buffer_size, &used, "[\n");
    if (err != JSON_OK) return err;

    // Gateway metadata
    err = append(output_buffer, buffer_size, &used,
        " {\n"
        "  \"gatewayId\": \"%s\",\n"
        "  \"date\": \"%s\",\n"
        "  \"deviceType\": \"%s\",\n"
        "  \"interval_minutes\": %d,\n"
        "  \"total_readings\": %d,\n"
        "  \"values\": {\n"
        "   \"device_count\": %d,\n"
        "   \"readings\": [\n",
        input->metadata.gatewayId,
        input->metadata.date,
        input->metadata.deviceType,
        input->metadata.interval_minutes,
        input->metadata.total_readings,
        input->device_count);

    if (err != JSON_OK) return err;

    // Device readings
    for (int i = 0; i < input->device_count; i++) {

        DeviceReading *dev = &input->readings[i];

        err = append(output_buffer, buffer_size, &used,
            "    {\n"
            "     \"media\": \"%s\",\n"
            "     \"meter\": \"%s\",\n"
            "     \"deviceId\": \"%s\",\n"
            "     \"unit\": \"%s\",\n"
            "     \"data\": [\n",
            dev->media,
            dev->meter,
            dev->deviceId,
            dev->unit);

        if (err != JSON_OK) return err;

        // Data points
        for (int j = 0; j < dev->data_count; j++) {

            MeterDataPoint *dp = &dev->data[j];

            err = append(output_buffer, buffer_size, &used,
                "      {\n"
                "       \"timestamp\": \"%s\",\n"
                "       \"meter_datetime\": \"%s\",\n"
                "       \"total_m3\": %.3f,\n"
                "       \"status\": \"%s\"\n"
                "      }",
                dp->timestamp,
                dp->meter_datetime,
                dp->total_m3,
                dp->status);

            if (err != JSON_OK) return err;

            if (j < dev->data_count - 1)
                append(output_buffer, buffer_size, &used, ",\n");
            else
                append(output_buffer, buffer_size, &used, "\n");
        }

        // Close data array and object
        err = append(output_buffer, buffer_size, &used,
            "     ]\n"
            "    }");

        if (err != JSON_OK) return err;

        if (i < input->device_count - 1)
            append(output_buffer, buffer_size, &used, ",\n");
        else
            append(output_buffer, buffer_size, &used, "\n");
    }

    // Close readings and values
    err = append(output_buffer, buffer_size, &used,
        "   ]\n"
        "  }\n"
        " }\n"
        "]\n");

    if (required_size)
        *required_size = used;

    return JSON_OK;
}

