// Pines de sensores
#define SLD A1 // Sensor de línea derecho
#define SIFD A2 // Sensor infrarrojo derecho
#define SIFM A3 // Sensor infrarrojo medio
#define SIFI A4 // Sensor infrarrojo izquierdo
#define SLI A5 // Sensor de línea izquierdo


// Pines motores
// Motor derecho
#define PWMD 3 // PWM del motor derecho
#define MI1 4//adelante    
#define MI2 5//atras
// Motor izquierdo
#define PWMI 6 // PWM del motor izquierdo
#define MD1 7//adelante
#define MD2 8//atras

// Pines externos
#define MI 2// Modulo de arranque
// Variables globales
bool  IFD=false; // Infrarrojo derecho
bool  IFM=false; // Infrarrojo medio
bool  IFI=false; // Infrarrojo izquierdo
bool  LD=0; // Sensor línea derecho
bool  LI=0; // Sensor línea izquierdo
int   MIS=0; // Estado del modulo de arranque
int REF=100;

void Sensores(){
  // Lectura de sensores infrarrojos
  IFD=digitalRead(SIFD); 
  IFM=digitalRead(SIFM);
  IFI=digitalRead(SIFI);
  int RLD =analogRead(SLD); 
  int RLI =analogRead(SLI);
  
  // Conversión de valores analógico a booleano para sensores de línea
  
  if (RLD < REF){
    LD=0;
    }
  else{
    LD=1;
      }
      
  if (RLI < REF){
    LI=0;
    }
  else{
    LI=1;
      }
  }


void setup() {
  //Sensores
  pinMode(SIFD,INPUT);
  pinMode(SIFM,INPUT);
  pinMode(SIFI,INPUT);
  pinMode(SLI,INPUT);
  pinMode(SLD,INPUT);
  //Motores
  pinMode(MD1,OUTPUT);
  pinMode(MD2,OUTPUT);
  pinMode(MI1,OUTPUT);
  pinMode(MI2,OUTPUT);
  //Extras
  pinMode(MI,INPUT);
  // delay(5000);
  // Interrucpión para dar fin
  attachInterrupt(digitalPinToInterrupt(MI),Paro,LOW);
  // Condición de inicio
 while (MIS==0){
   MIS=digitalRead(MI);
             }
  
}
void Embestida(){
  analogWrite(PWMD, 255);
  digitalWrite(MD2,HIGH);
  digitalWrite(MD1,LOW);
  analogWrite(PWMI, 255);
  digitalWrite(MI1,HIGH);
  digitalWrite(MI2,LOW);
  }
void Adelante(){
  analogWrite(PWMD, 120);
  digitalWrite(MD2,HIGH);
  digitalWrite(MD1,LOW);
  analogWrite(PWMI, 120);
  digitalWrite(MI1,HIGH);
  digitalWrite(MI2,LOW);
  }
void Atras(){
  analogWrite(PWMD, 255);
  digitalWrite(MD2,LOW);
  digitalWrite(MD1,HIGH); 
  analogWrite(PWMI, 255);
  digitalWrite(MI1,LOW);
  digitalWrite(MI2,HIGH);
  }
void Izquierda(){
  analogWrite(PWMD, 200);
  digitalWrite(MD2,HIGH);
  digitalWrite(MD1,LOW);
  analogWrite(PWMI, 200);
  digitalWrite(MI1,LOW);
  digitalWrite(MI2,HIGH);
  }
void Derecha(){
  analogWrite(PWMD, 200);
  digitalWrite(MD1,HIGH);
  digitalWrite(MD2,LOW);
  analogWrite(PWMI, 200);
  digitalWrite(MI1,HIGH);
  digitalWrite(MI2,LOW);
  }
void Paro(){
  analogWrite(PWMD, 0);
  digitalWrite(MD1,LOW);
  digitalWrite(MD2,LOW);
  analogWrite(PWMI,0);
  digitalWrite(MI1,LOW);
  digitalWrite(MI2,LOW);
  }
  
void loop() {
  if (LD==0 && LI==0){    // 0 es blanco
    if(IFD==1 && IFI==0 && IFM==0){
      Derecha();
      delay(30);
      Sensores();  
      }
    else if(IFD==0 && IFI==1 && IFM==0){
        Izquierda();
        delay(30);
        Sensores();  
      }
    else{
        Atras();
        delay(100);
        Derecha();
        delay(100);
        Sensores();  
        }
    }

    if (LD==0 && LI==1){
      if(IFD==1 && IFI==0 && IFM==0){
        Derecha();
        delay(30);
        Sensores();  
        }
      else if(IFD==0 && IFI==1 && IFM==0){
        Izquierda();
        delay(30);
        Sensores();  
       }
      else{
        Izquierda();
        Sensores();
      }
    }
    
    if (LD==1 && LI==0){
      if(IFD==1 && IFI==0 && IFM==0){
        Derecha();
        delay(30);
        Sensores();  
        }
        else if(IFD==0 && IFI==1 && IFM==0){
          Izquierda();
          delay(30);
          Sensores();  
          }
          else{
            Derecha();
            Sensores();
            }
    }

    if (LD==1 && LI==1){
      if(IFD==0 && IFI==0 && IFM==1){
        Embestida();
        Sensores();
        }
        else if(IFD==0 && IFI==1 && IFM==0){
          Izquierda();
          delay(30);
          Sensores();
          }
        else if(IFD==1 && IFI==0 && IFM==0){
          Derecha();
          delay(30);
          Sensores();
          }
          else{
            Adelante();
            Sensores();
        }
    }
    }
