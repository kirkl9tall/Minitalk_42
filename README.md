# Minitalk

Minitalk is a project developed as part of a C programming course to explore inter-process communication (IPC) using UNIX signals. The program consists of two parts: a **server** that waits for messages and a **client** that sends messages. The communication between the server and client is done by transmitting each character of the message as a binary representation using the `SIGUSR1` and `SIGUSR2` signals.

The server listens for these signals, decodes them into characters, and prints the message when it is fully received. On the client side, the message is converted into a sequence of bits, which are sent as signals to the server.

The project demonstrates the use of low-level system features in C, such as signal handling, process management, and binary data encoding/decoding, to establish simple but efficient communication between processes.

The goal of this project is to deepen the understanding of UNIX signals and the importance of signal handling in system-level programming.
