#include "RXSD.h"
extern uint8_t  Data[8];
//�˳�����Ҫ�������CAN�����ֲ�д�ģ�
//ʵ��������ʹ�ܣ���4�ֲ��������ٶȵĹ��ܡ�

uint8_t Buffer_to_send[8]={MCU_addr,0,0,0,0,0,0,0};
//4λ10������ת16 ����
int *Dec_to_bin(int x,int c[10])
{
    int hex[16]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
    int i=0;
    int m=0;
		int a[10];
//		int *p=c;
		while(x>0)
    {
     i++;
     a[i]=x%16;
     x=x/16;
    } //�õ���λ16������
    //printf("erer%d\r\n",i);
    if(i==1) {m=3;}
    else if(i==2) {m=2;}
    else if(i==3) {m=1;}

    for(;i>0;i--)
 {
	 c[m]=hex[(a[i])];
	 //printf("%d\r\n",p[m]);
     m++;
 }
 //printf("\r\n");
 return c;
}

//֪��Ҫִ�еĲ���
/*
  read_positon=1,
	read_speed,
  read_current,
  read_Status,
	
  set_spped,
  motor_status,
  diable_motor,
  error_clear,
  heart_beat,	
*/
void type_get(uint8_t x)
{
  switch(x)
	{
		case read_positon:{Buffer_to_send[1]=0x51;break;}
	  case read_speed:{Buffer_to_send[1]=0x53;break;}
		case read_current:{Buffer_to_send[1]=0x54;break;}
	  case read_status:{Buffer_to_send[1]=0x55;break;}
		
		case set_spped:{Buffer_to_send[1]=0x68;break;}
	  
		case motor_status:{Buffer_to_send[1]=0x71;	break;}
		case error_clear:{Buffer_to_send[1]=0x73;	break;}
		case heart_beat:{Buffer_to_send[1]=0x79;	break;}
	}
}
void clear_data(void)
{
uint8_t  i;
	for(i=1;i<8;i++)
	  {
		Buffer_to_send[i]=0;
		}
}

//����ʹ��
void RXSD_Enable(void)
{
	 uint8_t  Send_Buffer[3]={0x01,0x71,0x01};
   CANx_SendNormalData(&hcan1,0x602,Send_Buffer,3);
}
//��������4��ָ��
void get_param(uint8_t motor_which,uint8_t do_what)
{
    type_get(do_what);
	  CANx_SendNormalData(&hcan1,motor_which+0x200,Buffer_to_send,8);
}

//���ٶ�
void set_speed(uint8_t motor_which,int32_t speed_want)
{
    int buffer[10]={0,0,0,0,0,0,0,0,0,0};
	  int *speed_hex;
	  type_get(5);
    speed_hex= Dec_to_bin(speed_want,buffer);
		//int ��char�Ƿ�ƥ�䣿��
		Buffer_to_send[4]=speed_hex[0];
		Buffer_to_send[5]=speed_hex[1];
		Buffer_to_send[6]=speed_hex[2];
		Buffer_to_send[7]=speed_hex[3];
 	  CANx_SendNormalData(&hcan1,motor_which+0x300,Buffer_to_send,8);
    clear_data();		
}
//�������
void fault_clear(uint8_t motor_which)
{
  Buffer_to_send[1] = 0x73;
  Buffer_to_send[2] = 1;
	CANx_SendNormalData(&hcan1,motor_which+0x600,Buffer_to_send,3); 
	
}
//void enable_sure(void)
//{
//	 uint8_t  Send_Buffer[3]={0x01,0x71,0x01};
//   if(Receive_Meg.StdId==0x582)
//	{
//		 if(Data[0]==0x02){
//			 if(Data[1]==0x71){
//				 if(Data[2]==0x01){
//				   HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
//           //enable success
//		 }}}
//	 }
//	 else 
//   {
//	     //printf("Enable failed");
//	 }
//}
