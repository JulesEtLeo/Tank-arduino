//-- MOTEUR A --
int ENA=9; //Connecté à Arduino pin 9(sortie PWM)
int IN1=4; //Connecté à Arduino pin 4
int IN2=5; //Connecté à Arduino pin 5
int DROITE=12;
int GAUCHE=13;
int valDroite= 0;
int valGauche=0;
char test = "";
char action = "";
const int lanceur1 = 8;
const int lanceur2 = 2; 
#include <Servo.h>
Servo microservo;
Servo servoTourelleGD;
#include<SoftwareSerial.h>
#define RX 11
#define TX 12
SoftwareSerial BlueT(RX,TX);

//-- MOTEUR B --
int ENB=10; //Connecté à Arduino pin 10(Sortie PWM)
int IN3=6; //Connecté à Arduino pin 6
int IN4=7; //Connecté à Arduino pin 7

void setup() {
  Serial.begin(9600);
  BlueT.begin(9600);
  // put your setup code here, to run once:
  pinMode(lanceur1,OUTPUT);
  pinMode(lanceur2,OUTPUT);

  servoTourelleGD.attach(3);
  microservo.attach(13);
  pinMode(ENA,OUTPUT); // Configurer
  pinMode(ENB,OUTPUT); // les broches
  pinMode(IN1,OUTPUT); // comme sortie
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(DROITE,INPUT);
  pinMode(GAUCHE, INPUT);
  digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner
  digitalWrite(ENB,LOW);// Moteur B - Ne pas tourner

   // Direction du Moteur A
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  // Direction du Moteur B
  // NB: en sens inverse du moteur A
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  servoTourelleGD.write(90);
}

void avancer(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
}
void reculer(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
}
void tournerDroite(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,HIGH);
}
void tournerGauche(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,LOW);
}
void stopTank(){
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
}


void tirer(){
  digitalWrite(lanceur1,HIGH);
  digitalWrite(lanceur2,HIGH);
  delay(600);
  microservo.write(0);
  delay(600);
  microservo.write(180);
}
  
void stopTirer(){
  microservo.write(180);
  digitalWrite(lanceur1,LOW);
  digitalWrite(lanceur2,LOW);
    
}

void tourelleGauche(){
  servoTourelleGD.write(servoTourelleGD.read()+15);
   Serial.println(servoTourelleGD.read());
}  
  
void tourelleDroite(){
  if((servoTourelleGD.read()-15>10)){ // on vérifie que le moteur n'aille pas dans une position néfaste pour le moteur
    servoTourelleGD.write(servoTourelleGD.read()-15);
     Serial.println(servoTourelleGD.read());
  }
}
    
 

void loop() {
  if(BlueT.available()>0){
    //Serial.println(char(Serial.read())); // je ne la met pas car problème de lecture, affiche un caractère "�"
    action = char(BlueT.read());
    Serial.println("Bonjour, prêt pour les commandes bluetooth");
    Serial.println(action); // pour vérifier que chaque action est bien reçue
    if (action=='A'){
      avancer();
    }
    if (action=='B'){
      reculer();
    }
    if (action=='C'){
      tournerGauche();
    }
    if (action=='D'){
      tournerDroite();
    }
    if (action=='R'){
      tourelleGauche();
    }
    if (action=='L'){
      tourelleDroite();
    }
    if (action=='Z'){
      stopTank();
      stopTirer();
    }
    if (action=='F'){
      tirer();
    }
    if (action=='S'){
      stopTirer();
    }    
  }
  
  
}

