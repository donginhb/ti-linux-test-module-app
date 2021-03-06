#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/ioctl.h> 
#include "am1808_gpio.h"
#include "debug_console.h"
#include "test_gpio.h"

char p8_str_buf[512];

unsigned int g_u16_gpio_num_cmp[] = 
{
	// BBBB1
	8*16+0,
	8*16+1,
	8*16+2,
	8*16+3,
	8*16+4,
	8*16+5,
	8*16+6,
	8*16+7,
	8*16+8,
	8*16+9,
	8*16+10,
	8*16+11,
	8*16+12,
	8*16+13,
	8*16+14,
	8*16+15,

	// AAAA1
	0*16+0,
	0*16+1,
	0*16+2,
	0*16+3,
	0*16+4,
	0*16+5,
	0*16+6,
	0*16+7,
	0*16+8,
	0*16+9,
	0*16+10,
	0*16+11,
	0*16+12,
	0*16+13,
	0*16+14,
	0*16+15,

	// BBBB2
	5*16+0,
	5*16+1,
	5*16+2,
	5*16+3,
	5*16+4,
	5*16+5,
	5*16+6,
	5*16+7,
	5*16+8,
	5*16+9,
	5*16+10,
	5*16+11,
	5*16+12,
	5*16+13,
	5*16+14,
	5*16+15,

	// AAAA2
	3*16+0,
	3*16+1,
	3*16+2,
	3*16+3,
	3*16+4,
	3*16+5,
	3*16+6,
	3*16+7,
	3*16+8,
	3*16+9,
	3*16+10,
	3*16+11,
	3*16+12,
	3*16+13,
	3*16+14,
	3*16+15,

	// BBBB3
	4*16+8,
	4*16+9,
	4*16+10,
	4*16+11,
	4*16+12,
	4*16+13,
	4*16+14,
	4*16+15,

	// AAAA3
	7*16+8,
	7*16+9,
	7*16+10,
	7*16+11,
	7*16+12,
	7*16+13,
	7*16+14,
	7*16+15,

	// BBBB4
	2*16+9,
	2*16+12,
	2*16+15,
	6*16+9,
	6*16+10,
	6*16+11,
	6*16+12,
	6*16+13,
	6*16+14,

	// AAAA4
	1*16+4,
	1*16+5,
	1*16+8,
	1*16+9,
	1*16+10,
	1*16+11,
	1*16+12,
	1*16+13,
	1*16+14,

	// BBBB5
	6*16+0,
	6*16+1,
	6*16+2,
	6*16+3,
	6*16+4,
	6*16+5,
	6*16+6,
	6*16+7,
	6*16+8,

	// AAAA5
	2*16+0,
	2*16+1,
	2*16+2,
	2*16+3,
	2*16+4,
	2*16+5,
	2*16+6,
	2*16+7,
	2*16+8,
};


unsigned int g_u16_gpio_num[] = 
{
	// AAAA1
	0*16+0,
	0*16+1,
	0*16+2,
	0*16+3,
	0*16+4,
	0*16+5,
	0*16+6,
	0*16+7,
	0*16+8,
	0*16+9,
	0*16+10,
	0*16+11,
	0*16+12,
	0*16+13,
	0*16+14,
	0*16+15,

	// BBBB1
	8*16+0,
	8*16+1,
	8*16+2,
	8*16+3,
	8*16+4,
	8*16+5,
	8*16+6,
	8*16+7,
	8*16+8,
	8*16+9,
	8*16+10,
	8*16+11,
	8*16+12,
	8*16+13,
	8*16+14,
	8*16+15,

	// AAAA2
	3*16+0,
	3*16+1,
	3*16+2,
	3*16+3,
	3*16+4,
	3*16+5,
	3*16+6,
	3*16+7,
	3*16+8,
	3*16+9,
	3*16+10,
	3*16+11,
	3*16+12,
	3*16+13,
	3*16+14,
	3*16+15,

	// BBBB2
	5*16+0,
	5*16+1,
	5*16+2,
	5*16+3,
	5*16+4,
	5*16+5,
	5*16+6,
	5*16+7,
	5*16+8,
	5*16+9,
	5*16+10,
	5*16+11,
	5*16+12,
	5*16+13,
	5*16+14,
	5*16+15,
	
	// AAAA3
	7*16+8,
	7*16+9,
	7*16+10,
	7*16+11,
	7*16+12,
	7*16+13,
	7*16+14,
	7*16+15,

	// BBBB3
	4*16+8,
	4*16+9,
	4*16+10,
	4*16+11,
	4*16+12,
	4*16+13,
	4*16+14,
	4*16+15,

	// AAAA4
	1*16+4,
	1*16+5,
	1*16+8,
	1*16+9,
	1*16+10,
	1*16+11,
	1*16+12,
	1*16+13,
	1*16+14,

	// BBBB4
	2*16+9,
	2*16+12,
	2*16+15,
	6*16+9,
	6*16+10,
	6*16+11,
	6*16+12,
	6*16+13,
	6*16+14,

	// AAAA5
	2*16+0,
	2*16+1,
	2*16+2,
	2*16+3,
	2*16+4,
	2*16+5,
	2*16+6,
	2*16+7,
	2*16+8,

	// BBBB5
	6*16+0,
	6*16+1,
	6*16+2,
	6*16+3,
	6*16+4,
	6*16+5,
	6*16+6,
	6*16+7,
	6*16+8,

};



#define M_GPIO_NUM_CNT (sizeof(g_u16_gpio_num)/sizeof(unsigned int))

unsigned int g_u16_gpio_connect[M_GPIO_NUM_CNT];
int g_u16_gpio_connect_cnt = 0;

int fn_test_am1808_gpio(void)
{
	int i;
	int j;
	int value_tmp = 0;

	// test single gpio output
#if 0
	fn_set_am1808_gpio_direct(g_u16_gpio_num[0],M_GPIO_OUTPUT);
	fn_set_am1808_gpio_value(g_u16_gpio_num[0],M_GPIO_OUTPUT_LOW);
	printf("wait for gpio output\r\n");
	while(1);
#endif
	
	#if (DEBUG_TEST_GPIO >= 1)
	sprintf(p8_str_buf, "start test am1808 gpio,gpio_num_cnt=%d\r\n",M_GPIO_NUM_CNT);
	fn_test_uart_log_console_write(p8_str_buf);
	#endif
	// 循环每个引脚
	for(i = 0; i < M_GPIO_NUM_CNT; i++)
	{
		#if (DEBUG_TEST_GPIO >= 3)
		sprintf(p8_str_buf, "test gpio_num, GPIO%d[%d]\r\n",g_u16_gpio_num[i]/16,g_u16_gpio_num[i]%16);
		fn_test_uart_log_console_write(p8_str_buf);
		#endif	
		// 设定需要测试的引脚为输出 其他设定为输入
		for(j = 0; j < M_GPIO_NUM_CNT; j++)
		{
			if(j == i)
			{
				fn_set_am1808_gpio_direct(g_u16_gpio_num[j],M_GPIO_OUTPUT);
			}
			else
			{
				fn_set_am1808_gpio_direct(g_u16_gpio_num[j],M_GPIO_INPUT);
			}	
		}

		// 测试其余的gpio口
		g_u16_gpio_connect_cnt = 0;
		for(j = 0; j < M_GPIO_NUM_CNT; j++)
		{
			if(j == i)
			{
				continue;
			}		
#if 1	
			fn_set_am1808_gpio_value(g_u16_gpio_num[i],M_GPIO_OUTPUT_HIGH);
			value_tmp = fn_get_am1808_gpio_value(g_u16_gpio_num[j]);
			if(value_tmp != M_GPIO_OUTPUT_HIGH)
			{
				continue;
			}
#endif
	
			fn_set_am1808_gpio_value(g_u16_gpio_num[i],M_GPIO_OUTPUT_LOW);
			value_tmp = fn_get_am1808_gpio_value(g_u16_gpio_num[j]);
			if(value_tmp != M_GPIO_OUTPUT_LOW)
			{
				continue;
			}
			g_u16_gpio_connect[g_u16_gpio_connect_cnt] = g_u16_gpio_num[j];
			g_u16_gpio_connect_cnt++;
			#if (DEBUG_TEST_GPIO >= 3)
			sprintf(p8_str_buf, "test GPIO%d[%d] is same with GPIO%d[%d]\r\n",
							g_u16_gpio_num[i]/16,g_u16_gpio_num[i]%16,
							g_u16_gpio_num[j]/16,g_u16_gpio_num[j]%16);
			fn_test_uart_log_console_write(p8_str_buf);
			#endif
		}
		#if (DEBUG_TEST_GPIO >= 3)
		sprintf(p8_str_buf, "test gpio g_u16_gpio_connect_cnt=%d\r\n",g_u16_gpio_connect_cnt);
		fn_test_uart_log_console_write(p8_str_buf);
		#endif

		#if (DEBUG_TEST_GPIO >= 1)
		if(g_u16_gpio_connect_cnt == 1)
		{
			if(g_u16_gpio_connect[0] == g_u16_gpio_num_cmp[i])
			{
				sprintf(p8_str_buf, "OK:GPIO%d[%d] <---> GPIO%d[%d]\r\n",
					g_u16_gpio_num[i]/16,g_u16_gpio_num[i]%16,
					g_u16_gpio_connect[0]/16,g_u16_gpio_connect[0]%16);
				fn_test_uart_log_console_write(p8_str_buf);
			}
			else
			{
				sprintf(p8_str_buf, "ERROR:GPIO%d[%d] <---> GPIO%d[%d]\r\n",
					g_u16_gpio_num[i]/16,g_u16_gpio_num[i]%16,
					g_u16_gpio_connect[0]/16,g_u16_gpio_connect[0]%16);
				fn_test_uart_log_console_write(p8_str_buf);
			}
		}
		else if(g_u16_gpio_connect_cnt == 0)
		{
			sprintf(p8_str_buf, "ERROR:GPIO%d[%d] no connect,pls to GPIO%d[%d]\r\n",
					g_u16_gpio_num[i]/16,g_u16_gpio_num[i]%16,
					g_u16_gpio_num_cmp[i]/16,g_u16_gpio_num_cmp[i]%16);
				fn_test_uart_log_console_write(p8_str_buf);
		}
		else
		{
			int k;	
			sprintf(p8_str_buf, "ERROR:GPIO%d[%d] <---> ",
					g_u16_gpio_num[i]/16,g_u16_gpio_num[i]%16);	
			fn_test_uart_log_console_write(p8_str_buf);	
			for(k = 0; k < g_u16_gpio_connect_cnt;k++)
			{
				sprintf(p8_str_buf, " GPIO%d[%d] ",
					g_u16_gpio_connect[i]/16,g_u16_gpio_connect[i]%16);
				fn_test_uart_log_console_write(p8_str_buf);
			}
			fn_test_uart_log_console_write("\r\n");
		}
		//fn_test_uart_log_console_write("\r\n");
		#endif
		
	}
}






