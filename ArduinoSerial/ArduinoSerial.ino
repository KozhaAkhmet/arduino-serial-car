// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <ArduinoJson.h>

AF_DCMotor motor[4](1);
#define DEFAULT_SPEED 120
#define DEBUG false

String data;
int global_speed;
int motor_states[4] {};

#if DEBUG == false //======================

void setup() {
  Serial.begin(9600);           
  Serial.println("Started!");
  
  global_speed = DEFAULT_SPEED;

  for(int i = 0 ; i < 4 ; i++){
    motor[i] = AF_DCMotor(i+1);
    motor[i].setSpeed(global_speed);
    motor[i].run(RELEASE);
    motor[i].run(FORWARD);
  }  
  stop();
}

void loop() {
  if(Serial.available() > 0){

    static StaticJsonDocument<50> json_doc;
    const auto serial_data = deserializeJson(json_doc,Serial);

    int global_speed = json_doc["speed"];
    String c =  json_doc["direction"]; 

    if( c.equals("w") ){
      forward(global_speed);
    }else
    if( c.equals("s") ){
      backward(global_speed);
    }else
    if( c.equals("a") ){
      turn_left(global_speed);
    }else
    if( c.equals("d") ){
      turn_right(global_speed);
    }else
    if( c.equals("p") ){
      stop();
    }

    //TODO create motor state json serialization.
    Serial.println(" ");
  }
}
void set_speed_to_motors(int speed){
   global_speed = speed;
}

void forward(int speed){
  for(int i = 0 ; i < 4 ; i++){
    motor[i].setSpeed(speed);  
    motor[i].run(FORWARD);
    motor_states[i]++;
  }
}
void backward(int speed){
  for(int i = 0 ; i < 4 ; i++){
    motor[i].setSpeed(speed);  
    motor[i].run(BACKWARD);
  }
}
void turn_left(int speed){
  for(int i = 0 ; i < 4 ; i++)
    motor[i].setSpeed(speed);
  
  motor[0].run(BACKWARD);
  motor[2].run(BACKWARD);

  motor[1].run(FORWARD);
  motor[3].run(FORWARD);
}
void turn_right(int speed){
  for(int i = 0 ; i < 4 ; i++)
    motor[i].setSpeed(speed);
  
  motor[1].run(BACKWARD);
  motor[3].run(BACKWARD);

  motor[0].run(FORWARD);
  motor[2].run(FORWARD);
}

void stop(){
  for(int i = 0 ; i < 4 ; i++){
    motor[i].setSpeed(0);  
  }
}

#else  //=============== DEBUG MODE =====================

void setup() {
  Serial.begin(9600);           
  Serial.println("Started!");
  
  global_speed = DEFAULT_SPEED;

  for(int i = 0 ; i < 4 ; i++){
    motor[i] = AF_DCMotor(i+1);
    motor[i].setSpeed(global_speed);
    motor[i].run(RELEASE);
    motor[i].run(FORWARD);
  }  
  stop();
}

void loop() {
  if(Serial.available() > 0){

    static StaticJsonDocument<50> json_doc;
    const auto serial_data = deserializeJson(json_doc,Serial);

    int global_speed = json_doc["speed"];
    String c =  json_doc["direction"]; 

    Serial.println(global_speed);
    Serial.println(c);

    if( c.equals("w") ){
      forward(global_speed);
    }else
    if( c.equals("s") ){
      backward(global_speed);
    }else
    if( c.equals("a") ){
      turn_left(global_speed);
    }else
    if( c.equals("d") ){
      turn_right(global_speed);
    }else
    if( c.equals("p") ){
      stop();
    }else
    if( c.equals("t") ){
      test_motors();
    }
    Serial.println(" ");
  }
}
void set_speed_to_motors(int speed){
   global_speed = speed;
}

void forward(int speed){
  Serial.println("Moving forward!");
  for(int i = 0 ; i < 4 ; i++){
    motor[i].setSpeed(speed);  
    motor[i].run(FORWARD);
    motor_states[i]++;
  }
}
void backward(int speed){
  Serial.println("Moving backward!");
  for(int i = 0 ; i < 4 ; i++){
    motor[i].setSpeed(speed);  
    motor[i].run(BACKWARD);
  }
}
void turn_left(int speed){
  Serial.println("Turning left!");
  for(int i = 0 ; i < 4 ; i++)
    motor[i].setSpeed(speed);
  
  motor[0].run(BACKWARD);
  motor[2].run(BACKWARD);

  motor[1].run(FORWARD);
  motor[3].run(FORWARD);
}
void turn_right(int speed){
  Serial.println("Turning right!");
  for(int i = 0 ; i < 4 ; i++)
    motor[i].setSpeed(speed);
  
  motor[1].run(BACKWARD);
  motor[3].run(BACKWARD);

  motor[0].run(FORWARD);
  motor[2].run(FORWARD);
}

void stop(){
  Serial.println("Stopped");
  for(int i = 0 ; i < 4 ; i++){
    motor[i].setSpeed(0);  
  }
}
void test_motors(){
  uint8_t i,j;
    Serial.println("Motor test!");
  for(j=0; j < 4 ; j++){
    Serial.print("\n Testing");
    Serial.print("\n Current Motor:");
    Serial.print(j);

    for (i=0; i<255; i++) {
      motor[j].setSpeed(i);  
      delay(5);
    }
  
    for (i=255; i!=0; i--) {
      motor[j].setSpeed(i);  
      delay(5);
    }
  }
}
#endif
