#include "IMU50.h"
#include "math.h"

IMU_msg IMU_get;
extern uint8_t Rx_Buffer[48];

void IMU_Init(void)
{
	  /* USER CODE BEGIN 2 */
	//收到data_get个数据进入中断 将接收到的数据放入Rx_Buffer[48]
  HAL_UART_Receive_IT(&huart2,Rx_Buffer,48);          //
  /* USER CODE END 2 */
			IMU_data_get();
	
}
void IMU_data_get(void)
{
  uint8_t data_to_trans[5]={0x77,0x04,0x00,0x59,0x5D};
	HAL_UART_Transmit(&huart2,data_to_trans,5,1000);    
}
uint8_t data_transform(uint8_t x)  //0xXX变为XX
{
	uint8_t data;
	data=10*((x&0xf0)/16)+(x&0x0f)%16;
  return data;
}


void angular_acceleration_groy_get(void)
{	
	uint8_t flag;;
  if((Rx_Buffer[0]==0x77)&(Rx_Buffer[1]==0x2F)&(Rx_Buffer[2]==0x00)&(Rx_Buffer[3]==0x59))
  {
		flag=1;
	}
	if(flag==1)
	{
		//欧拉角
		//pitch get 
	  IMU_get.pitch=(Rx_Buffer[4]&0x0F)+data_transform(Rx_Buffer[5])+((float)data_transform(Rx_Buffer[6])/100);
		if((Rx_Buffer[4]&0x10)==0x10)  IMU_get.pitch=-IMU_get.pitch;
	  //roll get 
		IMU_get.roll=(Rx_Buffer[7]&0x0F)+data_transform(Rx_Buffer[8])+(float)data_transform(Rx_Buffer[9])/100;
		if((Rx_Buffer[7]&0x10)==0x10)  IMU_get.roll=-IMU_get.roll;	

		//重力加速度
	  //Gx get
		IMU_get.linear_acceleration_x=(Rx_Buffer[13]&0x0F)+0.01f*data_transform(Rx_Buffer[14])+(data_transform(Rx_Buffer[15])*0.0001f);
		if((Rx_Buffer[13]&0x10)==0x10)  IMU_get.linear_acceleration_x=-IMU_get.linear_acceleration_x;	
	  //Gy get
		IMU_get.linear_acceleration_y=(Rx_Buffer[16]&0x0F)+0.01f*data_transform(Rx_Buffer[17])+(data_transform(Rx_Buffer[18])*0.0001f);
		if((Rx_Buffer[16]&0x10)==0x10)  IMU_get.linear_acceleration_y=-IMU_get.linear_acceleration_y;	
	  //Gz get
		IMU_get.linear_acceleration_z=(Rx_Buffer[19]&0x0F)+0.01f*data_transform(Rx_Buffer[20])+(data_transform(Rx_Buffer[21])*0.0001f);
		if((Rx_Buffer[19]&0x10)==0x10)  IMU_get.linear_acceleration_z=-IMU_get.linear_acceleration_z;	

		//角速度
	  //x get
		IMU_get.angular_velocity_x=(Rx_Buffer[22]&0x0F)+data_transform(Rx_Buffer[23])+(0.01f*data_transform(Rx_Buffer[24]));
		if((Rx_Buffer[22]&0x10)==0x10)  IMU_get.angular_velocity_x=-IMU_get.angular_velocity_x;	
	  //y get
		IMU_get.angular_velocity_y=(Rx_Buffer[25]&0x0F)+data_transform(Rx_Buffer[26])+(0.01f*data_transform(Rx_Buffer[27]));
		if((Rx_Buffer[25]&0x10)==0x10)  IMU_get.angular_velocity_y=-IMU_get.angular_velocity_y;	
	  //z get
		IMU_get.angular_velocity_z=(Rx_Buffer[28]&0x0F)+data_transform(Rx_Buffer[29])+(0.01f*data_transform(Rx_Buffer[30]));
		if((Rx_Buffer[28]&0x10)==0x10)  IMU_get.angular_velocity_z=-IMU_get.angular_velocity_z;	
	}
}






