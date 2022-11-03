#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh;
std_msgs::Float32 cellreading;
ros::Publisher chatter("cellreading", &cellreading);

void messageCb(const std_msgs::Float32& toggle_msg){
  if(toggle_msg.data < 500)
    digitalWrite(8, HIGH);
  else
    digitalWrite(8, LOW);
}

ros::Subscriber<std_msgs::Float32> sub("cellreading", &messageCb );

int cellpin = 0;
int reading;
int ledpin;
int ledbrightness;

void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);
}
void loop() {
  // put your main code here, to run repeatedly:
  reading = analogRead(cellpin);
  Serial.print("Analog reading: ");
  Serial.println(reading);
  cellreading.data = reading;
  chatter.publish(&cellreading);
  nh.spinOnce();
  delay(100);

  

  delay(100);
}
