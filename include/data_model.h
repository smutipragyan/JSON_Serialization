#ifndef DATA_MODEL_H
#define DATA_MODEL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char *gatewayId;
    const char *date;           // "YYYY-MM-DD"
    const char *deviceType;
    int interval_minutes;
    int total_readings;
} GatewayMetadata;

typedef struct {
    const char *timestamp;      // "YYYY-MM-DD HH:MM"
    const char *meter_datetime; // "YYYY-MM-DD HH:MM"
    float total_m3;
    const char *status;
} MeterDataPoint;

typedef struct {
    const char *media;
    const char *meter;
    const char *deviceId;
    const char *unit;

    MeterDataPoint *data;
    int data_count;
} DeviceReading;

typedef struct {
    GatewayMetadata metadata;

    DeviceReading *readings;
    int device_count;
} MeterInputModel;

#ifdef __cplusplus
}
#endif

#endif
