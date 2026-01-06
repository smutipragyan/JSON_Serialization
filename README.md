# Embedded JSON Serialization Library

## Assignment Goal

This project implements a software library that serializes structured
meter measurement data into a fixed predefined JSON format.

The project models the realistic firmware pipeline:

Meter Data → Internal C Structures → JSON Serialization → Gateway Interface

w-MBus communication, encryption, OMS protocol, or real meter hardware
interaction are explicitly out of scope.

## Platform & Language

Platform: STM32CubeIDE  
Language: C

### Justification

STM32CubeIDE is chosen because:

- It matches the preferred target platform of the assignment
- STM32 MCUs are typical in industrial IoT gateways
- The C language allows full control over memory and buffers
- No third-party dependencies are required

## Library API

The library provides one main function:

serialize_to_json(input_data, output_buffer, buffer_size)

This API is:

- Transport agnostic
- Uses caller provided output buffer
- Prevents buffer overflows
- Returns detailed error codes

  Key characteristics of the API:

- Completely transport independent
- Operates only on internal data models
- Writes JSON into a caller-provided buffer
- Performs strict bounds checking
- Returns clear and simple error codes

## Data Model Design

Internal data structures are defined in:

include/data_model.h

The model consists of:

- GatewayMetadata structure for gateway level information
- DeviceReading structure for each meter device
- MeterDataPoint structure for timestamped values
- MeterInputModel as root container

## JSON Format

The library generates exactly the mandatory JSON structure
as required in the assignment with fixed field names
and numeric types.

## Example Output

An example JSON output produced by the demo application
is shown in the examples folder.

## Design Decisions

- JSON is built manually using snprintf()
- Caller controls memory
- No dynamic memory allocation inside library
- Strict buffer size tracking
- Fixed predefined format only

