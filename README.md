# Packet
Packet management for network communications. Tested on Serial, WebSocket and Bluetooth RFCOMM

I'm not fully sure about endianness problems, at least I never have problems before when communicating between Arduino UNO, ESP32, Windows 10, Android and Linux (Fedora, Debian).

Test everything before doing something with it, specially Float and Double appends and reads. In some Arduino board like UNO and Leonardo, float and double are both 4 bytes, so AppendDouble and ReadDouble will not work.

When using strings, remember to store the readed string in a char* and never forget to delete[] it after use, otherwise you will get a memory leak.

For low ram boards like Arduino UNO, the default max_body_length = 1020 is too much, I recommend to lower that value to something like max_body_length = 251 Note:  max_data_length is always the sum of max_body_length plus 4 bytes of the header.

You can put it as low as max_body_length = 4, this allow you to send "empty" packets, with contain only the opcode id (This uses 4 bytes)
