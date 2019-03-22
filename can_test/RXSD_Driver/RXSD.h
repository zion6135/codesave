#ifndef _RXSD_h_
#define _RXSD_h_

#include "can.h"
typedef enum
{
  read_positon=1,
	read_speed,
  read_current,
  read_status,
	
  set_spped,
  motor_status,
  diable_motor,
  error_clear,
  heart_beat,	
}command_name;

#define MCU_addr  1
#define motor_left 2
#define motor_right 3

void RXSD_Enable(void);
void type_get(uint8_t x);
void clear_data(void);
int *Dec_to_bin(int x,int c[10]);
void get_param(uint8_t motor_which,uint8_t do_what);
void set_speed(uint8_t motor_which,int32_t speed_want);
void fault_clear(uint8_t motor_which);


#endif 
