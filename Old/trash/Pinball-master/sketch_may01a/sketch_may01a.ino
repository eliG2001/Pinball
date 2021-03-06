/* This is the code for the main microcontroler.
*
*
*This control jobs are:
* [x]coin counter
* [ ]fliper control
* [x]com with screen ardino
* [ ]games played
* [needs work]display intergation
* [ASAP]test code
//*
*
*/


//*****************************************************************************************************************
// Decare these varible to the corisopning Aurdino pins and wanted vaules for tuning game play exsperence


// constants won't change. They're used here to set pin numbers:
const int popBumperOneSwitch = A0; // the number of the switch pin
const int popBumperOne = 5; // the number of the popBumper pin
//const int popBumperOneLED = 14; // the number of the popBumperLED pin

const int popBumperTwoSwitch = A1; // the number of the switch pin
const int popBumperTwo = 6; // the number of the popBumper pin
//const int popBumperTwoLED = 15; // the number of the popBumperLED pin

const int popBumperThreeSwitch = A2; // the number of the switch pin
const int popBumperThree = 7; // the number of the popBumper pin
//const int popBumperThreeLED = 16; // the number of the popBumperLED pin

const int flipperRightHoldSwitch = A3; // the number of the switch pin
const int flipperRightHoldCoil = 8; //

const int flipperRightPowerSwitch = A4; //
const int flipperRightPowerCoil = 9; // the number of the flipper pin

const int flipperLeftHoldSwitch = A5; // the number of the switch pin
const int flipperLeftHoldCoil = 10; //

const int flipperLeftPowerSwitch = 2; //
const int flipperLeftPowerCoil = 11; // the number of the flipper pin

const int slingshotOneSwitch = 3; // the number of the switch pin
const int slingshotOne = 12; // the number of the slingshot pin
//const int slingshotOneLED = 17; // the number of the slingshotLED pin

const int slingshotTwoSwitch = 4; // the number of the switch pin
const int slingshotTwo = 13; // the number of the slingshot pin
//const int slingshotLeftLED = 18; // the number of the slingshotLED pin

const int gatePin = 103;
const int openTime = 1;

const int coinDetect = 100;
const int ballDeathSwith = 101;
const int startButton = 102;

const int newBalls = 5; //the number of new ball per pament
const int minCoinsRequerd = 2; // minnum coins requard to get balls

//points
const int pointsForPopBumper = 10;
const int pointsForSlingShot = 10;
const int pointsForRollOver = 10;

//free balls
const int freeBalls = 1;
const int freeBallPoints = 2000;

//***************************************************************************************************************

// PUBLIC VARs and setup

int scoreRecord;
int score;// the score for a inivial game
int coinsCounted; // the total coin in the maching
int coins; //
int ballsRemaining;
char message[] = "0Coins";
char imputMessage;
int freeBallPointsTracker = 0;


bool gameState;


//int money;

void setup() {
    // initialize the LED pin as an output:
    pinMode(popBumperOne, OUTPUT);
    pinMode(popBumperTwo, OUTPUT);
    pinMode(popBumperThree, OUTPUT);

    pinMode(flipperRightPowerCoil, OUTPUT);
    pinMode(flipperRightHoldCoil, OUTPUT);

    pinMode(flipperLeftPowerCoil, OUTPUT);
    pinMode(flipperLeftHoldCoil, OUTPUT);

    pinMode(slingshotOne, OUTPUT);
    pinMode(slingshotTwo, OUTPUT);

    // initialize the pushbutton pin as an input:
    pinMode(popBumperOneSwitch, INPUT);
    pinMode(popBumperTwoSwitch, INPUT);
    pinMode(popBumperOneSwitch, INPUT);

    pinMode(flipperRightHoldSwitch, INPUT);
    pinMode(flipperLeftHoldSwitch, INPUT);
    pinMode(flipperRightPowerSwitch, INPUT);
    pinMode(flipperLeftPowerSwitch, INPUT);

    pinMode(slingshotOneSwitch, INPUT);
    pinMode(slingshotTwoSwitch, INPUT);

    pinMode(coinDetect, INPUT);
    pinMode(startButton, INPUT);
    pinMode(ballDeathSwith, INPUT);

    //initialize Serial comuticion
    Serial.begin(9600); // start serial communication at 9600bps with USB port
    //Serial1.begin(9600); // start serial1 communication at 9600bps with screen control aduino

    Serial.flush(); // flush communication
    //Serial1.flush(); // flush communication
}


void loop(){


    ElectronicsLoop();

    //ToDisplay(message);

    delay(5);
}



//*********************************************************************************************************


//******************************************************************************************************





// ELECTRONICS CONTROL






void ElectronicsLoop(){

    SlingshotControl(slingshotOne, slingshotOneSwitch, pointsForSlingShot);
    SlingshotControl(slingshotTwo, slingshotTwoSwitch, pointsForSlingShot);
    PopBumperControl(popBumperOne, popBumperOneSwitch, pointsForPopBumper);
    PopBumperControl(popBumperTwo, popBumperTwoSwitch, pointsForPopBumper);
    PopBumperControl(popBumperThree, popBumperThreeSwitch, pointsForPopBumper);
    FlipperControl(flipperLeftPowerCoil, flipperLeftHoldCoil, flipperLeftPowerSwitch, flipperLeftHoldSwitch);
    FlipperControl(flipperRightPowerCoil, flipperRightHoldCoil, flipperRightPowerSwitch, flipperRightHoldSwitch);
}

void BallGateControl (bool _open){ //puts ball into play NOT DONE
    if (_open){
        //open
        //digitalWrite(gatePin, HIGH);
        Serial.println("RUNNING: gate open");
    } else {
        Serial.println("RUNNING: gate closed");
        //close
    }
}

void PopBumperControl(int _popBumper, int _popBumperSwitch, int _points){

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(_popBumperSwitch);
    
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        Serial.println("PopBumperControl");
        // turn LED on:
        
        digitalWrite(_popBumper, HIGH);
        delay(40);
        digitalWrite(_popBumper, LOW);
    } else {
        // turn LED off:
        digitalWrite(_popBumper, LOW);
    }
}
/*
void UseLED(int _ledPin,  int _mode){//NOT DONE
    bool LEDState;

    if (_mode == 0){// LED off
        LEDState = true;
    } else if (_mode == 1){//LED on
        LEDState = false;
    } else if (_mode == 2) {// LED bink DO NOT USE
        digitalWrite(_ledPin, HIGH);
    }else if (_mode == 3){
        digitalWrite(_ledPin, HIGH);
    }

    if (LEDState){
        digitalWrite(_ledPin, HIGH);
    }else{
        digitalWrite(_ledPin, LOW);
    }
}
*/
void FlipperControl(int _flipperPowerCoil, int _flipperHoldCoil, int _flipperPowerSwitch, int _flipperHoldSwitch) {

    int buttonState = 1;
    int button2State = 1;
    // read the state of the pushbutton value:
    buttonState = digitalRead(_flipperPowerSwitch);
    button2State = digitalRead(_flipperHoldSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH && button2State == LOW) {
        Serial.print("RUNNING: FlipperControl  ");
        digitalWrite(_flipperHoldCoil, HIGH);
        digitalWrite(_flipperPowerCoil, HIGH);
    } else if (buttonState == HIGH && button2State == HIGH){
        digitalWrite(_flipperPowerCoil, LOW);
    } else {
        // turn LED off:
        digitalWrite(_flipperPowerCoil, LOW);
        digitalWrite(_flipperHoldCoil, LOW);
    }
}

void SlingshotControl(int _slingshot, int _slingshotSwitch, int _points) {//NOT DONE

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(_slingshotSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        Serial.print("RUNNING: SlingshotControl  ");
        
        digitalWrite(_slingshot, HIGH);
        delay(40);
        digitalWrite(_slingshot, LOW);
    } else {
        // turn LED off:
        digitalWrite(_slingshot, LOW);
    }
}


















/*
// this has been cleaned up
void PopBumperOneControl() {

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(popBumperOneSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
    // turn LED on:
        digitalWrite(popBumperOne, HIGH);
        AddScore(10);
        delay(40);
        digitalWrite(popBumperOne, LOW);
    } else {
        // turn LED off:
        digitalWrite(popBumperOne, LOW);
    }
}

void PopBumperTwoControl() {

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(popBumperTwoSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        digitalWrite(popBumperTwo, HIGH);
        delay(40);
        digitalWrite(popBumperTwo, LOW);
    } else {
        // turn LED off:
        digitalWrite(popBumperTwo, LOW);
    }
}

void PopBumperThreeControl() {

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(popBumperThreeSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        AddScore(pointsForSlingShot);
        digitalWrite(popBumperThree, HIGH);
        delay(40);
        digitalWrite(popBumperThree, LOW);
    } else {
        // turn LED off:
        digitalWrite(popBumperThree, LOW);
    }
}
void FlipperRightControl() {

    int buttonState = 1;
    int button2State = 1;
    // read the state of the pushbutton value:
    buttonState = digitalRead(flipperRightPowerSwitch);
    button2State = digitalRead(flipperRightHoldSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH && button2State == LOW) {

        digitalWrite(flipperRightHoldCoil, HIGH);
        digitalWrite(flipperRightPowerCoil, HIGH);
    } else if (buttonState == HIGH && button2State == HIGH){
        digitalWrite(flipperRightPowerCoil, LOW);
    } else {
        // turn LED off:
        digitalWrite(flipperRightPowerCoil, LOW);
        digitalWrite(flipperRightHoldCoil, LOW);
    }
}

void FlipperLeftControl() {

    int buttonState = 1;
    int button2State = 1;
    // read the state of the pushbutton value:
    buttonState = digitalRead(flipperLeftPowerSwitch);
    button2State = digitalRead(flipperLeftHoldSwitch);

    
    if (buttonState == HIGH && button2State == LOW) {// check if the pushbutton is pressed. If it is, the buttonState is HIGH:
        digitalWrite(flipperLeftHoldCoil, HIGH);
        digitalWrite(flipperLeftPowerCoil, HIGH);
    } else if (buttonState == HIGH && button2State == HIGH){
        digitalWrite(flipperLeftPowerCoil, LOW);
    } else {
        // turn LED off:
        digitalWrite(flipperLeftPowerCoil, LOW);
        digitalWrite(flipperLeftHoldCoil, LOW);
    }
}
void slingshotOneControl() {

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(slingshotOneSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        AddScore(pointsForSlingShot);
        digitalWrite(slingshotOne, HIGH);
        delay(40);
        digitalWrite(slingshotOne, LOW);
    } else {
        // turn LED off:
        digitalWrite(slingshotOne, LOW);
    }
}

void SlingshotLeftControl() {

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(slingshotTwoSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        AddScore(pointsForSlingShot);
        digitalWrite(slingshotLeft, HIGH);
        delay(40);
        digitalWrite(slingshotLeft, LOW);
    } else {
        // turn LED off:
        digitalWrite(slingshotLeft, LOW);
    }
}
*/
