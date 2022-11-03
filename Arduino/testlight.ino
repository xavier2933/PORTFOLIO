#include <ros.h>  //included required ROS stuff
#include <std_msgs/Float32.h>

ros::NodeHandle nh; //make the node , messages
std_msgs::Float32 cellreading;
ros::Publisher chatter("cellreading", &cellreading); //Publisher

void messageCb(const std_msgs::Float32& toggle_msg){ //This is how I controlled the LED
  if(toggle_msg.data < 500)
    digitalWrite(8, HIGH);
  else
    digitalWrite(8, LOW);
}

ros::Subscriber<std_msgs::Float32> sub("cellreading", &messageCb ); //Subscribe to publisher

int cellpin = 0;
int reading;
int ledpin;
int ledbrightness;

void setup() {
  pinMode(8, OUTPUT); //output, start serial, make node, subscriber, advertise this
  Serial.begin(9600);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);
}
void loop() {
  reading = analogRead(cellpin); //read, print
  Serial.print("Analog reading: ");
  Serial.println(reading);
  cellreading.data = reading;
  chatter.publish(&cellreading);
  nh.spinOnce();
  delay(100);

  

  delay(100);
}
