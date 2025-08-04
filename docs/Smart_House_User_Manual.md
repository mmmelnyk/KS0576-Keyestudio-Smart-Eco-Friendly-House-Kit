# Smart Eco-Friendly House - User Manual

## Table of Contents
1. [Overview](#overview)
2. [Hardware Components](#hardware-components)
3. [Getting Started](#getting-started)
4. [Keypad Layout](#keypad-layout)
5. [Task Operations](#task-operations)
6. [Troubleshooting](#troubleshooting)
7. [Technical Specifications](#technical-specifications)

---

## Overview

The Smart Eco-Friendly House is an Arduino-based home automation system that monitors environmental conditions and controls various devices. The system features 5 different operational modes (Tasks 0-4) controlled via a 4x4 matrix keypad and displays information on a 16x2 LCD screen.

### Key Features
- 🏠 Automatic lighting control based on motion and light levels
- 🌈 RGB LED control with multiple colors
- 📊 Real-time environmental monitoring (temperature, humidity, light, UV)
- 💧 Soil moisture and water level monitoring
- ⚡ Smart pump control with cycle management
- 🔔 Audio feedback and alarms
- 🎵 Startup melody

---

## Hardware Components

| Component | Purpose | Pin Connection |
|-----------|---------|----------------|
| **4x4 Matrix Keypad** | User input control | Rows: 2,3,4,7 / Cols: 8,12,13,A2 |
| **16x2 LCD Display** | Information display | I2C: SDA, SCL |
| **PIR Motion Sensor** | Motion detection | Pin 10 |
| **Photoresistor** | Light level sensing | Pin A0 |
| **DHT11 Sensor** | Temperature & humidity | Pin 9 |
| **UV Sensor** | UV index measurement | Pin A3 |
| **Soil Moisture Sensor** | Soil humidity | Pin A6 |
| **Water Level Sensor** | Water level detection | Pin A7 |
| **Relay Module** | Pump control | Pin 5 |
| **Buzzer** | Audio alerts | Pin 6 |
| **NeoPixel RGB LEDs** | Lighting control | Pin 11 |

---

## Getting Started

### Initial Setup
1. **Power On**: Connect power to the Arduino
2. **Startup**: The system will initialize all components
3. **Ready**: LCD will display the current task mode
4. **Default Mode**: System starts in Task 0 (Motion & Light Control)

### Basic Navigation
- Press number keys **0-4** to switch between tasks
- Press **A, B, C** for color control in Task 1
- Press **\*** for pump control in Task 4
- Press **#** for system recovery if LCD freezes

---

## Keypad Layout

```
┌─────┬─────┬─────┬─────┐
│  1  │  2  │  3  │  A  │
├─────┼─────┼─────┼─────┤
│  4  │  5  │  6  │  B  │
├─────┼─────┼─────┼─────┤
│  7  │  8  │  9  │  C  │
├─────┼─────┼─────┼─────┤
│  *  │  0  │  #  │  D  │
└─────┴─────┴─────┴─────┘
```

### Key Functions
- **0-4**: Switch to respective task modes
- **A**: Red LED control (Task 1 only)
- **B**: Green LED control (Task 1 only)  
- **C**: Blue LED control (Task 1 only)
- **\***: Pump activation (Task 4 only)
- **#**: Emergency LCD recovery
- **5-9, D**: Reserved for future features

---

## Task Operations

### Task 0: Motion & Light Control
**Purpose**: Automatic lighting based on motion detection and ambient light

**LCD Display**: `Task 0:PIR&Light`

**Operation**:
- System continuously monitors motion (PIR) and light levels
- **Auto LED ON**: When motion detected AND light level ≤ 200
- **Auto LED OFF**: When no motion OR light level > 200
- LED color: White when activated

**Status Indicators**:
- Serial monitor shows: `[Light Level] [Motion: 0/1]`
- LED automatically changes based on conditions

---

### Task 1: Manual RGB LED Control
**Purpose**: Manual control of RGB LED colors

**LCD Display**: `Task 1: LED RGB`

**Controls**:
- **Press A**: Toggle Red LED
- **Press B**: Toggle Green LED  
- **Press C**: Toggle Blue LED

**Operation**:
- Only one color active at a time
- Pressing the same color key turns it OFF
- Pressing a different color switches to that color
- LEDs turn off when switching away from Task 1

---

### Task 2: Environmental Monitoring
**Purpose**: Real-time display of environmental sensor data

**LCD Display**: 
```
TEMP:##  H:##
ILL:###  UV:#
```

**Monitored Parameters**:
- **TEMP**: Temperature from DHT11 sensor (°C)
- **H**: Humidity from DHT11 sensor (%)
- **ILL**: Illumination level from photoresistor (0-1023)
- **UV**: UV index (0-11 scale)

**Update Rate**: Data refreshes every ~150ms

---

### Task 3: Plant Care Monitoring
**Purpose**: Monitor soil moisture and water levels for plant care

**LCD Display**:
```
SoilHum:###
WaterLevel:###
```

**Automated Actions**:
- **Low Water Alarm**: Buzzer sounds when water level ≤ 50
- **Auto Watering**: Pump activates when:
  - Soil humidity ≤ 100 AND
  - Water level ≥ 500

**Monitoring Values**:
- **SoilHum**: Soil moisture level (0-1023, lower = more moisture)
- **WaterLevel**: Water tank level (0-1023, higher = more water)

---

### Task 4: Pump Control
**Purpose**: Manual pump operation with cycle management

**LCD Display**: `Task 4: Pump`

**Operation**:
- **Press \***: Start 5-cycle pump sequence
- **Pump Status**: Shows `Pump: ON 1/5` through `Pump: ON 5/5`
- **Auto Stop**: Pump automatically stops after 5 cycles
- **Cycle Duration**: Each cycle runs for 400ms

**Safety Features**:
- Cannot restart pump while running
- Automatic LCD recovery after pump cycles
- Relay protection with proper on/off timing

---

## Troubleshooting

### Common Issues

#### LCD Shows Garbled Text or Freezes
**Solution**: Press **#** key for LCD recovery
- This reinitializes the LCD display
- All system states are preserved
- Usually resolves display corruption

#### Keypad Not Responding
**Possible Causes**:
- Check keypad connections (pins 2,3,4,7,8,12,13,A2)
- Ensure proper power supply
- Try LCD recovery with **#** key

#### Pump Not Working (Task 4)
**Check**:
- Relay connections (pin 5)
- Power supply to relay module
- Press **\*** only when in Task 4
- Wait for current cycle to complete

#### Sensors Reading Incorrect Values
**Solutions**:
- **DHT11**: Ensure proper 3.3V/5V power and pin 9 connection
- **Photoresistor**: Check analog pin A0 connection
- **UV Sensor**: Verify pin A3 connection and power
- **Soil/Water**: Check analog pins A6, A7

#### LEDs Not Working
**Check**:
- NeoPixel power and data connections (pin 11)
- Adequate power supply (NeoPixels need significant current)
- Try different colors in Task 1

### Emergency Procedures

#### Complete System Reset
1. Press **#** for LCD recovery
2. Switch to Task 0 for basic operation
3. If issues persist, power cycle the Arduino

#### Safe Pump Operation
- Never force pump restart during operation
- Allow 5-cycle completion before restarting
- Monitor water levels in Task 3 before using pump

---

## Technical Specifications

### Power Requirements
- **Arduino**: 5V via USB or external adapter
- **Total Current**: ~2A recommended for all components
- **NeoPixels**: High current draw when all LEDs active

### Sensor Ranges
- **Temperature**: -40°C to +80°C (DHT11)
- **Humidity**: 20% to 95% RH (DHT11)
- **Light Level**: 0-1023 (analog reading)
- **UV Index**: 0-11 scale
- **Soil Moisture**: 0-1023 (lower = wetter)
- **Water Level**: 0-1023 (higher = more water)

### Timing Specifications
- **LCD Update Rate**: 300-500ms depending on task
- **Sensor Reading**: 100-150ms intervals
- **Pump Cycle**: 400ms ON per cycle
- **Motion Detection**: Real-time monitoring
- **UV Filtering**: 16-sample average for accuracy

### Communication Protocols
- **LCD**: I2C (address 0x27)
- **DHT11**: Digital single-wire protocol
- **Keypad**: Digital matrix scanning
- **Sensors**: Analog readings (10-bit ADC)

---

## Quick Reference Card

### Essential Controls
| Key | Function |
|-----|----------|
| 0 | Motion & Light Control |
| 1 | RGB LED Manual Control |
| 2 | Environmental Monitoring |
| 3 | Plant Care Monitoring |
| 4 | Pump Control |
| A | Red LED (Task 1) |
| B | Green LED (Task 1) |
| C | Blue LED (Task 1) |
| * | Start Pump (Task 4) |
| # | Emergency LCD Recovery |

### Status Indicators
- **White LED**: Auto-lighting active (Task 0)
- **Colored LEDs**: Manual control (Task 1)
- **Buzzer**: Low water alarm (Task 3)
- **Serial Output**: Detailed sensor readings

---

**Document Version**: 1.0  
**Last Updated**: August 2025  
**Compatible Firmware**: Comprehensive_experiment.ino
