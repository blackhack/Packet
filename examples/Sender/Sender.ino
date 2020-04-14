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

void Send()
{
  Packet packet(123);
  packet.AppendFloat(365.456f);
  packet.AppendInt32(random(999999));
  packet.AppendString("Test string!");

  Serial.write(packet.GetDataRaw(), packet.GetSize());
}

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  // Sending the packet every 5 seconds.
  delay(5000);
  Send();
}