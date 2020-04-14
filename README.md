# Packet
Packet management for network communications. Tested on Serial, WebSocket and Bluetooth RFCOMM

I'm not fully sure about endianness problems, at least I never have problems before when communicating between Arduino UNO, ESP32, Windows 10, Android and Linux (Fedora, Debian).

Test everything before doing something with it, specially Float and Double appends and reads.

When using strings, remember to store the Readed string in a char* and never forget to delete[] it after used, otherwise you will get a memoryleak.
