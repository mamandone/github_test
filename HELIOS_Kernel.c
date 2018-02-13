#include "HELIOS_Kernel.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


int task_global_num = 0;

task_type * task_head = NULL;
int MAX_TASK_NUM = 0;

void hos_getostime(task_type *pData , int time_add_us)
{
	  int i = 0;
	  task_type *pData_list = pData;
		while(pData_list != NULL && i<task_global_num)
		{
			  i++;
			  pData_list->realtime += time_add_us;
			  if(pData_list->sleep_time_us > 0)
				{
					    pData_list->sleep_time_us -= time_add_us;
				}
				else if(pData_list->sleep_time_us <= 0)
				{
						  pData_list->sleep_time_us = 0;
					    pData_list->status = ready;
				}
				pData_list = pData_list->task_next;
		}
}

void hos_delay(task_type*pData , int time_us)
{
	  if(pData->status != wait)
		{
				pData->sleep_time_us = time_us;
				if(time_us > 0)
				{
						pData->status = wait;
					  pData->stop_time_stamp = pData->realtime;
				}
		}
		if(pData->status == wait)
		{
				if(pData->sleep_time_us <= 0)
				{
					  pData->sleep_time_us = 0;
						pData->status = ready ;
					  return;
				}
				else
				{
						return ;
				}
				//os_schedule( task_head );
		}	
}
void hos_task_register( 
												 int pri,
												 char * name,
												 void (*fun)(struct TASK * pData))
{
		  task_type * LIST_TEMP = task_head;
			task_type *Temp_Data = (task_type *)malloc(sizeof(task_type));
	    Temp_Data->task_name = (char *)malloc(strlen(name));
			strcpy(Temp_Data->task_name , name);
	    Temp_Data->pri = pri;
			Temp_Data->pid = task_global_num++;
	    Temp_Data->f = fun;
			Temp_Data->task_next = NULL;
	    Temp_Data->status = ready;
	    Temp_Data->count  = 1;
			if (LIST_TEMP == NULL)
			{
				 task_head = Temp_Data;
			}
			else if (LIST_TEMP != NULL)
			{
				while (LIST_TEMP->task_next != NULL)
				{
					 LIST_TEMP = LIST_TEMP->task_next;
				}
				MAX_TASK_NUM ++;
				LIST_TEMP->task_next = Temp_Data;
			}
}

static int switch_task(task_type*pData)
{
	  int pri_max   = 0;
	  int count_min = 500;
	  unsigned long count_sun = 0;
	  task_type*pData_list = pData;
	  task_type* pData_pri_max = NULL; 
	  task_type* pData_count_min = NULL; 
		
	  if(task_global_num == 1)
		{
				return pData_list->pid;
		}
		while(pData_list != NULL)
		{
			  //count_sun += (pData_list->count+1)*( 10*(pData_list->stop_time_stamp - pData_list->start_time_stamp) );
			  count_sun += (pData_list->count+1);
			  pData_list = pData_list->task_next;
		}
		pData_list = pData;
	  while(pData_list != NULL)
		{
			  //pData_list->CPU_src = (10*(float)pData_list->count*(pData->stop_time_stamp-pData->start_time_stamp))/(float)count_sun;
			  pData_list->CPU_src = ((float)pData_list->count)/(float)count_sun;
				if(pData_list->status  == ready)
				{
						if(pri_max < pData_list->pri) 
						{
							  pri_max = pData_list->pri;
                pData_pri_max = pData_list;			
						}
						if(count_min > pData_list->count) 
						{
							  count_min = pData_list->count;
                pData_count_min = pData_list;			
						}
				}
				pData_list = pData_list->task_next;
		}
		if( (pData_count_min->pri * A + (count_sun-(pData_count_min->count+1)) * B)  >=   (pData_pri_max->pri * A + (count_sun-pData_pri_max->count) * B) )
		{
				return  pData_count_min->pid;
		}
		else
		{
				return  pData_pri_max->pid;
		}
}

static task_type* os_pid_to_task(int pid,task_type *pData_task)
{
		task_type* pHead = pData_task;
		if(pHead == NULL)	return  NULL;
		while(pHead!=NULL)
		{
				if(pHead->pid == pid)
					return pHead;
				else
					pHead = pHead->task_next;
		}
		return NULL;
}

void os_schedule( task_type *pData_task )
{
		static int pid = 0;
		task_type * task_to_run = NULL; 
		
	  switch_task(pData_task);
	  pid = pid + 1;
	  if(pid >= (MAX_TASK_NUM+1) )
		{
				pid = 0;
		}
		task_to_run = os_pid_to_task(pid,pData_task);
	  if(task_to_run == NULL ) return;
	  if(task_to_run->status == wait ) return;
	  task_to_run->count++;
		task_to_run->status = run;
	  task_to_run->f(task_to_run);
}

int  set_os_true(task_type *pData_task)
{
	   int result = 1; 
		
		 task_type * task_to_run = pData_task; 
		 if(task_to_run->status == ready || task_to_run->status == wait)
		 {
					result = 0;
					return result;
		 }
		 if( task_to_run->status == run)
		 {
			  task_to_run->start_time_stamp = task_to_run->realtime;
		 }
		 return result;
}

