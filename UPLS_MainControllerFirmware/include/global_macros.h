#ifndef GLOBAL_MACROS_H
#define GLOBAL_MACROS_H

// Define this device for package configuration
// THIS_DEFINE values:
//		1 - xavier
//		2 - hook
//		3 - main controller

#define THIS_DEVICE				3
#define DEFAULT_RECEIVER_DEVICE	2

//#define	__XAVIER
//#define	__HOOK
#ifndef __MAIN_CONTROLLER
# define	__MAIN_CONTROLLER
#endif

const char sun[9][19] = {
	"        '        \n",
    "     \\  ,  /     \n",
    " ' ,___/_\\___, ' \n",
    "    \\ /o.o\\ /    \n",
    "-=   > \\_/ <   =-\n",
    "    /_\\___/_\\    \n",
    " . `   \\ /   ` . \n",
    "     /  `  \\     \n",
    "        .        \n"
};

#define PI 		3.14159265359
#define TWO_PI	6.28318530718

/////////////////////// Pin definitions //////////////////////////

#include <PinNames.h>

// Led driver pins
#define LEDS_REAR   PA_0	// PWM
#define LEDS_FRONT  PB_1	// PWM

// Winch motor driver pins
#define WINCH_MOTOR_ADC     	PA_1
#define WINCH_MOTOR_SLP     	PB_5	// PWM
#define WINCH_MOTOR_IN2      	PB_6
#define WINCH_MOTOR_IN1     	PB_7
#define WINCH_MOTOR_ENCODER_A   PB_3
#define WINCH_MOTOR_ENCODER_B	PB_4

// Front leg motor driver pins
#define LEG_MOT_FRONT_ADC     		PA_6
#define LEG_MOT_FRONT_IN1     		PA_11	
#define LEG_MOT_FRONT_IN2           PA_12
#define LEG_MOT_FRONT_SLP           PB_0	// PWM
#define LEG_MOT_FRONT_POS_SWITCH	PA_4

// Rear leg motor driver pins
#define LEG_MOT_REAR_ADC     		PA_7
#define LEG_MOT_REAR_IN1     		PA_8
#define LEG_MOT_REAR_IN2     		PA_9
#define LEG_MOT_REAR_SLP     		PA_10	// PWM
#define LEG_MOT_REAR_POS_SWITCH		PA_5

// UART
#define UART_TX		PA_2
#define UART_RX		PA_3

// I2C
#define I2C_SDA		PB_11
#define I2C_SCL		PB_10

// nRF24L01+
#define RF24_MISO		PB_14
#define RF24_MOSI		PB_15
#define RF24_SCK		PB_13
#define RF24_CE			PB_12
#define RF24_CSN		PB_9
#define RF24_IRQ		PB_8

////////////////////// Other definitions /////////////////////////

#define WINCH_MOTOR_ENCODER_SPR		276
#define WINCH_MOTOR_R_IPROPI		2200.f
#define DRV8874_PWM_PERIOD_US		20000
#define UART_BAUD_RATE				38400
#define ADC_V_REF					3.3f

#endif // GLOBAL_MACROS_H