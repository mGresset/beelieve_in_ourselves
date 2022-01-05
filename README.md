# beelieve_in_ourselves

## Introduction
As part of the study project of the EI2I speciality at Polytech Sorbonne, and as students in the fourth grade, we have developed the Open Hive project. This project spanned the entire first semester and have globally taken 60 hours of framed time. We were supervised by M. Yann DOUZE and M. Sylvain VIATEUR.

The main goal of the project is to develop a device that can obtain phyisical measurements and make them available through an user interface over a web application.

This project is able to get values from the sensors, formatting the data and send it over a cloud platform called Ubidots thanks to Sigfox, a long-range and low power technology (LPWAN).

## Project Members
- BARKOUDEH Julian
- DOUZET Camille
- ESSAID Oumaima
- GRESSET Matthieu

## General Presentation
The goal of this project is to create a connected box equipped with sensors that send the data to a cloud platform. 

The box and the hive are been equipped with intelligent sensors in order to provide data on bee health and their productivity.\
The hive is placed on a scale that will provides weight which indicates the quantity of producted honey. It also helps us to detect whether the hive is stolen or not.\
Inside the hive, we have put three temperature sensors that allows the beekeeper to check if the hive heart is at 35°C.\
Morever, we placed one outside temperature and humidity sensor protected by a liitle box that we have printed.\
The Arduino card is powered by a battery which is charged by a solar panel.

Data are graphically accessible from a web interface on PC Desktop thanks to the Sigfox antenna. \
The system is also able to send alerts to your smartphone by mail when abnormal behaviour is detected such as low battery level.

[Photo ruche pendant la visite]

## Specifications
### "Bête à cornes" diagram
Functional analysis is an approach that involves researching and characterizing the functions offered by a product to meet the needs of its user.

The approach is generally conducted in project mode and can be used to create (design) or improve (redesign) a product.
Here the "Bête à cornes" diagram that we made for our project.

![bete_a_corne](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/bete_a_corne_r.PNG)

### Project Constraints
#### Energy 
The system is powered by a battery which is charged by a solar panel. Moreover, we have to make sure that the solar intensity is well enough during the day in order to make our system autonomous. In addition, we have an on/off button to control the whole system.
#### LPWAN Communication and Cloud Platform
We use the Sigfox technology in order to get the data from the sensors. We are limited to 140 messages per day for our device that is why we send data each 12 minutes.

We use Ubidots STEAM to access to the data dashboard and sends alerts via mail when abnormal behaviour is detected such as low battery level.

#### Sensors precision
The materiels' precision that were given to us from school were not the same as the ones mentioned in the specifications. Here is the solution to respond to the needs of the project that we have suggested:

The hive weighs around 30kg while the strain gauge's precision is 100g.\
The hive's heart temperature is approximately 35°C and the inside temperature sensor's precision is 0.5°C whereas in the specifications it was 0.1°C.\
We also have measured the outside temperature with a sensor's precision equals to 0.5°C and the outside humidity sensor's precision of 2%.\
On the battery level side, we provide to the users a precision of 1% for the battery state and 1% for the photoresistor which allows us to know the intensity light of the solar panel.

#### Budget
The sensors were given to us but we made some calculations of their costs to have an idea about the global project costs.
The materials budget is near 125 euros.

We also made the calculations for the worforce. We are a team of 4 persons and suppose that we are paid 10 euros per hour. The project duration is 60 hours.
So the workforce would have cost 2400 euros.

### APTE Diagram

The APTE (APplication aux Techniques d'Entreprise) diagram is used to define precisely the purpose and the objectives of the project in order to express the functions and the services provided to the users.

![APTE](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/pieuvre_r.PNG)

### WBS Diagram

The Work Breakdown Structure diagram is a structure and list of all tasks required for our project. The large tasks are broken into smaller components to separate the tasks between each member of the team. 

![WBS](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/WBS.drawio.png)

### GANTT Chart

Here is our GANTT Chart which gives a general view of the timeline and steps of the project that we followed.

![GANTT Diagram](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/Gantt_projet_corrected.png)
![GANTT legende](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/legende_gantt_r.png)

### Task Sharing

Please note that Matthieu was absent during one month from the end of September until the end of October due to some personal issue.

The first sessions of the project were dedicated to the study of the different components of the system and we have shared this task together.\
We also have to get familiar with Sigfox and Ubidots STEM dashboard during a practice session of four hours.\
Then we tested the different sensors, Julian took charge of the inside and outside temperature sensors while the rest of the team were occupied with the weight sensor.\
Julian was responsible of the arduino code and sending data via Sigfox.\
Oumaima was responsible of the Ubidots dashboard and set up the alerts.\
Camille handled the battery and solar panel with the code associed.\
Matthieu developped the PCB assembly and the conception of the outside temperature sensor support.\
Then, we all do our parts to assembly the whole system with the PCB such as the one wire for the inside sensors, the different welding of the cables etc...\
Camille and Oumaima have principally written the documentation of the project. At the same time, Julian and Matthieu were testing the final system.

## Project Realisation

### Sensors Presentation
Here's a general diagram that describes how the sensors are connected to the Arduino card.

![General Presentation](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/general_diagram_corrected.PNG)

### LPWAN Network choice


### Iot platform choice
### Microcontroller choice 
### Weight sensor choice
### Inside temperature sensor choice 
### Outside temperature and humidity sensor choice
### Electronical Schematics

Here's the electronical schematic prototype on the LABDEC :

![Electronical schematic LABDEC](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/schema_labdec_corrected.png)


In order to make the system robuster, we had add improvements to our project and replaced the LABDEC with a PCB card :

![PCB conception](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/PCB.png)

Here's a view of the inside box :

![PCB mis en place](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/pcb_misenplace.jpg)

## How to deploy our project
Guide d'utilisateur

## Some tests reports

Capture d'écran Ubidots et Sigfox

## Prospects for improvements

As a future work, we could have done the GPS option to protect the system and alert the bee-keepers in case of theft.

## Conclusion
## Source codes

We found some examples directly on the arduino application that helps to test the sensors.
We used the following libraries :
* [JULIAN A FAIIIIIIRE]
* 
## Bibliography

* Solar Panel : https://www.gotronic.fr/art-cellule-solaire-sol2w-18995.htm
* LiPo Rider Pro : https://www.gotronic.fr/art-carte-lipo-rider-pro-106990008-19050.htm
* Arduino MKR FOX 1200 : https://www.gotronic.fr/art-carte-arduino-mkr-fox-1200-abx00014-27323.htm
* Battery Li-Ion 3,7V 1050 mAh : https://www.gotronic.fr/art-accu-li-ion-3-7-v-1050-mah-5811.htm
* Inside temperature sensor DS18B20 : https://www.gotronic.fr/art-capteur-de-temperature-grove-101990019-23842.htm
* Weight sensor and strain gauge HX711 : https://www.gotronic.fr/art-amplificateur-hx711-grove-101020712-31346.htm
* Outside temperature and humidity sensors DHT22 : https://www.gotronic.fr/art-module-capteur-t-et-humidite-sen-dht22-31502.htm 
* Electronical schematic : https://fritzing.org/
* PCB design : https://www.autodesk.fr/
* GANTT project : https://www.ganttproject.biz/download
* Trello : https://trello.com/
