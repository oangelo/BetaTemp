class BetaTemp{
  public:
    BetaTemp(unsigned analog_pin, unsigned rseries, long int ntcnom = 100000, unsigned tempnom = 25, unsigned bcoeficient = 3950): analog_pin(analog_pin), ntcnom(ntcnom), tempnom(tempnom), bcoeficient(bcoeficient), rseries(rseries)
    {
      pinMode(analog_pin, INPUT);
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
  private: 
    unsigned analog_pin;
    long int ntcnom;
    unsigned tempnom; 
    unsigned bcoeficient;
    unsigned rseries; 
};
