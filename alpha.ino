#include <SoftwareSerial.h>

//PROYECTO 142 BASTON PARA NO VIDENTES

SoftwareSerial BT(10, 11);

int button = 4;

int echoObstacle = 12;    //Pin digital  para el eco del sensor ultrasonico
int triggerObstacle = 13; //Pin digital  para el Trigger del sensor ultrasonico

int echoDepth = 7;    //Pin digital  para el eco del sensor ultrasonico
int triggerDepth = 8; //Pin digital  para el Trigger del sensor ultrasonico

float sound;

float distanceObstacle;

float distanceDepth;

String answer;
String msg;

void setup()
{
    BT.begin(38400);

    sound = (343); 
    pinMode(echoObstacle,INPUT);
    pinMode(triggerObstacle, OUTPUT);

    pinMode(echoDepth,INPUT);
    pinMode(triggerDepth, OUTPUT);

    Serial.begin(9600);

    pinMode(button, INPUT);
}

float calculateDistance(int trigger,int echo) {
    digitalWrite(trigger, LOW);
    delay(2);
    digitalWrite(trigger,HIGH);
    delay(10);
    digitalWrite(trigger,LOW);
    float time = pulseIn(echo,HIGH);
    return time*sound*0.0001 / 2.0;
}

void loop()
{   
    // Calculando distancia del sensor frontal
    distanceObstacle = calculateDistance(triggerObstacle, echoObstacle);

    // Calculando distancia del sensor inferior
    distanceDepth = calculateDistance(triggerDepth, echoDepth);

    // Serial.print(distanceObstacle);
    // Serial.print(" cm Distancia Obstaculo");
    // Serial.println();

    // Serial.print(distanceDepth);
    // Serial.print(" cm Distancia Suelo");
    // Serial.println();

    // Presiona el boton de emergencia
    if(digitalRead(button) == HIGH)
        Serial.println("Presionado");
        BT.print('1');

    // Obstaculo detectado
    if(distanceObstacle < 50) {
        BT.print('2');
    } else if (distanceObstacle < 100){
        BT.print('3');
    }
    // Precipitacion encontrada
    if(distanceDepth > 120) {
        BT.print('4');
    }
}



