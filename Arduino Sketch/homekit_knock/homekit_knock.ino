/*
 * stateless_programmable_switch.ino
 *
 *  Created on: 2020-05-16
 *      Author: Mixiaoxiao (Wang Bin)
 *
 *
 * HAP section 8.37 Stateless Programmable Switch
 * An accessory contains a stateless programmable switch, also called a button.
 * Used to report Programmable Switch Event to HomeKit.
 *
 * Programmable Switch Event: (HAP section 9.75)
 * 0 "Single Press"
 * 1 "Double Press"
 * 2 "Long Press"
 *
 * Note:
 * Reading this "Programmable Switch Event" should always return "null".
 * The value must only be reported in the events ("ev") property.
 *
 * You should:
 * 1. read and use the Example01_TemperatureSensor with detailed comments
 *    to know the basic concept and usage of this library before other examples。
 * 2. erase the full flash or call homekit_storage_reset() in setup()
 *    to remove the previous HomeKit pairing storage and
 *    enable the pairing with the new accessory of this new HomeKit example.
 */

#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"
#include <PeakDetection.h> // import lib
#include <Schedule.h>
#include <ESP8266mDNS.h>


#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);
PeakDetection peakDetection;
void setup() {
	Serial.begin(115200);
	wifi_connect(); // in wifi_info.h
	//homekit_storage_reset(); // to remove the previous HomeKit pairing storage when you first run this new HomeKit example
	my_homekit_setup();
  pinMode(LED_BUILTIN, OUTPUT);

  int lag =  64;
  int threshold = 5;
  double influence = 0.05;

  Serial.printf("\nlag=%0d-threshold=%0d-influence=%f\n", lag, threshold, influence);
  
  peakDetection.begin(lag, threshold, influence);
  schedule_recurrent_function_us(announce, 5000000);
}

void loop() {
	my_homekit_loop();
}

//==============================
// HomeKit setup and loop
//==============================

extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_programmable_switch_event;

#define PIN_BUTTON 0 // Use the Flash-Button of NodeMCU

#define HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_SINGLE_PRESS   0
#define HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_DOUBLE_PRESS   1
#define HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_LONG_PRESS     2

#define RATIO_SINGLE_PRESS 0.5
#define RATIO_DOUBLE_PRESS 2
#define RATIO_LONG_PRESS   1
#define RATIO_TOLERANCE    0.15

// Called when the value is read by iOS Home APP
homekit_value_t cha_programmable_switch_event_getter() {
	// Should always return "null" for reading, see HAP section 9.75
	return HOMEKIT_NULL_CPP();
}

void my_homekit_setup() {
	pinMode(PIN_BUTTON, INPUT_PULLUP);

	cha_programmable_switch_event.getter = cha_programmable_switch_event_getter;
	arduino_homekit_setup(&config);
}


static uint32_t next_heap_millis = 0;
uint8_t       cha_value = 0;
unsigned long previous_sample;
int           notified = 0;
int           rising_edge_count;
int           previous_level = 0;
int           current_level = 0;
unsigned long previous_rising_edge;

#define NUM_KNOCKS 3
double        millis_between_knocks[NUM_KNOCKS-1];
unsigned long knock_millis[NUM_KNOCKS];
int           knocks_in_prog = 0;
bool          is_knock_in_prog = false;

int           knock_millis_minimum = 120;

void rising_edge_detected(){
  static unsigned long previous_millis;
  unsigned long current_millis = millis();
  is_knock_in_prog = true;

  

  if(current_millis - previous_millis > knock_millis_minimum){
    knock_millis[knocks_in_prog] = current_millis;
    previous_rising_edge = knock_millis[knocks_in_prog];
    Serial.printf("Knock_millis[%0d] = %0d (diff_with_previous=%0d)\n", knocks_in_prog, knock_millis[knocks_in_prog], knock_millis[knocks_in_prog]-knock_millis[(knocks_in_prog+(NUM_KNOCKS-1))%NUM_KNOCKS]  );
    knocks_in_prog++;
    knocks_in_prog %= NUM_KNOCKS;
    
    recognize_knock();
    previous_millis = current_millis;
  }
}

void recognize_knock(){
  unsigned long aligned_millis[NUM_KNOCKS];
  int notified = 0;
  for(int i = 0; i < NUM_KNOCKS; i++){
    aligned_millis[i] = knock_millis[(knocks_in_prog+i)%NUM_KNOCKS];
  }
  
  if(aligned_millis[0] != -1 &&
     aligned_millis[1] != -1 &&
     aligned_millis[2] != -1){
    float ratio;
    millis_between_knocks[0] = aligned_millis[1] - aligned_millis[0];
    millis_between_knocks[1] = aligned_millis[2] - aligned_millis[1];

    ratio = millis_between_knocks[0] / millis_between_knocks[1];
    Serial.printf("Ratio=%f\n", ratio);
    if(  (ratio > (RATIO_SINGLE_PRESS - RATIO_TOLERANCE)) && (ratio < (RATIO_SINGLE_PRESS + RATIO_TOLERANCE))){
      
      cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_SINGLE_PRESS;
      cha_programmable_switch_event.value.uint8_value = cha_value;
      homekit_characteristic_notify(&cha_programmable_switch_event, cha_programmable_switch_event.value);
      Serial.println("Single Pressed");
      notified = 1;
    }else if(  (ratio > (RATIO_DOUBLE_PRESS - RATIO_TOLERANCE)) && (ratio < (RATIO_DOUBLE_PRESS + RATIO_TOLERANCE))){
      
      cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_DOUBLE_PRESS;
      cha_programmable_switch_event.value.uint8_value = cha_value;
      homekit_characteristic_notify(&cha_programmable_switch_event, cha_programmable_switch_event.value);
      Serial.println("Double Pressed");
      notified = 1;
    }else if(  (ratio > (RATIO_LONG_PRESS - RATIO_TOLERANCE)) && (ratio < (RATIO_LONG_PRESS + RATIO_TOLERANCE))){
      
      cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_LONG_PRESS;
      cha_programmable_switch_event.value.uint8_value = cha_value;
      homekit_characteristic_notify(&cha_programmable_switch_event, cha_programmable_switch_event.value);
      Serial.println("Long Pressed");
      notified = 1;
    }
    if(notified == 1){
      clear_knock_time(1);
    }
  }
}

void clear_knock_time(int id){
  knock_millis[0] = -1;
  knock_millis[1] = -1;
  knock_millis[2] = -1;
  knocks_in_prog = 0;
  is_knock_in_prog = false;
  Serial.printf("[%0d] Clearing knock time, millis=%0d (previous_millis=%0d, diff=%0d)\n", id, millis(), previous_rising_edge, millis() - previous_rising_edge);
}

unsigned long previous_flash;
unsigned long previous_homekit_loop;
void my_homekit_loop() {
  unsigned long current_millis = millis();

  if((current_millis - previous_sample > 20) && (arduino_homekit_connected_clients_count() > 0) && homekit_is_paired()){
    current_level = process_sensor();
    if(previous_level == 0 && current_level == 1){
      rising_edge_count++;
      rising_edge_count %= 3;
      notified = 0;
      rising_edge_detected();
    } else if(current_millis - previous_rising_edge > 1000 && is_knock_in_prog){
      clear_knock_time(0);
    }
    previous_level  = current_level;
    previous_sample = current_millis;
  }

  if(current_millis - previous_flash > 250){
    static bool previous_level;
    if( (arduino_homekit_connected_clients_count() <= 0 || !homekit_is_paired()) || previous_level == false ){
      digitalWrite(LED_BUILTIN, previous_level);
      previous_level = !previous_level;
    }
    previous_flash = current_millis;
  }

  

  if(current_millis - previous_homekit_loop > 5){
    previous_homekit_loop = current_millis;
	  arduino_homekit_loop();
  }
  
  yield();

}

unsigned long previous_led_on;
int previous_analog_read;
int previous_peak[4];
int previous_peak_pointer;

int rolling_average_num = 4;
int process_sensor(){
  int analog_val;

  int analog_val_proc;
  analog_val = analogRead(A0);
  analog_val_proc = previous_analog_read-analog_val;
 
  peakDetection.add(analog_val);
  int peak = peakDetection.getPeak();
  previous_peak[previous_peak_pointer] = peak;
  previous_peak_pointer++;
  previous_peak_pointer %= 4;
  int peak_proc = (previous_peak[0] != 0) || (previous_peak[1] != 0) || (previous_peak[2] != 0) || (previous_peak[3] != 0);
  previous_analog_read = analog_val;
//  Serial.printf("250 0 %0d %0d %0d\n", analog_val, peak*100, 105 + peak_proc*100);
  return peak_proc;
}

bool announce() {
  MDNS.announce();
  return true;
}
