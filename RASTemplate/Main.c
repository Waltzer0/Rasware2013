#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/motor.h>
#include <RASLib/inc/adc.h>
#include <RASDemo/RASDemo.h>
// Blink the LED to show we're on
tBoolean blink_on = true;

void blink(void) {
    SetPin(PIN_F2, blink_on);
    blink_on = !blink_on;
	
}



// The 'main' function is the entry point of the program
int main(void) {
	float ADCValue;
	float ADCValue2;
	tADC *adc[4];
	tADC *adc2[4];
	typedef struct Motor tMotor;
	typedef struct ADC tADC;
	tMotor *left;
	tMotor *right;
	tADC *LeftIR;
	tADC *RightIR;
	float Wall_Left = 0;
	float Wall_Right = 0;
	left = InitializeServoMotor(PIN_B0, false);
  right = InitializeServoMotor(PIN_B1, true);

	adc[0] = InitializeADC(PIN_D0);
	adc[1] = InitializeADC(PIN_D1);
  adc[2] = InitializeADC(PIN_D2);
  adc[3] = InitializeADC(PIN_D3);
		//InitializeADC(PIN_C0);

	adc2[0] = InitializeADC(PIN_E0);
  adc2[1] = InitializeADC(PIN_E1);
  adc2[2] = InitializeADC(PIN_E2);
  adc2[3] = InitializeADC(PIN_E3);

	while(1) {
		while(1){
					SetMotor(right,0.5);
					SetMotor(left,0.5);
					blink();
					Wait(.05);
		}
	
		blink();
		Wait(.05);
    ADCValue = ADCRead(adc[0]);
    Printf("IR values: %d\n", (int)(1000 * ADCValue));  //Left IR sensor
    ADCValue2 = ADCRead(adc2[0]);
    Printf("IR values: %d\n", (int)(1000 * ADCValue2));	//Right IR sensor
		if(ADCValue >= .5 && ADCValue2 >= .5){
			SetMotor(right , 0.0);
			SetMotor(left , 0.0);
		}else if(ADCValue >= .4 && ADCValue2 < .4){		//object to the left, but nothing to the right so turn right
			SetMotor(right , 0.5);
			SetMotor(left , 0.0);
		}else if(ADCValue2 >= .4 && ADCValue < .4){	//object to the right, but nothing to the left so turn left
			SetMotor(right , 0.0);
			SetMotor(left , 0.5);			
		}else{
			SetMotor(right , 0.5);
			SetMotor(left , 0.5);
		}
	}
 }
 
