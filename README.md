# CA_azure_openhab
This repository allows to integrate Cambridge Audio Azure 551 with openHAB. 

The Azure 551 can be controled by external systems via an RS232 port.
Build/buy a "converter" prepared of the following elements:

* Wemos D1 mini
* Max2323
* Power supply

It can look like the following:

![Converter](https://github.com/raf1000/azure_openhab/blob/main/CA_converter.jpg)


The converter communicates with Azure 551 via RS232 protocol and port.

The converter communicates with openHAB via MQTT protocol. The physical connection via Wifi.

# Converter set up (Arduino):
* Install and run arduino IDE, connect to Wemos D1 mini via USB.
* Upload [CambridgeAudio.ino](https://github.com/raf1000/azure_openhab/blob/main/Arduino/CambridgeAudio.ino) program to arduino IDE
* Save the new program and add directory "include" in it. Load there the [deifnitions.h](https://github.com/raf1000/azure_openhab/blob/main/Arduino/definitions.h) file
* Specify network and mqtt parameters in the definitions.h file.
* Upload the compiled CambridgeAudio.ino progrm to wemos D1 mini. Connect wemos D1 mini to the max2323 and RS232 port of Azure. 
# openHAB set up:
* Install and set up MQTT Broker (mosquitto)
* Install MQTT binding in openHAB
* Add JSONPatch Transformation in openHAB
* Create items : [azure.items](https://github.com/raf1000/azure_openhab/blob/main/openHAB/azure.items) file
* Create MQTT client with channels : [azure_mqtt_client](https://github.com/raf1000/azure_openhab/blob/main/openHAB/azure_mqtt_client) file
* Update sitemap : [azure.sitemap](https://github.com/raf1000/azure_openhab/blob/main/openHAB/azure.sitemap) file 
* Add rules : [azure.rules](https://github.com/raf1000/azure_openhab/blob/main/openHAB/azure.rules) file
# Some notes:
1. The integration is tested with Cambridge Audio Azure 551R V2 but shall work for other/similar models as well
2. The integration covers most usefull (for me) functions only and can be extended based on the attached document of Azure 551 serial protocol. But not all features of Azure 551 available in OSD are available via serial protocol.
3. Bi-amping feature of Azure551 is not accesible directly in the serial protocol. I have implemented a "macro" in Arduino part which uses OSD commands to change (toggle) bi-amping ON/OFF . The change of biamping takes ~ 10seconds. Other functions not supported by the Azure serial protocol can be accessed in a similar way. Or you can use raw command in openHAB to define a similar logic using rules.
