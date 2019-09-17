//int PIN_NTC = A0;  

#define NTCNOM 100000 // Valor do termistor na temperatura nominal      
#define TEMPNOM 25  // Temp. nominal descrita no Manual 
#define NAMOSTRAS 5 // Número de amostragens para o calculo
#define BCOEFICIENTE 3950 // coeficiente Beta do NTC
#define RSERIE 10000 // valor do resistor em série    


void setup() 
{
   Serial.begin(9600);
   pinMode(13, OUTPUT);
   pinMode(12, OUTPUT);
   pinMode(A0, INPUT);
   pinMode(A1, INPUT);
}

float temp(int PIN_NTC){
   float temperatura, resistencia; // Variáveis auxiliares
 
   resistencia = ((1023.0/analogRead(PIN_NTC) -1)*RSERIE);  //  Calcula o valor atual da resistência = (1024/ADC - valor do NTC a 25°C)
   
 
   /******************************************************************/
   /*       Utiliza a equação do Fator Beta:                         */
   /*    Temperatura em Kelvin = T0 + (B / (ln(R/R0)))               */
   /*  onde, neste caso: T0 = 25C, B = 3820, R é a resistencia atual */
   /*  do NTC e R0 = 10k                                             */
   /******************************************************************/
 
   temperatura = resistencia / NTCNOM; // (R/Ro)
   temperatura = log(temperatura);   // ln(R/Ro)
   temperatura /= BCOEFICIENTE;  // 1/B * ln(R/Ro)
   temperatura += 1.0 / (TEMPNOM + 273.15); // + (1/To)
   temperatura = 1.0 / temperatura; // Inverte o valor
   temperatura -=273.15;                         // Converte para Celsius
   return temperatura;
  }

void loop() 
{
   float tp(temp(A0));
   delay(1000);
   float tm(temp(A1));

   Serial.print("Temperatura: "); 
   Serial.print((int)(tp));
   Serial.print(" - ");
   Serial.print((int)(tm));
   if(tp < 220){
      analogWrite(13, 70);
    }else{
      digitalWrite(13, LOW);
      }
    if(tm < 220){
      analogWrite(12, 160);
    }else{
      digitalWrite(12, LOW);
      }  
   Serial.print("\xC2\xB0"); // Envia o simbolo "°". Arduino IDE 1.8.3 utiliza formatação UTF-8
   Serial.println("C"); 
   
}
