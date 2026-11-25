# ESP32 FFT Chromatic Tuner

A chromatic tuner built on an ESP32 that listens through a MAX9814
microphone, runs an FFT to find the dominant frequency, and maps it to
the nearest musical note.

## Goals
- Sample audio from the MAX9814 using the ESP32 ADC
- Detect pitch with the arduinoFFT library
- Display the note name and how many cents sharp or flat

## Hardware
- ESP32 dev board (CP2102 USB)
- MAX9814 microphone amplifier module

## Software
- Arduino IDE with the Espressif ESP32 board package
- arduinoFFT library
