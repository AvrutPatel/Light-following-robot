# Light Seeking Robot
The objective of this project is to design and implement an autonomous light-seeking robot capable of navigating towards the brightest light source in its environment using light sensors and motor control.

## Project Objective

To design and build a light-seeking robot that autonomously detects and moves toward the strongest light source. This project introduces fundamental robotics concepts, including sensor integration, autonomous navigation, and motor control.

## Problem Statement

The primary goal is to create a robot that consistently follows a stationary light source with constant intensity. The robot uses sensors to detect light levels and adjusts its movements to navigate towards the source. The environment is assumed to be flat and free of obstacles.

## Long Description

The **Light Seeking Robot** is designed to emulate basic phototaxis behavior—moving towards a light source—by integrating light sensors (photoresistors), actuators, and control logic. The robot operates by reading light intensity data from sensors positioned on different parts of its body. Based on the comparative light levels detected by these sensors, the robot decides its movement, steering itself towards the brightest source.

This simple behavior mimics what some insects do naturally, offering an educational introduction to robotics and AI concepts like sensor fusion and real-time decision-making. The project also provides a hands-on learning experience, where you’ll encounter challenges like light sensor calibration, motor control synchronization, and dealing with variable environmental conditions.

While this version of the robot operates in a straightforward environment with few obstacles, future versions could integrate additional sensors (such as ultrasonic sensors) to handle more complex terrains. Enhancements like obstacle avoidance, dynamic light tracking, and machine learning-based adaptations could be incorporated to make the robot smarter.

By using light-seeking behavior as a base, this project paves the way for developing more advanced robotic systems capable of interacting with their surroundings and making decisions based on sensory input.

## Assumptions

- The light source is stationary with constant intensity.
- The environment is mostly flat and free of obstacles.
- Basic building materials such as chassis, wheels, motors, and light sensors are readily available.

## Components

### Actuators
- **Wheels**: Allow the robot to move and adjust its position.
- **Differential Steering (optional)**: Uses two independent motors to control direction.

### Sensors
- **Light Sensors (Photoresistors)**: Detect the intensity of light from different directions, allowing the robot to orient itself towards the brightest source.

## PEAS (Performance Measure, Environment, Actuators, Sensors)

- **Performance Measure**: The time taken to reach the light source (faster is better) or the distance traveled (shorter is better).
- **Environment**: A physical space with obstacles, varying light conditions, and a smooth surface.
- **Actuators**: Wheels and optional steering mechanism.
- **Sensors**: Light sensors to detect light intensity from multiple directions.

## Modes of Operation

### 1. **Chase Mode**
- The robot reads analog values from photoresistors and calculates the difference between the left and right sensors.
- If the difference is minimal and both sensors detect high light levels, the robot moves forward.
- If one sensor detects more light than the other, the robot adjusts by turning in that direction.
  
### 2. **Hiding Mode**
- In this mode, the robot attempts to move away from light sources, operating in reverse to the chase mode.
  
### 3. **Sleep Mode**
- When in sleep mode, the robot powers down its motors and enters a low-power state.

## Challenges

- **Sensor Limitations**: The directional sensitivity of the LDR (Light Dependent Resistor) sensors can affect how well the robot detects light sources.
- **Environmental Factors**: Varying light conditions and the terrain may impact performance.
- **Power Management**: Efficient use of battery power is crucial to maintain long-term functionality.

## Simulation and Future Exploration

The project also explores the potential of using machine learning to improve robot behavior. Future versions of the robot could learn to navigate complex environments with obstacles, adapt to changing light conditions, or build an internal map of its surroundings. The possibilities for incorporating learning algorithms are vast and could significantly improve the robot’s performance and adaptability in real-world applications.

## Learning Outcomes

- Basics of robotics and sensor integration.
- Practical experience with motor control and autonomous navigation.
- Understanding of real-time decision-making in robots.

---

### Group Members
- **Avrut Patel** (U22CS051)
- **Mitkumar Rohit** (U22CS070)
