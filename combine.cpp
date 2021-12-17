#include<stdio.h>
 int main()
{
    //Variables using for Shortest Job First (Non-preemptive)
    /*
    bt = burst time
    p= process
    wt = waiting time
    tat = turn around time
	*/
	//SJF variables 
	int bt[20],p[20],wt[20],tat[20],i,j,n,total=0,pos,temp1;
    float avg_wt,avg_tat;
    
    //Round Robin variables 
	int  limit, remain, counter = 0, time_quantum, overheads, x = -1;
    int wait_time[10], turnaround_time[10], wait_time_sum = 0, turnaround_time_sum =0,  arrival_time[10], burst_time[10], temp[10];
    float average_wait_time, average_turnaround_time, awt, att;
	
	printf("Enter Total Number of Processes:");
	//Ask user for the input and store in bt array
    scanf("%d",&n); 
    limit = n;
		  for(i = 0; i < limit; i++)
      {
            printf("\nEnter Details of Process[%d]", i + 1);
            printf("\nArrival Time: "); scanf("%d", &arrival_time[i]);
            printf("Burst Time: ");  scanf("%d", &burst_time[i]);   
            temp[i] = burst_time[i];
            bt[i] = burst_time[i];
            p[i]=i+1;
      }
 
      printf("nEnter Time Quantum: ");
      scanf("%d", &time_quantum);
// SJF functionn 
  
   //Sorting of burst times
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(bt[j]<bt[pos])
                pos=j;
        }
        temp1=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp1;
        temp1=p[i];
        p[i]=p[pos];
        p[pos]=temp1;
    }
    wt[0]=0; //Waiting time of the first element is zero
    
	//The remaining waiting time is calculated by using two for loop           
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
        total+=wt[i];
    }
    printf("\n Shortest Job First");
    avg_wt=(float)total/n;      
    total=0;
    printf("\nProcess\t    \t    Burst Time\t    \tWaiting Time\tTurnaround Time");
    
    //Turnaround time is calculated by adding the burst time and the waiting time
    
	for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];   
        total+=tat[i];
        printf("\nProcess[%d]\t\t  %d\t\t    %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
    }
    total = 0;
    
	printf("\n");	
	
	printf("\n Roun Robin");  

      printf("\nProcess ID |Burst Time |Turnaround Time |Waiting Time");
    
    // Round Robin function
    remain = n;
	  for(total = 0, i = 0; remain != 0;)
      {
      		//Don't have burst time remained
            if(temp[i] <= time_quantum && temp[i] > 0)
            {
                  total = total + temp[i];
                  temp[i] = 0;
                  counter = 1;
                  x++;
            }
            //Still have burst time remained
            else if(temp[i] > 0)
            { 
				  //Decrease the burst_time of current process by time quantum      	
                  temp[i] = temp[i] - time_quantum;
                  total = total + time_quantum;
                  x++;
                 
            }
            //Don't have any burst time left => End process
			if(temp[i] == 0 && counter == 1)
            {	
            	
                  remain--;
                 //Wait_time and turn around time without overheads
				  wait_time[i] = total - arrival_time[i] - burst_time[i] ;
                  turnaround_time[i] = total - arrival_time[i] ;
				  printf("\nProcess[%d]     \t%d          \t%d          \t%d  <- Without Overheads", i + 1, burst_time[i], turnaround_time[i] , wait_time[i] );
				  //Wai_time and turn around time with overheads
				  printf("\nProcess[%d]     \t%d          \t%d          \t%d  <- With Overheads", i + 1, burst_time[i], turnaround_time[i]+x , wait_time[i] +x  );
				  awt =  awt + (total +x) - arrival_time[i] - burst_time[i];
				  att =  att + (total + x) - arrival_time[i];				 
				  wait_time_sum = wait_time_sum +   wait_time[i];
                  turnaround_time_sum = turnaround_time_sum + turnaround_time[i];
                  counter = 0;
                  printf("\n");
            }
          
		    if(i == limit - 1)
            {
                  i = 0;
            }
            //Check time appear of next process
            else if(arrival_time[i + 1] <= total)
            {
                  i++; 
            }
            else
            {
                  i = 0;
                
            }	
      }
    avg_tat=(float)total/n;    
    printf("\n\nAverage Waiting Time using for Shortest Job First (Non-preemptive): %f",avg_wt);
    printf("\nAverage Turnaround Time using for Shortest Job First (Non-preemptive):%f\n",avg_tat);
    
    overheads = x ;
    average_wait_time = wait_time_sum * 1.0 / limit;
    average_turnaround_time = turnaround_time_sum * 1.0 / limit;
    awt = awt * 1.0 / limit;
    att = att * 1.0 / limit;
	printf("\nAverage Waiting Time Using Roun Robin:\t%f", average_wait_time);
    printf("\nAvg Turnaround Time Using Roun Robin :\t%fn", average_turnaround_time);
    printf("\nAverage Waiting Time Using Roun Robin with overheads:\t%f", awt);
    printf("\nAvg Turnaround Time Using Roun Robin with overheads  :\t%fn", att);
    printf("\n overhead time :\t%dms", overheads);
    printf("\n");
    
    if (avg_wt < average_wait_time && avg_tat < average_turnaround_time){
    	printf("Average Waiting Time and Turnaround time using for Shortest Job First (Non-preemptive) smaller than Round Robin");
    	printf("\nShortest Job First will be your priority choice");
	} else if(avg_wt > average_wait_time && avg_tat > average_turnaround_time){
		printf("Average Waiting Time and Turnaround time using for Shortest Job First (Non-preemptive) larger than Round Robin");
		printf("\nRoun Robin will be your priority choice");
	}
	else if (avg_wt == average_wait_time && avg_tat == average_turnaround_time){
		printf("\nBoth will be your priority  ");
	}
      return 0;
}
