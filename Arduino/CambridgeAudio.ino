#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "include/definitions.h" 
//#include <SoftwareSerial.h>
//SoftwareSerial* logger = nullptr;


const int BUFFER_SIZE = JSON_OBJECT_SIZE(22); //returns the number of bytes required to store a JSON object that contains n key-value pairs.

WiFiClient espClient;
PubSubClient mqttClient;


void sendStateToMQTT()
{
  StaticJsonDocument<BUFFER_SIZE> jsonDocument; //stores a JSON document in memory. It owns the memory referenced JsonObject,

  jsonDocument["status"] = powerState ? "ON" : "OFF"; 
  jsonDocument["volume"] = volume;
  jsonDocument["isMute"] = isMuted ? "ON" : "OFF";
  jsonDocument["selectedInput"] = selectedInput;
  jsonDocument["sourceType"] = sourceType;
  jsonDocument["tunerBand"] = tunerBand ? "FM" : "AM";
  jsonDocument["surroundMode"] = surroundMode;
  jsonDocument["currentMode"] = currentMode;
  jsonDocument["drcSet"] = drcSet;
  jsonDocument["biAmp"] = biAmping ? "ON" : "OFF";
  jsonDocument["signalWifi"] = WiFi.RSSI();

  char buffer[BUFFER_SIZE];
  size_t n = serializeJson(jsonDocument, buffer); // n = number of bytes
  mqttClient.publish(status_topic, buffer, true);
}

void sendCommandToSerial(String command)
{
// logger->print(command);
  Serial.println(command);
}


void SerialRead()
{
  while (Serial.available() > 0)
  {
    char recieved = Serial.read();
    receivedSerialMessage += recieved;

    if (recieved == '\r')
    {
      receivedSerialMessage = ""; // Clear recieved buffer
      return;
    }
  }
}


void serialReadLoop()
{
  while (Serial.available() > 0)
  {
    char recieved = Serial.read();
    receivedSerialMessage += recieved;

    // Process message when carriage return character is recieved
    if (recieved == '\r')
    {
      receivedSerialMessage.trim(); // too usuwa spacje a nie znak /r
    
      if (!receivedSerialMessage.isEmpty())
      {
        handleReceivedMessage(receivedSerialMessage);
        receivedSerialMessage = ""; // Clear recieved buffer
      }
    }
  }
}

bool handleReceivedMessage(String replyMessage)
{
  String error = checkForError(replyMessage);

  if (!error.isEmpty())
  {
//logger->print("Got error : " + error);
    return false;
  }
  if (replyMessage.substring(0, 5) == onOffReply)                 handleOnOffReply(replyMessage.substring(6, 7));
  else if (replyMessage.substring(0, 5) == muteReply)             handleMuteReply(replyMessage.substring(6, 8));
  else if (replyMessage.substring(0, 5) == inputSelectedReply)    handleInputTypeMessage(replyMessage.substring(6, 8));
  else if (replyMessage.substring(0, 5) == sourceTypeReply)       handleSourceMessage(replyMessage.substring(6, 8));
  else if (replyMessage.substring(0, 5) == volumeUpReply || replyMessage.substring(0, 5) == volumeDownReply) handleVolumeMessage(replyMessage.substring(6,9));
  else if (replyMessage.substring(0, 5) == tunerBandReplay)        handleTunerBandMessage(replyMessage.substring(6, 8));
  else if (replyMessage.substring(0, 5) == surroundModesReplay)    handleSurroundModesMessage(replyMessage.substring(6));
  else if (replyMessage.substring(0, 5) == currentDDDTSModeReplay) handleCurrentDDDTSModeMessage(replyMessage.substring(6));
  else if (replyMessage.substring(0, 5) == drcReplay)              handleDrcMessage(replyMessage.substring(6,8));
  else if (replyMessage.substring(0, 4) == osdOnReplay);    // do nothing
  else if (replyMessage.substring(0, 4) == osdBackReplay);  // do nothing
  else if (replyMessage.substring(0, 4) == osdUpReplay);    // do nothing
  else if (replyMessage.substring(0, 4) == osdDownReplay);  // do nothing
  else if (replyMessage.substring(0, 4) == osdLeftReplay);  // do nothing
  else if (replyMessage.substring(0, 4) == osdRightReplay); // do nothing
  else if (replyMessage.substring(0, 4) == osdEnterReplay); // do nothing
  else
  {
//    logger->print("Unknown/custom reply message: " + replyMessage);
    return false;
  }
  sendStateToMQTT();
  return true;
}



String checkForError(String replyMessage)
{
  if (replyMessage == commandGroupUnknownError)         return "unknown command group";
  if (replyMessage == commandNumberInGroupUnknownError) return "unknown command number in group";
  if (replyMessage == commandDataError)                 return "unknown command data";
  return "";
}

void handleOnOffReply(String onOffReplyMessage)
{
  if (onOffReplyMessage == onReply)  powerState = true;
  if (onOffReplyMessage == offReply) powerState = false;
//  else  logger->print("Unknown on/off reply message: " + onOffReplyMessage);
}

void handleVolumeMessage(String volumeReplyMessage)
{
//  logger->print("Volume reply message: " + volumeReplyMessage);
  volume = volumeReplyMessage.toInt();
//  volume = volume ? volume : -56;
}

void handleMuteReply(String muteReplyMessage)
{
  if (muteReplyMessage == muteOnReply)   isMuted = true;
  if (muteReplyMessage == muteOffReply)  isMuted = false;
//  else logger->print("Unknown mute reply message: " + muteReplyMessage);
}

void handleInputTypeMessage(String inputTypeMessage)
{
  if (inputTypeMessage == inputSelectedBDReply)      selectedInput = inputSelectedBDLabel;
  if (inputTypeMessage == inputSelectedCDReply)      selectedInput = inputSelectedCDLabel;
  if (inputTypeMessage == inputSelectedVideo2Reply)  selectedInput = inputSelectedVideo2Label;
  if (inputTypeMessage == inputSelectedAuxReply)     selectedInput = inputSelectedAuxLabel;
  if (inputTypeMessage == inputSelectedTapeReply)    selectedInput = inputSelectedTapeLabel;
  if (inputTypeMessage == inputSelectedTunerReply)   selectedInput = inputSelectedTunerLabel;
  if (inputTypeMessage == inputSelectedVid3MP3Reply) selectedInput = inputSelectedVid3MP3Label;
  if (inputTypeMessage == inputSelectedDirectInReply)selectedInput = inputSelectedDirectInLabel;
  if (inputTypeMessage == inputSelectedTVARCReply)   selectedInput = inputSelectedTVARCLabel;
//  else logger->print("Unknown input type reply message: " + inputTypeMessage);
}

void handleSourceMessage(String sourceMessage)
{
  if (sourceMessage == sourceTypeAnalogueReply)sourceType = sourceTypeAnalogueLabel;
  if (sourceMessage == sourceTypeHDMIReply)    sourceType = sourceTypeHDMILabel;
  if (sourceMessage == sourceTypeDigitalReply) sourceType = sourceTypeDigitalLabel;
//  else logger->print("Unknown source reply message: " + sourceMessage);
}

void handleTunerBandMessage(String bandMessage)
{
  if (bandMessage == tunerBandFMReplay)    tunerBand = true;
  if (bandMessage == tunerBandAMReplay)    tunerBand = false;
//  else logger->print("Unknown source reply message: " + bandMessage);
}

void handleSurroundModesMessage(String surroundMessage)
{
  surroundMode = surroundMessage;
}

void handleCurrentDDDTSModeMessage(String currentMessage)
{
  currentMode =  currentMessage;
}


void handleDrcMessage( String drcMessage)
{
  if (drcMessage == drcAutoReply) drcSet = drcAutoLabel;
  if (drcMessage == drcOnReply)   drcSet = drcOnLabel;
  if (drcMessage == drcOffReply)  drcSet = drcOffLabel;  
}


void callback(char *topic, byte *payload, unsigned int length)
{
  char message[length + 1];
  for (unsigned int i = 0; i < length; i++)
  {
    message[i] = (char)payload[i];
  }
  message[length] = '\0'; // Null terminator used to terminate the char array

  if (!processJson(message))
  {
//    logger->print("Could not process message");
    return;
  }
}


bool processJson(char *message)
{
  StaticJsonDocument<BUFFER_SIZE> jsonDocument;

  deserializeJson(jsonDocument, message);
  JsonObject root = jsonDocument.as<JsonObject>(); //

  if (root.isNull())
  {
//   logger->print("parseObject() failed");
    return false;
  }

  if (root.containsKey("status"))
  {
    if (root["status"] == "ON") sendCommandToSerial(onCommand);
    else if (root["status"] == "OFF") sendCommandToSerial(offCommand);
  }
  if (root.containsKey("mute"))
  {
    if (root["mute"] == "ON")sendCommandToSerial(muteCommand);
    else if (root["mute"] == "OFF")sendCommandToSerial(unmuteCommand);
  }
  if (root.containsKey("volume"))
  {
    if (root["volume"] == "up")sendCommandToSerial(volumeUpCommand);
    else if (root["volume"] == "down")sendCommandToSerial(volumeDownCommand);
  }
  if (root.containsKey("input"))
  {
    if (root["input"] == inputSelectedBDLabel)          sendCommandToSerial(inputSelectBDCommand);
    else if (root["input"] == inputSelectedCDLabel)     sendCommandToSerial(inputSelectCDCommand);
    else if (root["input"] == inputSelectedVideo2Label) sendCommandToSerial(inputSelectVideo2Command);
    else if (root["input"] == inputSelectedAuxLabel)    sendCommandToSerial(inputSelectAuxCommand);
    else if (root["input"] == inputSelectedTapeLabel)   sendCommandToSerial(inputSelectTapeCommand);
    else if (root["input"] == inputSelectedTunerLabel) sendCommandToSerial(inputSelectTunerCommand);
    else if (root["input"] == inputSelectedVid3MP3Label)sendCommandToSerial(inputSelectVid3MP3Command);
    else if (root["input"] == inputSelectedDirectInLabel)sendCommandToSerial(inputSelectDirectInCommand);
    else if (root["input"] == inputSelectedTVARCLabel)  sendCommandToSerial(inputSelectTVARCCommand);
  }

  if (root.containsKey("sourceType"))
  {
    if (root["sourceType"] == sourceTypeAnalogueLabel)      sendCommandToSerial(sourceTypeAnalogueCommand);
    else if (root["sourceType"] == sourceTypeHDMILabel)     sendCommandToSerial(sourceTypeHDMICommand);
    else if (root["sourceType"] == sourceTypeDigitalLabel)  sendCommandToSerial(sourceTypeDigitalCommand);
  }

  if (root.containsKey("tunerBand"))
  {
    if (root["tunerBand"] == "FM")       sendCommandToSerial(tunerBandFMCommand);
    else if (root["tunerBand"] == "AM")  sendCommandToSerial(tunerBandAMCommand);
  }

  if (root.containsKey("surroundMode"))
  {
    if (root["surroundMode"] == "Next")  sendCommandToSerial(surroundModesCommand);
  }

  if (root.containsKey("currentMode"))
  {
    if (root["currentMode"] == "Get")       sendCommandToSerial(currentDDDTSModeCommand);
  }

  if (root.containsKey("drcSet"))
  {
    if (root["drcSet"] == drcAutoLabel)      sendCommandToSerial(drcAutoCommand);
    else if (root["drcSet"] == drcOnLabel)   sendCommandToSerial(drcOnCommand);
    else if (root["drcSet"] == drcOffLabel)  sendCommandToSerial(drcOffCommand);
  }

  if (root.containsKey("biAmp")) //macro for Biamp
  {
    if (root["biAmp"] == "ON") {
      sendCommandToSerial(osdOnCommand);
      SerialRead();
      biAmping = true;
      delay(1000);
      sendStateToMQTT();
      sendCommandToSerial(osdDownCommand);
      SerialRead();
      delay(500);
      sendCommandToSerial(osdDownCommand);
      SerialRead();
      delay(500);
      sendCommandToSerial(osdDownCommand);
      SerialRead();
      delay(1000);
      sendCommandToSerial(osdEnterCommand);
      SerialRead();
      delay(1000);
      sendCommandToSerial(osdDownCommand);
      SerialRead();
      delay(500);
      sendCommandToSerial(osdDownCommand);
      SerialRead();
      delay(500);
      sendCommandToSerial(osdDownCommand);
      SerialRead();
      delay(500);
      sendCommandToSerial(osdDownCommand);
      SerialRead();
      delay(500);
      sendCommandToSerial(osdDownCommand);
      SerialRead();
      delay(1000);
      sendCommandToSerial(osdRightCommand);
      SerialRead();
      delay(1000);
      sendCommandToSerial(osdBackCommand);
      SerialRead();
      biAmping = false;
      delay(1000);
      sendCommandToSerial(osdBackCommand);
      SerialRead();
      sendStateToMQTT();
    }
  }

  if (root.containsKey("rawCommand"))
  {
    sendCommandToSerial(root["rawCommand"]);
  }

  return true;
}



void mqttConnect()
{
  while (!mqttClient.connected())
  {
    if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD))
    {
 //    logger->println("MQTT connected");
      mqttClient.subscribe(command_topic);
      delay(1000);
    }
    else
    {
//      logger->println("MQTT connection failed, rc=" + String(mqttClient.state()));
//      logger->println("Trying again in 5 seconds");
      delay(5000);
    }
  }
}


void setup()
{
  Serial.begin(baud_rate);

 // Serial.swap();
  // Hardware serial is now on RX:GPIO13 (D7) TX:GPIO15 (D8)
  // use SoftwareSerial on regular RX(3)/TX(1) for logging

//  logger = new SoftwareSerial(3, 1);
//  logger->begin(9600);
//  logger->enableIntTx(false);
 

   WiFi.mode(WIFI_STA); 
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) 
   {
//     logger->print(".");
     delay(500);
   }
//  logger->println();
//  logger->print("connected, address=");
//  logger->println(WiFi.localIP());

  mqttClient.setClient(espClient);
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(callback);

  mqttConnect();
  sendStateToMQTT();
}

void loop()
{
  if (!mqttClient.connected())
  {
    delay(1000);
    mqttConnect();
  }

  mqttClient.loop();

  serialReadLoop();  
}
