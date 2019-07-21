


# Arduino-Web-Interface
[![](https://img.shields.io/github/issues/SampaioLeal/Arduino-Web-Interface.svg)](https://github.com/SampaioLeal/Arduino-Web-Interface/issues) [![](https://img.shields.io/github/forks/SampaioLeal/Arduino-Web-Interface.svg)](https://github.com/SampaioLeal/Arduino-Web-Interface/network) [![](https://img.shields.io/github/stars/SampaioLeal/Arduino-Web-Interface.svg)](https://github.com/SampaioLeal/Arduino-Web-Interface/stargazers) [![](https://img.shields.io/github/release/SampaioLeal/Arduino-Web-Interface.svg)](https://github.com/SampaioLeal/Arduino-Web-Interface/releases) [![GitHub license](https://img.shields.io/github/license/SampaioLeal/Arduino-Web-Interface.svg)](https://github.com/SampaioLeal/Arduino-Web-Interface/blob/master/LICENSE)

WebInterface to control Arduino using Processing.
By default, the project is configured to control a 16X2 LCD and a ServoMotor.

## Project Files
### Arduino
  Folder: `resources/Arduino/interface`
### Processing
  Folder: `resources/Processing/interfaceWeb`

## Configuring to your enviroment

To use this project, you have to define some variables in the arduino and processing files.
1. In Processing file, there is a variable called `json`, change it to your enviroment URL.
2. In Arduino file, there is a defined variable called `SERVO` with the Digital PWM Port of the ServoMotor. Change it, if you want.
3. After, there is the LiquidCrystal setup, with the digital ports. Change it to adapt to your enviroment.
