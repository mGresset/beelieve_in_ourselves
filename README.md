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

### Structural Diagram
### APTE Diagram

![APTE](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/pieuvre.PNG)

### WBS Diagram


![WBS](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/WBS.drawio.png)
### GANTT Chart

Here is our GANTT Chart which gives a general

![GANTT Diagram](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/Gantt_projet_corrected.png)
![GANTT legende](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/legende_gantt.png)

### Task Sharing

## Project Realisation

### Sensors Presentation

![General Presentation](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/general_diagram_corrected.PNG)

### LPWAN Network choice
### Iot platform choice
### Microcontroller choice 
### Weight sensor choice
### Inside temperature sensor choice 
### Outside temperature and humidity sensor choice
### Electronical Schematic

## Prospects for improvements
## Conclusion
## Source codes
## Bibliography
