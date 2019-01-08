

#include <Servo.h>
#include <AFMotor.h>

#define LINE_BUFFER_LENGTH 512
char STEP = MICROSTEP ;
const int arriba= 70;
const int abajo = 40;
const int plumaServoPin =10 ;
const int stepsPerRevolution = 24; 


Servo plumaServo;  


AF_Stepper myStepperY(stepsPerRevolution,1);            
AF_Stepper myStepperX(stepsPerRevolution,2);  


struct point { 
  float x; 
  float y; 
  float z; 
};
struct point actuatorPos;
float StepInc = 1;
int StepDelay = 3;
int LineDelay =0;
int penDelay = 50;
float pasosPorMillimetroX = 100.0;
float pasosPorMillimetroY = 100.0;
float Xmin = 0;
float Xmax = 40;
float Ymin = 0;
float Ymax = 40;
float Zmin = 0;
float Zmax = 1;
float Xpos = Xmin;
float Ypos = Ymin;
float Zpos = Zmax; 







void setup() {

  
  Serial.begin( 9600 );
  
  plumaServo.attach(plumaServoPin);
  plumaServo.write(arriba);
  delay(100);


  myStepperX.setSpeed(200);

  myStepperY.setSpeed(200);  
  
  Serial.println("CNC Vivia y lista para echarle watts");

}

void loop() 
{
  
  delay(100);
  char line[ LINE_BUFFER_LENGTH ];
  char c;
  int lineIndex;
  bool lineIsComment, lineSemiColon;

  lineIndex = 0;
  lineSemiColon = false;
  lineIsComment = false;

  while (1) {


    while ( Serial.available()>0 ) {
      c = Serial.read();
      if (( c == '\n') || (c == '\r') ) {             
        if ( lineIndex > 0 ) {                      
          line[ lineIndex ] = '\0';                  
         
          }
          
        } 
        else { 
         
        }
        lineIsComment = false;
        lineSemiColon = false;
        Serial.println("ok");    
      } 
    
     
        if ( (lineIsComment) || (lineSemiColon) ) {   
          if ( c == ')' )  lineIsComment = false;     
        
        else {
          if ( c <= ' ' ) {                           
          } 
          else if ( c == '/' ) {                    
          } 
          else if ( c == '(' ) {                    
            lineIsComment = true;
          } 
          else if ( c == ';' ) {
            lineSemiColon = true;
          } 
          else if ( lineIndex >= LINE_BUFFER_LENGTH-1 ) {
           
            lineIsComment = false;
            lineSemiColon = false;
          } 
          else if ( c >= 'a' && c <= 'z' ) {        
            line[ lineIndex++ ] = c-'a'+'A';
          } 
          else {
            line[ lineIndex++ ] = c;
          }
        }
      }
    }
  }


void processIncomingLine( char* line, int charNB ) {
  int currentIndex = 0;
  char buffer[ 64 ];                                 
  struct point newPos;

  newPos.x = 0.0;
  newPos.y = 0.0;



  while( currentIndex < charNB ) {
    switch ( line[ currentIndex++ ] ) {              
    case 'U':
     arriba1(); 
      break;
    case 'D':
      arriba; 
      break;
    case 'G':
      buffer[0] = line[ currentIndex++ ];          
    
      buffer[1] = '\0';

      switch ( atoi( buffer ) ){                  
      case 0:                                   
      case 1:
    
        char* indexX = strchr( line+currentIndex, 'X' ); 
        char* indexY = strchr( line+currentIndex, 'Y' );
        if ( indexY <= 0 ) {
          newPos.x = atof( indexX + 1); 
          newPos.y = actuatorPos.y;
        } 
        else if ( indexX <= 0 ) {
          newPos.y = atof( indexY + 1);
          newPos.x = actuatorPos.x;
        } 
        else {
          newPos.y = atof( indexY + 1);
          indexY = '\0';
          newPos.x = atof( indexX + 1);
        }
        drawLine(newPos.x, newPos.y );
      
        actuatorPos.x = newPos.x;
        actuatorPos.y = newPos.y;
        break;
      }
      break;
    case 'M':
      buffer[0] = line[ currentIndex++ ];       
      buffer[1] = line[ currentIndex++ ];
      buffer[2] = line[ currentIndex++ ];
      buffer[3] = '\0';
      switch ( atoi( buffer ) ){
      case 300:
        {
          char* indexS = strchr( line+currentIndex, 'S' );
          float Spos = atof( indexS + 1);
       
          if (Spos == 30) { 
            arriba1(); 
          }
          
          break;
        }
      case 114:                           
        Serial.print( "posicion : X = " );
        Serial.print( actuatorPos.x );
        Serial.print( "  -  Y = " );
        Serial.println( actuatorPos.y );
        break;
      default:
        Serial.print( "comando no reconocido : M");
        Serial.println( buffer );
      }
    }
  }



}


void drawLine(float x1, float y1) {

  if (x1 >= Xmax) { 
    x1 = Xmax; 
  }
  if (x1 <= Xmin) { 
    x1 = Xmin; 
  }
  if (y1 >= Ymax) { 
    y1 = Ymax; 
  }
  if (y1 <= Ymin) { 
    y1 = Ymin; 
  }
  x1 = (int)(x1*pasosPorMillimetroX);
  y1 = (int)(y1*pasosPorMillimetroY);
  float x0 = Xpos;
  float y0 = Ypos;

  
  long dx = abs(x1-x0);
  long dy = abs(y1-y0);
  int sx = x0<x1 ? StepInc : -StepInc;
  int sy = y0<y1 ? StepInc : -StepInc;

  long i;
  long over = 0;

  if (dx > dy) {
    for (i=0; i<dx; ++i) {
      myStepperX.onestep(sx,STEP);
      over+=dy;
      if (over>=dx) {
        over-=dx;
        myStepperY.onestep(sy,STEP);
      }
    delay(StepDelay);
    }
  }
  else {
    for (i=0; i<dy; ++i) {
      myStepperY.onestep(sy,STEP);
      over+=dx;
      if (over>=dy) {
        over-=dy;
        myStepperX.onestep(sx,STEP);
      }
      delay(StepDelay);
    }    
  }
  delay(LineDelay);
  Xpos = x1;
  Ypos = y1;
}


void arriba1() { 
  plumaServo.write(arriba); 
  delay(penDelay); 
  Zpos=Zmax; 
  digitalWrite(15, LOW);
    digitalWrite(16, HIGH);
  
    
  } 


void abajo1() { 
  plumaServo.write(abajo); 
  delay(penDelay); 
  Zpos=Zmin; 
  digitalWrite(15, HIGH);
    digitalWrite(16, LOW);
 
    
    
  } 

