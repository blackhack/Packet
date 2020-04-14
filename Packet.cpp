#include "Packet.h"

Packet::Packet(int32_t opcode) : _opcode(opcode)
{
    AppendInt32(opcode);
}

Packet::Packet(uint8_t* data)
{
    uint8_t byte1 = data[0];
    uint8_t byte2 = data[1];
    uint16_t size = data[2];
    size |= (uint16_t)data[3] << 8;

    memcpy(_data, data, size);

    _opcode = ReadInt32();
}

Packet::Packet(Packet& packet) : _data_pointer(packet._data_pointer)
{
    memcpy(_data, packet._data, _data_pointer);
    _data_pointer = fixed_header_length;

    _opcode = ReadInt32();
}

void Packet::AppendUInt8(uint8_t value)
{
    for (int i = 0; i < 1; ++i)
        _data[_data_pointer + i] = (uint8_t)(value >> (8 * i));

    _data_pointer += 1;

    UpdateHeader();
}

void Packet::AppendUInt16(uint16_t value)
{
    for (int i = 0; i < 2; ++i)
        _data[_data_pointer + i] = (uint8_t)(value >> (8 * i));

    _data_pointer += 2;

    UpdateHeader();
}

void Packet::AppendUInt32(uint32_t value)
{
    for (int i = 0; i < 4; ++i)
        _data[_data_pointer + i] = (uint8_t)(value >> (8 * i));

    _data_pointer += 4;

    UpdateHeader();
}

void Packet::AppendUInt64(uint64_t value)
{
    for (int i = 0; i < 8; ++i)
        _data[_data_pointer + i] = (uint8_t)(value >> (8 * i));

    _data_pointer += 8;

    UpdateHeader();
}

void Packet::AppendInt8(int8_t value)
{
    for (int i = 0; i < 1; ++i)
        _data[_data_pointer + i] = (uint8_t)(value >> (8 * i));

    _data_pointer += 1;

    UpdateHeader();
}

void Packet::AppendInt16(int16_t value)
{
    for (int i = 0; i < 2; ++i)
        _data[_data_pointer + i] = (uint8_t)(value >> (8 * i));

    _data_pointer += 2;

    UpdateHeader();
}

void Packet::AppendInt32(int32_t value)
{
    for (int i = 0; i < 4; ++i)
        _data[_data_pointer + i] = (uint8_t)(value >> (8 * i));

    _data_pointer += 4;

    UpdateHeader();
}

void Packet::AppendInt64(int64_t value)
{
    for (int i = 0; i < 8; ++i)
        _data[_data_pointer + i] = (uint8_t)(value >> (8 * i));

    _data_pointer += 8;

    UpdateHeader();
}

void Packet::AppendFloat(float value)
{
    memcpy(_data + _data_pointer, &value, fixed_float_size);
    _data_pointer += fixed_float_size;
    UpdateHeader();
}

void Packet::AppendDouble(double value)
{
    memcpy(_data + _data_pointer, &value, fixed_double_size);
    _data_pointer += fixed_double_size;
    UpdateHeader();
}

void Packet::AppendString(const char* str)
{
    uint32_t strLength = static_cast<uint32_t>(strlen(str));
    AppendUInt32(strLength); // Store string length
    memcpy(_data + _data_pointer, str, strLength);
    _data_pointer += strLength;
    UpdateHeader();
}

uint8_t Packet::ReadUInt8()
{
    uint8_t value = 0;

    for (int i = 0; i < 1; ++i)
        value |= (uint8_t)_data[_data_pointer + i] << (8 * i);

    _data_pointer += 1;

    return value;
}

uint16_t Packet::ReadUInt16()
{
    uint16_t value = 0;

    for (int i = 0; i < 2; ++i)
        value |= (uint16_t)_data[_data_pointer + i] << (8 * i);

    _data_pointer += 2;

    return value;
}

uint32_t Packet::ReadUInt32()
{
    uint32_t value = 0;

    for (int i = 0; i < 4; ++i)
        value |= (uint32_t)_data[_data_pointer + i] << (8 * i);

    _data_pointer += 4;

    return value;
}

uint64_t Packet::ReadUInt64()
{
    uint64_t value = 0;

    for (int i = 0; i < 8; ++i)
        value |= (uint64_t)_data[_data_pointer + i] << (8 * i);

    _data_pointer += 8;

    return value;
}

int8_t Packet::ReadInt8()
{
    int8_t value = 0;

    for (int i = 0; i < 1; ++i)
        value |= (int8_t)_data[_data_pointer + i] << (8 * i);

    _data_pointer += 1;

    return value;
}

int16_t Packet::ReadInt16()
{
    int16_t value = 0;

    for (int i = 0; i < 2; ++i)
        value |= (int16_t)_data[_data_pointer + i] << (8 * i);

    _data_pointer += 2;

    return value;
}

int32_t Packet::ReadInt32()
{
    int32_t value = 0;

    for (int i = 0; i < 4; ++i)
        value |= (int32_t)_data[_data_pointer + i] << (8 * i);

    _data_pointer += 4;

    return value;
}

int64_t Packet::ReadInt64()
{
    int64_t value = 0;

    for (int i = 0; i < 8; ++i)
        value |= (int64_t)_data[_data_pointer + i] << (8 * i);

    _data_pointer += 8;

    return value;
}

float Packet::ReadFloat()
{
    float value;
    memcpy(&value, _data + _data_pointer, fixed_float_size);

    _data_pointer += fixed_float_size;

    return value;
}

double Packet::ReadDouble()
{
    double value;
    memcpy(&value, _data + _data_pointer, fixed_double_size);

    _data_pointer += fixed_double_size;

    return value;
}

char* Packet::ReadString()
{
    size_t strLength = static_cast<size_t>(ReadUInt32());

    char* newArray = new char[strLength + 1];
    memcpy(newArray, _data + _data_pointer, strLength);
    newArray[strLength] = '\0';

    _data_pointer += strLength;

    return newArray;
}

void Packet::UpdateHeader()
{
    _data[0] = byte_check_one;
    _data[1] = byte_check_two;
    _data[2] = (uint8_t)_data_pointer;
    _data[3] = (uint8_t)(_data_pointer >> 8);
}
