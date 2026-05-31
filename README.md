# K-26 "Stratosphere" - Advanced ICBM Guidance System

## Project Overview
The **K-26** is a state-of-the-art software simulation of an Intercontinental Ballistic Missile (ICBM). Written in C, this project simulates the full lifecycle of a strategic launch vehicle, from lift-off to MIRV (Multiple Independent Re-entry Vehicle) deployment. It models advanced guidance, navigation, and control (GNC) logic, including hypersonic evasive maneuvers ("juggling") and multi-sensor fusion (Radar/Satellite/Gyroscopic).

**Status:** Simulation / Educational Prototype  
**Classification:** Unrestricted / Open Source Logic

---

## 1. K-26 Specifications (Technical Data)

This simulation models a "Satan II" class heavy ICBM with modernized avionics.

| Parameter | Specification |
| :--- | :--- |
| **Missile Name** | K-26 "Stratosphere" |
| **Class** | Intercontinental Ballistic Missile (ICBM) |
| **Total Range** | 18,000 km (Global Reach) |
| **Launch Weight** | ~208,100 kg (Simulated Fuel + Structure) |
| **Warhead Capacity** | 8,800 kg (MIRV Bus) |
| **Warhead Type** | Thermonuclear / Heavy Conventional (Simulated) |
| **Max Speed (Terminal)** | Mach 27+ (~9,200 m/s) |
| **Propulsion** | 3-Stage Liquid Fuel Rocket |
| **Guidance** | Inertial (INS), Stellar (Star Tracker), Satellite (GLONASS/GPS) |

### Advantages of the K-26 Design
1.  **Invulnerability:** Utilizes a "Juggling" trajectory (random path deviation) and polar launch capability to bypass standard radar grids.
2.  **MIRV Capability:** Can theoretically deploy up to 15 independent warheads, making interception by current ABM systems statistically impossible.
3.  **Hypersonic Glide:** Re-entry vehicles glide at hypersonic speeds, generating plasma sheaths that absorb radar waves.

---

## 2. IoT & Hardware Tools (Simulated)

While the K-26 runs on a standard Windows PC, it simulates the following high-end hardware components found in real aerospace engineering:

*   **Primary Flight Computer:** Simulated ARM Cortex-R52 equivalent.
*   **Inertial Measurement Unit (IMU):** Ring Laser Gyroscope (RLG) for "Juggling" maneuvers.
*   **Seeker/Sensor:** Active Phased Array Radar (Terminal Phase) + Electro-Optical Star Tracker (Space Phase).
*   **Actuators:** Thrust Vector Control (TVC) Nozzles.

---

## 3. System Requirements & Setup

### OS & Power Setup
This simulation is designed to run on standard developer hardware.

*   **Operating System:** Windows 10 / Windows 11 (PowerShell 5.1+).
*   **Architecture:** x64 (64-bit).
*   **RAM:** 4GB Minimum.
*   **Processor:** Intel i3 / AMD Ryzen 3 or better.

### Windows PowerShell Setup
To compile and run the K-26 project, the Windows environment must be configured for C development.

1.  **Install Compiler:**
    *   Install **TDM-GCC** (MinGW-w64).
    *   Ensure `gcc` is added to the System PATH.
2.  **Verify Setup:**
    *   Open PowerShell.
    *   Run: `gcc --version`.
    *   If a version string appears, the system is ready.

---

## 4. Cost Analysis

### Development Cost
*   **Software Cost:** $0.00 (Open Source C Language).
*   **Compiler:** Free (TDM-GCC).
*   **IDE:** Free (VS Code / Notepad++).

### Simulated Unit Cost (Per Missile)
*Estimated based on similar class ICBMs (e.g., RS-28 Sarmat)*
*   **Manufacturing:** ~$100 Million USD.
*   **Maintenance & Launch:** ~$5 Million USD per flight.

---

## 5. A-Z Guide: How to Use this in Building (Simulating) Missiles

This section explains how to utilize the **K-26 Codebase** to understand and design missile guidance logic.

**Note:** This is a software simulation for educational purposes. It does not interface with physical hardware.

#### Step A: Understanding the Architecture
The project is split into modular C files, representing real-world subsystems:
*   `types.h`: Defines physical constants and states (Physics Model).
*   `navigation.c`: Calculates coordinates and trajectory (Math Model).
*   `propulsion.c`: Manages fuel and thrust curves (Engine Model).
*   `guidance.c`: The "Brain" (Logic Model for threats and targeting).

#### Step B: Compilation (Building the Software)
1.  Open PowerShell in the project directory.
2.  Run the build script:
    ```powershell
    .\build.bat
    ```
3.  This links the navigation, propulsion, and guidance modules into a single executable (`missile_guidance.exe`).

#### Step C: Launch Simulation
1.  Run the executable.
2.  Input confirmation when prompted (Commander Authorization).
3.  The system calculates a ballistic trajectory to the target coordinates.

#### Step D: Monitoring Telemetry
The system outputs real-time data:
*   **Altitude:** Tracks the sub-orbital arc.
*   **Nav Status:** Switches between Radar (Active) and Stellar (Passive) when jammed.
*   **State Machine:** Watch the missile transition `BOOST` -> `SUBORBITAL` -> `REENTRY` -> `TERMINAL`.

#### Step E: Testing Evasive Capabilities
The code automatically simulates "Interceptor Clouds".
1.  The guidance system detects a threat.
2.  It switches to `STATE_EVASIVE`.
3.  It engages **Gyroscopic Sensing**, adding random vectors to the flight path ("Juggling").
4.  It boosts to Mach 24+ to outrun the threat.

---

## 6. Project Structure

```text
/K-26_Missile_System
├── bin/                # Compiled Executable
├── include/            # Header Files (Prototypes)
│   ├── types.h         # Physics & Warhead Definitions
│   ├── navigation.h    # Trajectory Logic
│   ├── propulsion.h    # Engine Logic
│   └── guidance.h      # Decision Making Logic
├── src/                # Source Files (C Code)
│   ├── main.c          # Mission Control
│   ├── navigation.c
│   ├── propulsion.c
│   └── guidance.c
├── build.bat           # Windows Compiler Script
└── README.md           # This File
```

## 7. Disclaimer
The K-26 project is a computer simulation written in the C programming language. It is intended for educational purposes to demonstrate software architecture, physics calculations, and state machine logic. It does not contain schematics for manufacturing weapons or interfaces for controlling real military hardware.

---

### Quick Start Command
```powershell
cd C:\MissileGuidanceSystem
.\build.bat
```
```</think>### Optional: Update the Code to match "K-26"

To make your program output match this README, open **`src\main.c`** and find these lines:

**Change:**
```c
printf(">>> ORDER RECEIVED: LAUNCH RS-28 SARMAT\n");
```
**To:**
```c
printf(">>> ORDER RECEIVED: LAUNCH K-26 STRATOSPHERE\n");
```

**Change:**
```c
printf(">>> LAUNCH SEQUENCE INITIATED: SATAN II <<<\n");
```
**To:**
```c
printf(">>> LAUNCH SEQUENCE INITIATED: K-26 ICBM <<<\n");
```

Re-run `.\build.bat` to see the updated name in action.