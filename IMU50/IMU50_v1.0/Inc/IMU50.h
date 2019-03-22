#ifndef _IMU50_H_
#define _IMU50_H_

#include "usart.h"


typedef struct IMU_DATA
{

	float yaw;   
	float pitch;  
	float roll;   

	float Euler_covariance[9]; 

	float angular_velocity_x;   
	float angular_velocity_y; 
	float angular_velocity_z;   
	float angular_velocity_covariance[9]; 

	float linear_acceleration_x;  
	float linear_acceleration_y;  
	float linear_acceleration_z;  
	float linear_acceleration_covariance[9]; 
	
	unsigned char IMU_state;  
}IMU_msg;



void IMU_data_get(void);
uint8_t data_transform(uint8_t x);
void IMU_Init(void);
void angular_acceleration_groy_get(void);

#endif
