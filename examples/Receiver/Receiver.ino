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

#include <Packet.h>

void setup()
{
    Serial.begin(115200);
}

uint8_t* Receive()
{
	// In low memory boards like Arduino UNO, change this for something like 255
	// also change max_body_length to 251 in Packet.h, otherwise the board will run out of memory and crash
	// For more information see README.md
    static uint8_t buffer[1024];
    static bool waiting_header = true;

    if (int size = Serial.available())
    {
        if (waiting_header && size >= Packet::fixed_header_length)
        {
            Serial.readBytes(buffer, Packet::fixed_header_length);

            // Error, data is not part of the Packet protocol
            if (buffer[0] != Packet::byte_check_one || buffer[1] != Packet::byte_check_two)
                return nullptr;

            size -= Packet::fixed_header_length;
            waiting_header = false;
        }

        if (!waiting_header)
        {
            uint16_t data_size = buffer[2];
            data_size |= (uint16_t)buffer[3] << 8;

            if (size < data_size - Packet::fixed_header_length)
                return nullptr;

            Serial.readBytes(buffer + Packet::fixed_header_length, data_size - Packet::fixed_header_length);

            waiting_header = true;
            
            return buffer;
        }
    }

    return nullptr;
}

void loop()
{
    if (uint8_t* data = Receive())
    {
        // This copies the contents of data pointer before it changes, so no problem using this pointer.
        Packet packet(data);

        Serial.print("Opcode ID: ");
        Serial.println(packet.GetOpcodeId());
        Serial.print("Float: "); // In some Arduino boards like UNO and Leonardo, Float and Double are both 4 bytes, so ReadDouble and AppendDouble will not work.
        Serial.println(packet.ReadFloat(), 3); // in this case you need to use always ReadFloat and AppendFloat
        Serial.print("Random Int: ");
        Serial.println(packet.ReadInt32());

        char* str = packet.ReadString();
        Serial.print("String: ");
        Serial.println(str);
        delete[] str; // DONT FORGET to delete[] after using ReadString!!
    }
}
