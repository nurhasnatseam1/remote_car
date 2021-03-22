
int md_inp_1=11;
int md_inp_2=10;
int md_inp_3=9;
int md_inp_4=8;


char command = 'S';




boolean isActing =false;
long timer;
const long TIME_OUT=150;
const int lowest_velocity = 25;
int moving_velocity =255;



void setup() {
  // put your setup code here, to run once:
  setPinModeOutput();
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    processResult();
  }

  if (isActing && (millis()-timer >=150)){
    stop();
    isActing=false;
    }
    
}

void setPinModeOutput(){
  pinMode(md_inp_1,OUTPUT);
  pinMode(md_inp_2,OUTPUT);
  pinMode(md_inp_3,OUTPUT);
  pinMode(md_inp_4,OUTPUT);  
};

void stopLeft(){
  digitalWrite(md_inp_1,LOW);
  digitalWrite(md_inp_2,LOW);
  }
void stopRight(){
  digitalWrite(md_inp_3,LOW);
  digitalWrite(md_inp_4,LOW);
  }
void stop(){
  stopRight();
  stopLeft();
  }


void rmClock(float rightClockVelocity){
  analogWrite(md_inp_3,rightClockVelocity);
  analogWrite(md_inp_4,0);
  };
void rmAntiClock(float rightAntiClockVelocity){
  analogWrite(md_inp_3,0);
  analogWrite(md_inp_4,rightAntiClockVelocity);
  };

void lmClock(float leftClockVelocity){
  analogWrite(md_inp_1,leftClockVelocity);
  analogWrite(md_inp_2,0);
  };
void lmAntiClock(float leftAntiClockVelocity){
  digitalWrite(md_inp_1,0);
  digitalWrite(md_inp_2,leftAntiClockVelocity);
  };

void moveBackward(float leftAntiClockVelocity,float rightAntiClockVelocity){
  lmAntiClock(leftAntiClockVelocity);
  rmAntiClock(rightAntiClockVelocity);
  }




void moveForward(float leftClockVelocity, float rightClockVelocity){
  lmClock(leftClockVelocity);
  rmClock(rightClockVelocity);
  }


void turnRight(float leftClockVelocity,float rightAntiClockVelocity){
  lmClock(leftClockVelocity);
  rmAntiClock(rightAntiClockVelocity);
  }

void turnLeft(float leftAntiClockVelocity,float rightClockVelocity){
  lmClock(leftAntiClockVelocity);
  rmClock(rightClockVelocity);
  }



void motorsWrite(float leftVelocity,float rightVelocity){
  boolean leftClockWise = leftVelocity >0;
  boolean rightClockWise= rightVelocity > 0;
  if(leftClockWise && rightClockWise){
    moveForward(leftVelocity,rightVelocity);
  }else if(!leftClockWise && !rightClockWise){
    leftVelocity *= -1;
    rightVelocity *= -1;
    moveBackward(leftVelocity,rightVelocity);
  }else if(leftClockWise && !rightClockWise){
    rightVelocity *=-1;
    turnRight(leftVelocity,rightVelocity);
  }else if (!leftClockWise && rightClockWise){
    leftVelocity *=-1;
    turnLeft(leftVelocity,rightVelocity);
  }
  
  }




void changeAction (float directionLeft,float directionRight){
  motorsWrite(moving_velocity * directionLeft,moving_velocity*directionRight);
  timer = millis();
  isActing =true;    
  }

  
void processResult(){
  char command = Serial.read();
  switch(command){
    case 'F':
      changeAction(1,1);
      break;
    case 'B':
      changeAction(-1,-1);
      break;
    case 'L':
      changeAction(-.5,.5);
      break;
    case 'R':
      changeAction(.5,-.5);
      break;
    case 'G':
      changeAction(.8,1); //forward left
      break;
    case 'I':
      changeAction(1,.8);//forward right
      break;
    case 'H':
      changeAction(-.8,-1);//Backward left
      break;
    case 'j':
      changeAction(-1,-.8); //Backward right
      break;
    case 'x' :
      stop();
      break;
    case '1':
      moving_velocity = lowest_velocity;
      break;
    case '2':
      moving_velocity = lowest_velocity *2;
      break;
    case '3':
      moving_velocity = lowest_velocity *3;
      break;
    case '4':
      moving_velocity = lowest_velocity *4;
      break;
    case '5':
      moving_velocity = lowest_velocity *5;
      break;
    case '6':
      moving_velocity = lowest_velocity * 6;
      break;
    case '7':
      moving_velocity  = lowest_velocity *7;
      break;
    case '8':
      moving_velocity = lowest_velocity *8;
      break;
    case '9':
      moving_velocity = lowest_velocity *9;
      break;
    case 'q':
      moving_velocity = 255;
      
    }
  }
