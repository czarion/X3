*How to Use This Code:

Install SFML (Simple and Fast Multimedia Library)

Download SFML from its official website.

Follow the setup instructions for your compiler (e.g., GCC or Visual Studio).

Use a compiler like GCC or Visual Studio with SFML properly linked.

For Visual Studio, set up SFML in your project settings.

*Required Software:
SFML Library: Provides the graphics and animation functionality.
Code Editor: Visual Studio Code, Visual Studio, or any C++ IDE.
Compiler: GCC, Clang, or MSVC.

-------------------------------------------------------------------------------------

*The code is written in C++, and it uses the SFML (Simple and Fast Multimedia Library) for graphics and window rendering. SFML is a lightweight library that's commonly used for 2D game development, animations, and graphical applications.

*This program uses:

SFML/Graphics.hpp: For drawing shapes (circle, rectangle) and rendering graphics.
Mathematical functions: To handle object positions and radar sweep movement using trigonometry

*Steps for a Live Radar:

Integrating Sensors:
Provide sensor details (communication protocol, data format, and range).
Use libraries like SerialPort for C++ to read live data from sensors.
Replace generateObjects:
Replace simulated objects with data parsed from the sensor.
Plot their coordinates relative to the radar's position.

-------------------------------------------------------------------------------------

The C++ code is designed to integrate directly with sensors, allowing it to process live data from hardware like radar detectors, motion sensors, or any device capable of providing real-time coordinates or object detection data. It already includes placeholders (generateObjects) that can be replaced with data from sensors.
The C++ version uses SFML, a high-performance library for graphics and multimedia, which allows it to render a radar interface efficiently and process live updates with ease.

The provided C++ code can run on any platform that supports the SFML library and C++ compilers, such as, Windows: Use Visual Studio or MinGW.
Download SFML from SFML's official website and integrate it with your development environment.

*To integrate the code with your hardware setup:

The radar sensor must output its data in a binary file named sensor_data.bin or default name. Ensure the radar sensor sends data to a file or directly streams data through a serial interface. If it streams, you need additional code to read the stream and write it into the expected binary file format. 

*Each record in the binary file should contain:

float angle: Sweep angle in degrees.
float distance: Object distance (relative to the radar's scaling).