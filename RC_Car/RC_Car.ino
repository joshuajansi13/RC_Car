// RC Car Code

#define in1 6 //L298n Motor Driver pins
#define in2 7
#define in3 5
#define in4 4
#define LED 13
#define ena 9
#define enb 3
int command; //Int to store app command state.
int Speed = 204; // 0 - 255.
int Speedsec;
int buttonState = 0;
int lastButtonState = 0;
int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will malfunction if this is higher than int Speed.
int brakeTime = 45;
int brkonoff = 1; //1 for the electronic braking system, 0 for normal.
void setup() {
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(ena, OUTPUT);
pinMode(enb, OUTPUT);
pinMode(LED, OUTPUT); //Set the LED pin.
Serial.begin(9600); //Set the baud rate to your Bluetooth module.
}
void forward() {
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
analogWrite(ena, 255);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
analogWrite(enb, 255);
}
void back() {
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
analogWrite(ena, 255);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
analogWrite(enb, 255);
}
void left() {
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
analogWrite(ena, 0);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
analogWrite(enb, 255);
}
void right() {
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
analogWrite(ena, 255);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
analogWrite(enb, 0);
}
void forwardleft() {
analogWrite(in1, Speedsec);
analogWrite(in3, Speed);
}
void forwardright() {
analogWrite(in1, Speed);
analogWrite(in3, Speedsec);
}
void backright() {
analogWrite(in2, Speed);
analogWrite(in4, Speedsec);
}
void backleft() {
analogWrite(in2, Speedsec);
analogWrite(in4, Speed);
}
void Stop() {
analogWrite(in1, 0);
analogWrite(in2, 0);
analogWrite(in3, 0);
analogWrite(in4, 0);
}
void brakeOn() {
//Here's the future use: an electronic braking system!
// read the pushbutton input pin:
buttonState = command;
// compare the buttonState to its previous state
if (buttonState != lastButtonState) {
// if the state has changed, increment the counter
if (buttonState == 'S') {
if (lastButtonState != buttonState) {
digitalWrite(in1, HIGH);
digitalWrite(in2, HIGH);
digitalWrite(in3, HIGH);
digitalWrite(in4, HIGH);
delay(brakeTime);
Stop();
}
}
// save the current state as the last state,
//for next time through the loop
lastButtonState = buttonState;
}
}
void brakeOff() {
}
void loop() {
if (Serial.available() > 0) {
command = Serial.read();
Stop(); //Initialize with motors stoped.
switch(command){
case 'a':
forward();
break;
case 'c':
back();
break;
case 'd':
left();
break;
case 'b':
right();
break;
case 'G':
forwardleft();
break;
case 'I':
forwardright();
break;
case 'H':
backleft();
break;
case 'J':
backright();
break;
case '0':
Speed = 100;
break;
case '1':
Speed = 140;
break;
case '2':
Speed = 153;
break;
case '3':
Speed = 165;
break;
case '4':
Speed = 178;
break;
case '5':
Speed = 191;
break;
case '6':
Speed = 204;
break;
case '7':
Speed = 216;
break;
case '8':
Speed = 229;
break;
case '9':
Speed = 242;
break;
case 'q':
Speed = 255;
break;
}
Speedsec = Turnradius;
if (brkonoff == 1) {
brakeOn();
} else {
brakeOff();
}
}
}