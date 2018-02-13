#ifndef _HELIOS_KERNEL_H_
#define _HELIOS_KERNEL_H_


#define h_int   static int
#define h_char  static char
#define h_long  static long
#define h_short static short
#define h_byte  static unsigned char
#define os_true set_os_true((pData))




#define A     1000
#define B     5

extern int task_global_num;

typedef enum task_status
{
	idle = 0,
	ready ,
	wait,
	run,
} task_status;

typedef struct TASK
{
	int                              pri;   					             //优先级
	unsigned long                    count; 					            //运行次数
	float                            CPU_src; 				           //所占用的CPU资源
	int                              pid;     				          //任务pid号
	unsigned long                    realtime;  			         //任务的实时运行时间
	unsigned long                    start_time_stamp;  			//任务启动时间戳
	unsigned long                    stop_time_stamp;  		   //任务结束时间戳
	int                              sleep_time_us;         //任务挂起时的睡眠时间
	task_status                      status;       			   //任务的状态
	char *                           task_name;           //任务的名字
	void (*f)(struct TASK * pData);                      //任务对应的处理函数
	struct TASK * task_next;                            //指针，指向下一个任务
}task_type;

typedef struct APP_message_typedef
{
		unsigned int muetx;
	  unsigned char Rx_Data[20];
}APP_message_typedef_type;

extern int MAX_TASK_NUM;

extern task_type * task_head;
int  set_os_true(task_type * task_head);
void hos_getostime(task_type*pData , int time_add_us);
void hos_delay(task_type*pData , int time_us);
void hos_task_register(
												 int pri,
												 char * name,
												 void (*fun)(struct TASK * pData));
void os_schedule( task_type*pData_task );













#endif



