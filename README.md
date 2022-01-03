#azure_openhab
This repository allows to integrate Cambridge Audio Azure 551 with openHAB. 

The Azure 551 can be controled by external systems via an RS232 port.
The following "converter" shall be prepared:

Wemos D1 mini
Max2323
Power supply

The converter communicates with Azure 551 via RS232 protocol and port.

The converter communicates with openHAB via MQTT protocol. The physical connection via Wifi.

#Converter set up (Arduino):
* Install and run arduino IDE, connect to Wemos D1 mini via USB.
* Upload brink_hr(https://github.com/raf1000/azure_openhab/blob/main/Arduino/CambridgeAudio) program: Brink_HR.ino to arduino IDE
* Specify network and mqtt parameters in the definitions.h program. make sure that definitions.h file is visible by the main program.
* Upload the compiled Brink_HR progrm to wemos D1 mini. Connect wemos D1 mini to the max2323 and RS232 port of Azure. 
#openHAB set up:
* Install and set up MQTT Broker (mosquitto)
* Install MQTT binding in openHAB
* Create items : [azure.items](https://github.com/raf1000/azure_openhab/blob/main/openHAB/azure.items) file
* Create MQTT client with channels : [azure_mqtt_client](https://github.com/raf1000/azure_openhab/blob/main/openHAB/azure_mqtt_client) file
* Update sitemap : [azure.sitemap](https://github.com/raf1000/azure_openhab/blob/main/openHAB/azure.sitemap) file 
* Add rules : [azure.rules](https://github.com/raf1000/azure_openhab/blob/main/openHAB/azure.rules) file
#Some notes:
??
