# mBot_Controller
User Interface for the mBot project

# Idea
A software designed to take user input ( via a standard USB gamepad / controller ) and send it to the mBot robot.

# Requirements & Implementation
## Physical requirements
* mBot ( robot + serial-stick )
* USB gamepad / controller
* laptop / raspberry pi

## Software requirements
* [SFML](https://www.sfml-dev.org/) installed
* A C++ compiler
* A text editor
* Drivers for the USB stick, controller, etc...

## Implementation 
A main graphical window ( [sf::Window](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Window.php) ) takes input from the gamepad / controller ( [sf::Joystick](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Joystick.php) ) and the information is processed and sent trough the serial device ( using the specific protocol ), obtaining the desired effect : controlling the mBot robot remotely, with a gamepad.
For debugging purposes, the controller input is drawn in the main graphical window.

## Todo List
- [ ] Main C++ / SFML framework for taking input
- [ ] Debug system / Visual input representation
- [ ] Function for powering motors on / off
- [ ] Function for steering ( separately powering motors )
- [ ] Function for visual feedback ( LED's )

- [ ] Article for it @ www.gdrh.ro
- [ ] Demo video
- [ ] Pictures
- [ ] Project Schematic
- [ ] Function documentation / Code comments
