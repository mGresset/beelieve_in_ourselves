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

![Photo ruche pendant la visite](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/projet_deploye.png)

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

![General Presentation](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/general_schema.PNG)

### LPWAN Network choice

In order to share the data with the beekeepers via a dashboards, we have decided to use LPWAN Sigfox; Low Power Wide Area Network.
Low Power because its consumption is between 15 and 40mA during few seconds of the communication and only few µA while sleep mode.

![Sigfox](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/Sigfox_logo.jpg)

### Iot platform choice
![Ubidots](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/ubidots_logo.jpg)

### Microcontroller choice 
![Microcontroller](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/photo_mkrfox1.PNG)

### Weight sensor choice

To measure the weight of the hive, we used a strain gauge and a load cell.\
A load cell is an instrument that helps to determine the size of a load (either a force or weight) and converts the force into measurable electrical output.\
A load cell consists of a metal core and a set of electrical resistances that transform when a force is applied to it. But after the force is removed, it returns to its original state. \
To use a load cell, we have calibrate it first to get your correct weight using a microcontroller or microprocessor.

The HX711 strain gauge is a precision 24-bit analog-to-digital converter (ADC) that is designed for weighing scales and industrial control applications to interface directly with a Wheatstone bridge sensor.

![Weight sensor](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/photo_capteur_poids1.PNG)

This sensor communicates with an Arduino microcontroller via a two-pin digital interface.\
The power supply of the strain gauge is possible from 2.6 to 5,5 Vcc.\
This sensor allows us to read the resistance changes of the weight sensor, which will give us precise measurements after calibration.

### Inside temperature sensor choice 

This waterproof temperature sensor is based on the DS18B20 circuit with a measurement range of -55°C to +125°C.\
It digitally returns a 12-bit temperature in degrees Celsius. 

This type of sensor has the advantage of having a cylindrical shape with a small radius, which makes it possible to put several of them in a hive without having too much of an impact on the living environment of the bees. 

![Inside temperature sensor](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/photo_inside_temp1.PNG)

It is also possible to connect several at the same time using a One-Wires system. \
Indeed, each sensor has a unique 64-bit address, which reduces the cables between the card and the hive. 

It allows temperature measurement with an accuracy of 0.5°C and is powered between 3Vdc and 5Vdc. \
Thus it makes it possible to meet the constraints of the specifications on all points.

### Outside temperature and humidity sensor choice

This sensor measures ambient air humidity and temperature with its capacitive humidity probe and thermistor and displays a digital signal output. \
It allows temperature measurement between -40 and 80°C with an accuracy of 0.5°C. 
Regarding humidity, the sensor returns a value between 0 and 100% with an accuracy of 2% humidity in the air. 

The DHT22 is powered between 3.3 and 5Vdc and has the advantage of having low current consumption. \
It therefore perfectly meets the specifications of the project concerning the measurement of temperature and humidity outside.\
Moreover, it is one of the most used temperature sensors in different projects and there is a lot of documentation on it available. 

![Outside temperature and humidity sensor](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/photo_dht1.PNG)

It is water resistant so it can be placed outdoors. \
It is preferable, in order to improve this tightness, to manufacture a support which makes it possible to protect the sensor from the rain.

![Outside temperature and humidity sensor](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/modelisation_dht.png)

### Electronical Schematics

Here's the electronical schematic prototype on the LABDEC :

![Electronical schematic LABDEC](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/schema_labdec_corrected.png)


In order to make the system more robust, we had to add improvements to our project and replace the LABDEC with a PCB card :

![PCB conception](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/PCB.png)

Here's a view of the inside box :

![PCB mis en place](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/pcb_misenplace.jpg)

## How to deploy our project
Guide d'utilisateur

## Some tests reports

Capture d'écran Ubidots et Sigfox

Firstly, we will go through the test process of each element and the codes used. Secondly, we will explain the data collected form the test realized in the final environment over a week. \
In order to minimize the problems in our system, we have tested each sensor separately.\
Using the example codes provided by the sensor’s library, we have firstly verified if the sensor working normally and giving reasonable readout.\
This method helped us to establish an idea on what code elements are needed in order to retrieve and send the data from each sensor. 

### DHT

Our first test was done on the DHT sensor using the “DHTtester” code provided by its library. \
The readout of the sensor was successfully retrieved after figuring out how to connect it to our Sigfox module. \
This test was done in the first “TP” session, where we used a simple test code provided by the Sigfox library in order to send the DHT readout to Sigfox Backend server. 

We were able to conclude through the test the necessary elements to implement to initiate the connection with the Sigfox server, in addition to the command lines that allow us to send a data structure containing multiple readouts at a time. 

### OneWire

The test of the OneWire sensors followed the same method, and had similar results as the DHT sensor.\
Nevertheless, we had to do an additional test to the OneWire sensors in order to connect the 3 of them on a single pin. \
To do so, we used a specific section of the “DS18x20_Temperature” to retrieve the addresses of each sensor, and store them in 3 constants in our final code.  

### HX711

Multiple tests were done to ensure that all the aspects of the sensor’s readout comply with our specifications.\
After doing some online search, we have found an example code that allows to calibrate the sensor. \
We have put a known on the sensor and adjust the calibration factor to obtain a precise readout. \
The code provides also the Zero calibration factor, which allows the sensor to have readouts even if there is a weight already on the sensor while turning it on. \
After these tests we implemented the factors in constants in our code. 

### Battery and Photodiode

The code used to retrieve the data from the battery and the photodiode were fairly simple, however some tests were done in order to send a “usable” information to Sigfox server.\
Indeed, the data retrieved is simply the analog readout from the AD converter, so we had to treat this data to represent it in a value between 0 and 100. 

Based on the battery datasheet, we have used an external voltage source to simulate the battery input with the maximum and minimum voltage. \
This simulation allowed us to determine the mathematical formula to use in order to convert the readout to a 0 to 100 scale. 

We have also used the photodiode datasheet to determine its theoretical maximum and minimum voltage outputs.\
Although we had to do an experience in a “realistic environment” by exposing the photodiode to high luminist flash, and isolating the photodiode to simulate the day and night conditions. \
We have established the formula according to the results retrieved form this experience. 

### Our Week experiment  
![image](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/sigfox_trame.png)

The screen shot above shows the data received in the Sigfox server containing the data from all the sensors. \
In order to have the precision mentioned for each sensor above, we have multiplied the redouts of all the temperature sensors by 2 to have a precision of +-0.5°.\
To have a +- 0.1 Kg precision for the weight sensor we have multiplied the redout by 100. 

![image](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/ubidots1.jpg)

The experience that took place over the last week represented a perfect test to verify that our system will be functional in all conditions.\
As shown by the graph the first day of the test the temperatures were not very low with a normal humidity level.\
As the night started to fall, we were able to test our system in below freezing temperature without any issue. \
In addition, our system encountered serval rainy days varying from light to rather heavy rain. 

![image](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/ubidots2.jpg)

This experience ensured us about the autonomy of our system, knowing that we started it with about 50% of battery level. \
As shown in graph during the week the battery did not reach any critical level as it stayed above 50%. \
The second and third day of the experience were sunny in part of the day, so we were able to confirm that the solar panel is able to fully charge the battery in a relatively short time. \
In addition, we were able to conclude that the system could go through many days with clouds covering the sun during the entirety of the day, and even heavy fog as it was the case on the 11th of January. 

![image](https://github.com/CamilleDouzet/beelieve_in_ourselves/blob/main/image/ubidots3.jpg)

Unfortunately, we were not able to test the weight sensor in a variety of situations, as the bees do not leave the hive in theses temperatures.\
Although we were able to conclude that the sensor worked without any issue during the week as the readouts did not show any anomaly caused be the elements.

## Prospects for improvements

As a future work, we could have done the GPS option to protect the system and alert the bee-keepers in case of theft.

## Conclusion
Through this project, we have acquired many skills.

We first put into practice technical knowledge in electronics with the installation and use of several sensors. \
It was an opportunity for some to learn how to weld or to understand how to design a PCB for example. 

In the programming field, we were able to experiment with the implementation and management of several sensors with Arduino, each of which has its own specificity.

It was also an opportunity for us to put our ingenuity into practice by designing a 3D printed medium for the PDB as well as the outside temperature sensor.

We were able to implement a complete system thanks to Sigfox and Ubidots technologies. 

Finally, this project allowed us to learn to meet the needs of a client, here the beekeepers, in a collective way. 
Seeing our project deployed and functional is very rewarding for the team. We hope it will remain usable for a long time and will be useful to beekeepers.

## Source codes

We found some examples directly on the arduino application that helps to test the sensors.
We used the following libraries :
* DHT
* SigFox
* OneWire 
* ArduinoLowPower
* HX711
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
