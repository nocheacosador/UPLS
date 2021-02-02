#ifndef GLOBAL_MACROS_H
#define GLOBAL_MACROS_H

#pragma GCC diagnostic ignored "-Wreorder"

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

#ifdef _MSC_VER
    #define forceinline __forceinline
#elif defined(__GNUC__)
    #define forceinline inline __attribute__((__always_inline__))
#elif defined(__CLANG__)
    #if __has_attribute(__always_inline__)
        #define forceinline inline __attribute__((__always_inline__))
    #else
        #define forceinline inline
    #endif
#else
    #define forceinline inline
#endif

/*
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
*/

#define PI 		3.14159265359f
#define TWO_PI	6.28318530718f

/////////////////////// Pin definitions //////////////////////////

#include <PinNames.h>

// Led driver pins
#define LEDS_REAR   PA_0	// PWM_2
#define LEDS_FRONT  PB_1	// PWM_1

// Winch motor driver pins
#define WINCH_MOTOR_ADC     	PA_1
#define WINCH_MOTOR_SLP     	PB_5	
#define WINCH_MOTOR_IN2      	PB_6	// PWM_4
#define WINCH_MOTOR_IN1     	PB_7	// PWM_4
#define WINCH_MOTOR_ENCODER_A   PB_3
#define WINCH_MOTOR_ENCODER_B	PB_4

// Front leg motor driver pins
#define LEG_MOT_FRONT_ADC     		PA_6
#define LEG_MOT_FRONT_IN1     		PA_11	
#define LEG_MOT_FRONT_IN2           PA_12
#define LEG_MOT_FRONT_SLP           PB_0	// PWM_1
#define LEG_MOT_FRONT_POS_SWITCH	PA_4	// unused

// Rear leg motor driver pins
#define LEG_MOT_REAR_ADC     		PA_7
#define LEG_MOT_REAR_IN1     		PA_8
#define LEG_MOT_REAR_IN2     		PA_9
#define LEG_MOT_REAR_SLP     		PA_10	// PWM_1
#define LEG_MOT_REAR_POS_SWITCH		PA_5	// unused


// Old pinout UART
// #define UART_TX		PA_2
// #define UART_RX		PA_3

// new UART
#define UART_TX		PB_10
#define UART_RX		PB_11

// Extruder control pins
#define EXTRUDER_PWM	PA_2	// PWM_2
#define EXTRUDER_DIR	PA_3

// nRF24L01+
#define RF24_MISO		PB_14
#define RF24_MOSI		PB_15
#define RF24_SCK		PB_13
#define RF24_CE			PB_12
#define RF24_CSN		PB_9
#define RF24_IRQ		PB_8

////////////////////// Other definitions /////////////////////////

#define WINCH_MOTOR_ENCODER_SPR			134
#define WINCH_PULLEY_DIAMETER			0.0235f		// meters
#define WINCH_LOWERING_GROUND_SPEED		0.1f		// m/s
#define WINCH_SPEED_GROUND_DISTANCE		1.f			// meters
#define WINCH_MAX_LOWERING_ACCELERATION	100.f		// RPM/s
#define WINCH_MAX_RETURN_SPEED			270.f
#define WINCH_MAX_SPEED					200.f		// RPM
#define WINCH_HOME_SEARCHING_SPEED		100.f		// RPM
#define WINCH_HOME_SEARCHING_CUR_TRESH	800			// milliamperes
#define WINCH_MOTOR_R_IPROPI			2200.f		// ohms
#define LEG_MOT_FRONT_R_IPROPI			2200.f		// ohms
#define LEG_MOT_REAR_R_IPROPI			2200.f		// ohms
#define DRV8874_PWM_PERIOD_US			20000		// microseconds
#define DRV8874_PROPER_PWM_PERIOD_US	200			// microseconds
#define UART_BAUD_RATE					38400
#define ADC_V_REF						3.3f		// volts

#define METERS_PER_SEC_TO_RPM(x)		( x / WINCH_PULLEY_DIAMETER / PI * 60.f )
#define RPM_TO_METERS_PER_SEC(x)		( x * WINCH_PULLEY_DIAMETER * PI / 60.f )

#define MOTOR_UPDATE_PERIOD			0.02f		// seconds

// 		PID Parameters
// Fixed point with precision of 6 digits
#define PID_KP		 0.0001f
#define PID_KI		 0.009f
#define PID_KD		 0.00005f

#endif // GLOBAL_MACROS_H