#define SIZE_ARRAY 10

class BetaTemp{
  public:
    BetaTemp(uint8_t analog_pin, unsigned rseries, long int ntcnom = 100000, unsigned tempnom = 25, unsigned bcoeficient = 3950): analog_pin(analog_pin), ntcnom(ntcnom), tempnom(tempnom), bcoeficient(bcoeficient), rseries(rseries)
    {
      pinMode(analog_pin, INPUT);
      for(unsigned i=0; i < 10; ++i){
        temps[i] = get_temp();
      }
    }
    /******************************************************************/
    /*       Utiliza a equação do Fator Beta:                         */
    /*    Temperatura em Kelvin = T0 + (B / (ln(R/R0)))               */
    /*  onde, neste caso: T0 = 25C, B = 3820, R é a resistencia atual */
    /*  do NTC e R0 = 10k                                             */
    /******************************************************************/
    float get_temp(){
      float temp, resistance; 
      resistance = ((1023.0/analogRead(analog_pin) -1)*rseries);
      temp = resistance / ntcnom; // (R/Ro)
      temp = log(temp); // ln(R/Ro)
      temp /= bcoeficient; // 1/B * ln(R/Ro)
      temp += 1.0 / (tempnom + 273.15); // + (1/To)
      temp = 1.0 / temp; // Inverte o valor
      temp -=273.15; // Converte para Celsius
      return temp;
    };
    float get_mean_temp(){
      add_new_temp();
      return mean_temps();  
    }
  private: 
    float temps[SIZE_ARRAY];
    unsigned analog_pin;
    long int ntcnom;
    unsigned tempnom; 
    unsigned bcoeficient;
    unsigned rseries; 
    void add_new_temp(){
      for(unsigned i=0; i < SIZE_ARRAY-1; ++i){
        temps[i] = temps[i+1];
      }
      temps[9]=get_temp();
    }
    float mean_temps(){
      float mean(0);
      for(unsigned i=0; i < SIZE_ARRAY; ++i){
        mean += temps[i] / SIZE_ARRAY;
      }
      return mean;
    }
};
