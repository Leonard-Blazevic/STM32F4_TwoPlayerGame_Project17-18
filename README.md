# STM32F4_TwoPlayerGame_Project17-18
A 1v1 shooting game developed for multiple STM32F4 Discovery boards with wireless communication between them.

Pay attention to main.h - USER DEFINES section - when building project and loading flash memory of STM that is
connected via UART to ESP that works in STATION mode it necessary to use that define, when building project and loading flash memory of STM that is
connected via UART to ESP that works in AP mode it is necessary to comment out that line