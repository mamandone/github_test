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
	int                              pri;   					             //���ȼ�
	unsigned long                    count; 					            //���д���
	float                            CPU_src; 				           //��ռ�õ�CPU��Դ
	int                              pid;     				          //����pid��
	unsigned long                    realtime;  			         //�����ʵʱ����ʱ��
	unsigned long                    start_time_stamp;  			//��������ʱ���
	unsigned long                    stop_time_stamp;  		   //�������ʱ���
	int                              sleep_time_us;         //�������ʱ��˯��ʱ��
	task_status                      status;       			   //�����״̬
	char *                           task_name;           //���������
	void (*f)(struct TASK * pData);                      //�����Ӧ�Ĵ�����
	struct TASK * task_next;                            //ָ�룬ָ����һ������
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



