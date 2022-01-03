#define MQTT_SERVER "IP address"
#define MQTT_PORT 1883
#define MQTT_USER "put your name"
#define MQTT_PASSWORD "put uour password"
#define MQTT_CLIENT_ID "CambridgeAudio"


#define WIFI_SSID "your wifi"
#define WIFI_PASSWORD "your wifi password"


// ---- stop editing from here down ----

const char *command_topic = "Azure/command";
const char *status_topic = "Azure/status";

const unsigned int baud_rate = 9600;

bool powerState = false; // store the power stat of the device
int8_t volume; 
bool isMuted = false; // store if the device is muted
String selectedInput; // store the selected input type
String sourceType; // store the selected source
bool tunerBand = true; //store tuner band
String surroundMode = "PCM"; // surround cycle to next mode
String currentMode; // DTS/DD mode
String drcSet = "Auto"; //dynamic range control
bool biAmping = false; // macro for bi-amping

String receivedSerialMessage; // store the message received from the device over RS2322
//commands to Azure
const char *onCommand = "#1,01,1";
const char *offCommand = "#1,01,0";

const char *volumeUpCommand = "#1,02";
const char *volumeDownCommand = "#1,03";

const char *muteCommand = "#1,11,01";
const char *unmuteCommand = "#1,11,00";

const char *drcAutoCommand = "#1,12,00";
const char *drcOnCommand = "#1,12,02";
const char *drcOffCommand = "#1,12,01";

const char *osdOnCommand = "#1,13";
const char *osdBackCommand = "#1,14";
const char *osdUpCommand = "#1,15";
const char *osdDownCommand = "#1,16";
const char *osdLeftCommand = "#1,17";
const char *osdRightCommand = "#1,18";
const char *osdEnterCommand = "#1,19";


const char *inputSelectBDCommand = "#2,01,01";
const char *inputSelectCDCommand = "#2,01,02";
const char *inputSelectVideo2Command = "#2,01,03";
const char *inputSelectAuxCommand = "#2,01,04";
const char *inputSelectTapeCommand = "#2,01,05";
const char *inputSelectTunerCommand = "#2,01,06";
const char *inputSelectVid3MP3Command = "#2,01,07";
const char *inputSelectDirectInCommand = "#2,01,08";
const char *inputSelectTVARCCommand = "#2,01,09";

const char *sourceTypeAnalogueCommand = "#2,04,00";
const char *sourceTypeDigitalCommand = "#2,04,01";
const char *sourceTypeHDMICommand = "#2,04,02";

const char *tunerBandFMCommand = "#3,09,00";
const char *tunerBandAMCommand = "#3,09,01";

const char *surroundModesCommand = "#4,03";  //cycles to next
const char *currentDDDTSModeCommand = "#4,05";

// Replays from Azure
const char *onOffReply = "#6,01";
const char *onReply = "1";
const char *offReply = "0"; //00

const char *volumeUpReply = "#6,02";
const char *volumeDownReply = "#6,03";

const char *muteReply = "#6,11";
const char *muteOnReply = "01";
const char *muteOffReply = "00";

const char *drcReplay = "#6,12";
const char *drcAutoReply = "00";
const char *drcOnReply = "02";
const char *drcOffReply = "01";

const char *osdOnReplay = "#6,13";
const char *osdBackReplay = "#6,14";
const char *osdUpReplay = "#6,15";
const char *osdDownReplay = "#6,16";
const char *osdLeftReplay = "#6,17";
const char *osdRightReplay = "#6,18";
const char *osdEnterReplay = "#6,19";


const char *inputSelectedReply = "#7,01";
const char *inputSelectedBDReply = "01";
const char *inputSelectedCDReply = "02"; 
const char *inputSelectedVideo2Reply = "03";
const char *inputSelectedAuxReply = "04";
const char *inputSelectedTapeReply = "05";
const char *inputSelectedTunerReply = "06";
const char *inputSelectedVid3MP3Reply = "07";
const char *inputSelectedDirectInReply = "08";
const char *inputSelectedTVARCReply = "09";

const char *sourceTypeReply = "#7,04";
const char *sourceTypeAnalogueReply = "00";
const char *sourceTypeDigitalReply = "01";
const char *sourceTypeHDMIReply = "02";


const char *tunerBandReplay = "#8,09";
const char *tunerBandFMReplay = "00";
const char *tunerBandAMReplay = "01";

const char *surroundModesReplay = "#9,03";
const char *currentDDDTSModeReplay = "#9,05";


const char *commandGroupUnknownError = "#11,01";
const char *commandNumberInGroupUnknownError = "#11,02";
const char *commandDataError = "#11,03";

// replays mapping
const char *inputSelectedBDLabel = "BDDVD";
const char *inputSelectedCDLabel = "CDVideo1";
const char *inputSelectedVideo2Label = "Video2";
const char *inputSelectedAuxLabel = "AuxTV";
const char *inputSelectedTapeLabel = "TapeMDCDR";
const char *inputSelectedTunerLabel = "Tuner";
const char *inputSelectedVid3MP3Label = "Vid3MP3";
const char *inputSelectedDirectInLabel = "DirectIn";
const char *inputSelectedTVARCLabel = "TVARC";

const char *sourceTypeAnalogueLabel = "Analogue";
const char *sourceTypeDigitalLabel = "Digital";
const char *sourceTypeHDMILabel = "HDMI";

const char *drcAutoLabel = "Auto";
const char *drcOnLabel = "On";
const char *drcOffLabel = "Off";


 
