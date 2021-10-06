//PROYECTO 142 BASTON PARA NO VIDENTES

int led = 1;      //led 
int sensor = A0;  //sensor de temperatura
int buzzer = 9;   //buzzer
int echo = 12;    //Pin digital  para el eco del sensor ultrasonico
int trigger = 13; //Pin digital  para el Trigger del sensor ultrasonico
int vibrador = 6;
int motor = 3; 
float sonido;
float distancia;
float tiempo;
float temperatura;
int temp;

void setup()
{
  pinMode(motor, OUTPUT);     //salida
  pinMode(sensor,INPUT);      //entrada
  pinMode(buzzer, OUTPUT);    //salida
  pinMode(led, OUTPUT);       //salida
  pinMode(echo,INPUT);        //entrada
  pinMode(trigger, OUTPUT);   //salida
  pinMode(vibrador, OUTPUT);  //salida
  Serial.begin(9600);         //inicia el motor seria
  sonido=(343);               //velocidad del sonido en m/s
  digitalWrite(vibrador,LOW);
  tone(buzzer,LOW);
  digitalWrite(led,HIGH);
}

void loop()
{ 
  //conversion  del sensor de temperatura
  temp= analogRead(sensor);
  temperatura=((temp*0.488)-50);  //grados centigrados
  
  if(temperatura >15)
    digitalWrite(motor,HIGH); 
  
  digitalWrite(trigger, LOW);
  delay(2);
  digitalWrite(trigger,HIGH);
  delay(10);
  digitalWrite(trigger,LOW);
  
  tiempo = pulseIn(echo,HIGH);
  distancia = tiempo*sonido*0.0001 / 2.0;  // conversion a centimetros
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  
  analogWrite(vibrador,measureDistanceVibrator(distancia));
  tone(buzzer, measureDistanceTone(distancia),200);
  delay(50);
}
int measureDistanceVibrator(int distance) {
  int intensity = 0;
  if(distance < 10) {
    intensity = 255;
  } else if (distance < 20) {
    intensity = 204;
  } else if (distance < 40) {
    intensity = 102;
  } else if (distance < 50) {
    intensity = 51;
  }
  return intensity;
}
int measureDistanceTone(int distance) {
  int tone = 0;
  if(distance < 10) {
    tone = 3000;
  } else if (distance < 20) {
    tone = 2000;
  } else if (distance < 30) {
    tone = 1000;
  }
  return tone;
}
