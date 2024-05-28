#include <Arduino.h>
#include <font6x8.h>
#include <ssd1306xled.h>

unsigned long mstime = 0; // measurment start time

unsigned long R = 47000; //value of connected resistor

int output_555_pin = 3; // output from 555 pin3

int analog_pin = 4;

int output_state;

bool measuring = false;
bool change_state = true;

unsigned long etime = 0;
char etime_c[20] = {"0"};

unsigned long result = 0;
char result_c[20] = {"0"};

char analog_c[20] = {"0"};
int val = 0;
int oldval = 0;


void setup() {
  _delay_ms(40);
  SSD1306.ssd1306_init();

  pinMode(output_555_pin, INPUT);

  SSD1306.ssd1306_fillscreen(0x00);

  delay(1500);
}

void loop() {
  output_state = digitalRead(output_555_pin);

  // val = analogRead(A2);
  // if(oldval > val){
  //   val = oldval;
  // }else{
  //   oldval = val;
  // }
  SSD1306.ssd1306_setpos(0, 30);
  snprintf(analog_c, 20, "Analog = %d", val);
  SSD1306.ssd1306_string_font6x8(analog_c); 


  if(measuring == false && output_state == HIGH){
    measuring = true;
    mstime = millis();
    change_state = true;
  }

  if(measuring == true && output_state == LOW){
    measuring = false;
    etime = millis() - mstime;
    result = (etime*1000) / (long int)(R*1.1);

    SSD1306.ssd1306_setpos(0, 10); 
    snprintf(etime_c, 20, "t = %lu     ", etime);
    SSD1306.ssd1306_string_font6x8(etime_c);

    SSD1306.ssd1306_setpos(0, 20);
    snprintf(result_c, 20, "C = %d uF      ", result);
    SSD1306.ssd1306_string_font6x8(result_c);  
    change_state = true;
  } 

  if(change_state){
    SSD1306.ssd1306_setpos(0, 0);
    if(measuring){
      SSD1306.ssd1306_string_font6x8("Measuring    ");  
    }else{
      SSD1306.ssd1306_string_font6x8("Not measuring");  
    }
    change_state = false;
  }
}