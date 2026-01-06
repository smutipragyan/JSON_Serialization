#include "data_model.h"
#include "json_serializer.h"
#include <stdio.h>

int main(void)
{
    MeterDataPoint dp1 = {
        .timestamp = "1970-01-01 00:00",
        .meter_datetime = "1970-01-01 00:00",
        .total_m3 = 107.752,
        .status = "OK"
    };

    DeviceReading dev1 = {
        .media = "water",
        .meter = "waterstarm",
        .deviceId = "stromleser_50898527",
        .unit = "m3",
        .data = &dp1,
        .data_count = 1
    };

    MeterInputModel model = {
        .metadata = {
            .gatewayId = "gateway_1234",
            .date = "1970-01-01",
            .deviceType = "stromleser",
            .interval_minutes = 15,
            .total_readings = 1
        },
        .readings = &dev1,
        .device_count = 1
    };

    char buffer[1024];
    int required_size;

    JsonError err = serialize_to_json(&model,
                                      buffer,
                                      sizeof(buffer),
                                      &required_size);

    if (err == JSON_OK) {
        printf("Generated JSON (%d bytes):\n%s",
               required_size,
               buffer);
    } else {
        printf("Error serializing JSON\n");
    }

    return 0;
}
