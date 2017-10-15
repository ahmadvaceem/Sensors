#include <math.h>

int datArray[150][2] = {
  {1, -87},
  {10, -60},
  {20, -50},
  {30, -44},
  {40, -40},
  {50, -36},
  {60, -33},
  {70, -30},
  {80, -28},
  {90, -25},
  {100, -23},
  {110, -21},
  {120, -19},
  {130, -18},
  {140, -16},
  {150, -15},
  {160, -13},
  {170, -12},
  {180, -10},
  {190, -9},
  {200, -8},
  {210, -6},
  {220, -5},
  {230, -4},
  {240, -3},
  {250, -2},
  {260, 0},
  {270, 1},
  {280, 2},
  {290, 3},
  {300, 4},
  {310, 5},
  {320, 6},
  {330, 7},
  {340, 8},
  {350, 9},
  {360, 10},
  {370, 11},
  {380, 12},
  {390, 13},
  {400, 14},
  {410, 15},
  {420, 16},
  {430, 17},
  {440, 18},
  {450, 19},
  {460, 20},
  {470, 21},
  {480, 22},
  {490, 23},
  {500, 24},
  {510, 25},
  {520, 26},
  {530, 27},
  {540, 28},
  {550, 29},
  {560, 30},
  {570, 31},
  {580, 32},
  {590, 33},
  {600, 34},
  {610, 35},
  {620, 37},
  {630, 38},
  {640, 39},
  {650, 40},
  {660, 41},
  {670, 42},
  {680, 44},
  {690, 45},
  {700, 46},
  {710, 48},
  {720, 49},
  {730, 51},
  {740, 52},
  {750, 54},
  {760, 55},
  {770, 57},
  {780, 58},
  {790, 60},
  {800, 62},
  {810, 64},
  {820, 66},
  {830, 68},
  {840, 70},
  {850, 72},
  {860, 75},
  {870, 77},
  {880, 80},
  {890, 83},
  {900, 87},
  {910, 91},
  {920, 95},
  {930, 99},
  {940, 104},
  {950, 110},
  {960, 117},
  {970, 125},
  {980, 135},
  {990, 148},
  {1000, 168},
  {1010, 201},
  {1020, 301},
  {1023, 475}
};

int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float b = 3435;
float t0 = 273.15;
float t1 = 0;
float adc;
float logR, T, R, Tc, Tf, Rth;
float logR2, R2, temp;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
float error = 0;
void setup() {
  Serial.begin(9600);
}
float Calculation(float adc)
{
  Vo = Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  temp = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  temp = temp - 273.15;
  R = (1024 / adc - 1);
  logR = log(R);
  T = 1.0 / (1 / (temp + t0) + 1 / b * logR);
  Tc = T - 273.15;

  //Tf = (Tc * 9.0)/ 5.0 + 32.0;
  //Rth = exp(b * (1/T - 1/(Vo+t0)));

  return T;
}
float CalculationLinearly(int adc)
{
  float y = 0;

  if (0 < adc && adc < 40)
    y = (1.4014 * adc) - 81.977;
  else if ( 40 <= adc && adc < 150)
    y = (0.2232 * adc) - 46.565;
  else if (150 <= adc && adc < 800)
    y = (0.1097 * adc) - 30.034;
  else if (800 <= adc && adc < 900)
    y = (0.2468 * adc) - 136.4;
  else if (900 <= adc && adc < 980)
    y = (0.5821 * adc) - 440.36;
  else if (980 <= adc && adc < 1023)
    y = (6.4596 * adc) - 6246.3;
  else
    Serial.println("  Error ");
  return y;
}
int get_temp(int adc)
{
  int i = 0;
  while (datArray[i][0] < adc)
  {
    i++;
  }
  return (datArray[i][1]);
}

void loop()
{
  if (adc < 1024)
    for (adc = 0; adc < 1024; adc = adc + 10)
    {
        
      if (adc == 0) {
        Serial.print(adc + 1); Serial.print( " ADC : "); Serial.print( Calculation(adc + 1)); Serial.print(" K Temperature : "); Serial.print(get_temp(adc+1)); Serial.print( " ExcelTemp : "); Serial.print(Tc);
      }
      else {
        Serial.print(adc); Serial.print( " ADC : "); Serial.print( Calculation(adc)); Serial.print(" K Temperature : "); Serial.print(get_temp(adc)); Serial.print( " ExcelTemp : ");Serial.print(Tc);
      }
      Serial.print(" Calculated Tc  : ");
      Serial.print(CalculationLinearly(adc));
      error = (CalculationLinearly(adc) - Tc);
      Serial.print(" LinearlyCalculated Tc  : "); Serial.print(error); Serial.print( " Error ");
      Serial.println();
      Serial.println();
      delay(100);
    }
}

