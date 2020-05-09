
#include <ESP8266WiFi.h>
#include <Time.h>
#include <Timezone.h>
#include "NTP.h"
#define WIFI_SSID "79"       // 使用时请修改为当前你的 wifi ssid
#define WIFI_PASS "79797979"   // 使用时请修改为当前你的 wifi 密码

// 北京时间时区
#define STD_TIMEZONE_OFFSET +8    // Standard Time offset (-7 is mountain time)

TimeChangeRule mySTD = {"", First,  Sun, Jan, 0, STD_TIMEZONE_OFFSET * 60};
Timezone myTZ(mySTD, mySTD);
WiFiClient client;

// This function is called once a second
void update(void) {
  TimeChangeRule *tcr;        // Pointer to the time change rule
  // Read the current UTC time from the NTP provider
  time_t utc = now();
  // Convert to local time taking DST into consideration
  time_t localTime = myTZ.toLocal(utc, &tcr);

  int weekdays =   weekday(localTime);
  int days    =   day(localTime);
  int months  =   month(localTime);
  int years   =   year(localTime);

  int seconds =   second(localTime);
  int minutes =   minute(localTime);
  int hours   =   hour(localTime) ;   //12 hour format use : hourFormat12(localTime)  isPM()/isAM()

}

void loop() {}
  


void serialEvent(){
  while (Serial.available())   //时刻读取硬件串口数据
  {
    if (char(Serial.read())=="wifi)"{
    if (c==1) Serial.print("ok");
  }else if (char(Serial.read())=="time"{
    update();
    Serial.println(year);
    delay(10);
    Serial.println(month);
    delay(10);
    Serial.println(day);
    delay(10);
    Serial.println(hour);
    delay(10);
    Serial.println(minute);
    delay(10);
    Serial.println(second);
    delay(10);
  } 
  while (Serial.read() >= 0) {} //清除串口缓存
}
  
}
