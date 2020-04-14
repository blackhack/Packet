/*
    Packet
    Copyright(C) 2020 Blackhack

    This program is free software : you can redistribute itand /or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see < http://www.gnu.org/licenses/>.
*/

#ifndef Packet_h__
#define Packet_h__

// Arduino have its own definitions of the functions we need.
#ifdef ARDUINO
#include <Arduino.h>
#else
#include <cstring>
#include <cstdint>
#endif

class Packet
{
public:
    // Two first bytes in the header, those magic numbers are just a basic form of protocol identification.
    static const uint8_t byte_check_one = 0x41;
    static const uint8_t byte_check_two = 0xB5;

    static const size_t max_body_length = 1020;
    static const size_t fixed_header_length = 4;
    static const size_t max_data_length = max_body_length + fixed_header_length;
    static const size_t fixed_float_size = 4;
    static const size_t fixed_double_size = 8;

    Packet(int32_t opcode);
    Packet(uint8_t* data);
    Packet(Packet& packet);

    uint32_t GetOpcodeId() { return _opcode; }
    size_t GetSize() { return _data_pointer; }
    uint8_t* GetDataRaw() { return _data; }

    void AppendUInt8(uint8_t value);
    void AppendUInt16(uint16_t value);
    void AppendUInt32(uint32_t value);
    void AppendUInt64(uint64_t value);
    void AppendInt8(int8_t value);
    void AppendInt16(int16_t value);
    void AppendInt32(int32_t value);
    void AppendInt64(int64_t value);
    void AppendFloat(float value);
    void AppendDouble(double value);
    void AppendString(const char* str);

    uint8_t ReadUInt8();
    uint16_t ReadUInt16();
    uint32_t ReadUInt32();
    uint64_t ReadUInt64();
    int8_t ReadInt8();
    int16_t ReadInt16();
    int32_t ReadInt32();
    int64_t ReadInt64();
    float ReadFloat();
    double ReadDouble();
    char* ReadString();
private:
    void UpdateHeader();

private:
    int32_t _opcode;
    uint8_t _data[max_data_length] = { 0 };
    size_t _data_pointer = fixed_header_length;
};

#endif // Packet_h__
