/*
TODO: Define controls
controllable values:

1-4 -speed up/down/absolute/read (uint8_t r = value)
5-8 -mode up/down/absolute/read  (uint8_t r = value)
9-12 -brightness up/down/absolute/read (uint8_t r = value)
15-16 -color up/down
21-26 -set/get fade colors (rgb) (21=set1,22=get1, 23=set2,24=get2, 25=set3,26=get3
50 -get speed,mode,brightness (r=speed,g=mode,b=brightness)


to get all variables:
4 (get speed)
8 (get mode)
12 (get brightness)
22 (get color 1)
24 (get color 2)
26 (get color 3)

50 get speed, mode, brightness

*/

#include <gmaRGBLight.h>
#include <RF24.h>

#define SOUND_REQUEST_INTERVAL 120000  // 2 minutes

RF24 radio(9,10);

void RF_Init() {
  radio.begin();
  radio.setDataRate(RF24_1MBPS);  // RF24_250KBPS
  radio.setChannel(50);    // 2.450 GHz
  radio.setPayloadSize(sizeof(rf_hat_payload_t));
  radio.setAutoAck(false);  // fixed payload size + autoAck(false) = ShockBurst transmission (quicker)
  //radio.setRetries(15,10);
  radio.setCRCLength(RF24_CRC_8);
  
  radio.openWritingPipe(RF_SOUND_FOR_EVERYONE_PIPE);
  
  radio.openReadingPipe(1,RF_CONTROL_THE_HAT_PIPE);

  radio.startListening();
}

void RF_SoundForEveryone() {
  rf_hat_payload_t payload;
  payload.command = 1;
  payload.mode = 0;
  payload.band0 = cnf.eq8Band[0]; payload.band1 = cnf.eq8Band[1];
  payload.band2 = cnf.eq8Band[2]; payload.band3 = cnf.eq8Band[3];
  payload.band4 = cnf.eq8Band[4]; payload.band5 = cnf.eq8Band[5];
  payload.band6 = cnf.eq8Band[6]; payload.band7 = cnf.eq8Band[7];
  //do not need --radio.stopListening();
  radio.write( &payload, sizeof(payload));
  radio.startListening();
}

void RF_RgbLightCommand(rf_hat_payload_t *_command) {
  switch(_command->command) {
  
    // commands that make sense (imho):
    
    // get/set brightness
    // get/set mode
    // get/set automodechange
    // request sound broadcast
    
    // enable music broadcast? always enabled?
    
    case 2:
    break;
    
  /*
    case 2: // speed down
      ChangeDelay(0);
      _command->value = s.currDelay;
    break;
    case 3: // speed absolute
      SetDelay(_command->r);
      _command->value = s.currDelay;
    break;
    
    case 5: // mode up
      ChangeMode(1);
      _command->value = s.currMode;
    break;
    case 6: // mode down
      ChangeMode(0);
      _command->value = s.currMode;
    break;
    case 7: // mode absolute
      SetMode(_command->value);
      _command->value = s.currMode;
    break;
    
    case 9: // brightness up
      ChangeBrightness(1);
      _command->value = s.currBrightness;
    break;
    case 10: // brightness down
      ChangeBrightness(0);
      _command->value = s.currBrightness;
    break;
    case 11: // brightness absolute
      SetBrightness(_command->value);
      _command->value = s.currBrightness;
    break;
    */
  }
}

void RF_Read() {
  if(radio.available()) {
    rf_hat_payload_t payload;
    radio.read( &payload, sizeof(payload));
    
    if(payload.command > 1) {
      RF_RgbLightCommand(&payload);
    }
  }
}


