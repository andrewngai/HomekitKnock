/*
 * wifi_info.h
 *
 *  Created on: 2020-05-15
 *      Author: Mixiaoxiao (Wang Bin)
 */

#ifndef WIFI_INFO_H_
#define WIFI_INFO_H_

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif
#include <WiFiManager.h>  


uint8_t mac[WL_MAC_ADDR_LENGTH];
int name_len;
char *name_value;

void wifi_connect() {
  WiFiManager wifiManager;
  
WiFi.macAddress(mac);
  name_len = snprintf(NULL, 0, "%s_%02X%02X%02X","Knock", mac[3], mac[4], mac[5]);
  name_value = (char*)malloc(name_len + 1);
  snprintf(name_value, name_len + 1, "%s_%02X%02X%02X", "Knock", mac[3], mac[4], mac[5]);
  
  wifiManager.autoConnect(name_value);  

	Serial.println("WiFi connecting...");
	while (!WiFi.isConnected()) {
		delay(100);
		Serial.print(".");
	}
	Serial.print("\n");
	Serial.printf("WiFi connected, IP: %s\n", WiFi.localIP().toString().c_str());
 
}

#endif /* WIFI_INFO_H_ */
