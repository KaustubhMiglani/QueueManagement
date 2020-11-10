#include<stdio.h>
#include<stdlib.h>
struct intentryexit
    {int timetaken;
    int requestnumber;
    int entry;
    int exit;
	int selfnum;
    };




struct adress
{struct intentryexit* adressof;

};
struct linkedlist
{int integer;
struct linkedlist* next;
};
void deleting(struct linkedlist* head)//deleting the head from linked list//
    {head=head->next;
    }
void move(struct intentryexit* array,int lenofarray)//moving the data of last(n-1) elemnts to first (n-1) elments where n =size of array.In short the elments are moving ahead in counterbuffer by a distance of one.//
    {int i=0;
    for(i=1;i<lenofarray;i++)
        {(array+i-1)->timetaken=(array+i)->timetaken;
        (array+i-1)->entry=(array+i)->entry;
        (array+i-1)->exit=(array+i)->exit;
        (array+i-1)->requestnumber=(array+i)->requestnumber;
	(array+i-1)->selfnum=(array+i)->selfnum;

        }
    (array+lenofarray-1)->timetaken=-1;
    }
void replacetimebysum(struct intentryexit* array,int lenofarray)//a function that replaces timetaken of a request by totaltime taken in the counterbuffer//
{int i=0;
int j=0;
for(i=1;i<lenofarray;i++)


        {((array+i)->timetaken)+=((array+i-1)->timetaken);
        }


}

int main()
    {FILE* fptr;
	FILE* fptralloc;
	FILE* fptrlog;
    fptr=fopen("queue.txt","r");
    struct adress* adressarray;
    struct linkedlist* z;
    struct linkedlist* head;
    struct linkedlist* tail;
    int l=0;
	fptralloc=fopen("allocation.txt","w");
	fptrlog=fopen("log.txt","w");

    struct intentryexit* y;
    int n;
    int b;
    int j;
    int dummy;
    fscanf(fptr,"%d",&n);
    fscanf(fptr,"%d",&b);

    adressarray=(struct adress*)calloc(n,sizeof(struct adress));//an array of pointers//
    int i=0;
    while(i<n)
        {y=(struct intentryexit*)calloc(b,sizeof(struct intentryexit));
        ((adressarray+i)->adressof)=y;//storing these adresses in adressarray//
        i++;
        }
    i=0;
    int counter=0;
    while(fscanf(fptr,"%d",&dummy)>0)//reading data and storing in linked list//
        {z=(struct linkedlist*)malloc(sizeof(struct linkedlist));
        (*z).integer=dummy;
        (*z).next=NULL;
        if(counter==0)
            {head=z;
            tail=z;
            }
        else
            {(*tail).next=z;
            tail=z;
            }
        counter++;
        }
int time=0;
int lob=0;
int now=1;
    int dumming=1;
    for(j=0;j<b;j++)//reading first n*b requests//
        {for(i=0;i<n;i++)
            {if(head!=NULL){((((adressarray+i)->adressof)+j))->timetaken=(head->integer);
            ((((adressarray+i)->adressof)+j))->entry=0;
            ((((adressarray+i)->adressof)+j))->exit=0;
            ((((adressarray+i)->adressof)+j))->requestnumber=dumming;
	((((adressarray+i)->adressof)+j))->selfnum=(head->integer);
           fprintf(fptrlog,"The request number %d has moved to buffercounter from queue at time %d\n",((((adressarray+i)->adressof)+j)->requestnumber),time);
            head=head->next;
            dumming++;
	now++;
		if(lob==0){fprintf(fptrlog,"The request number %d has moved to the counter from queue at time %d \n",(((adressarray+i)->adressof)->requestnumber),time);}

            }}
	lob++;
        }
if(now<n*b)
	{printf("There must be more than %d requests in file since otherwise the counterbuffer of some counters will have empty spotand there will be no elements in queue at all \n Please try again \n ",n*b);
	exit(0);}
    for(i=0;i<n;i++)
        {replacetimebysum((adressarray+i)->adressof,b);
        }





     time=1;
    while(head!=NULL) //reading all elements one by one from queue if a request exits//
        {l=0;
            for(i=0;i<n;i++)
            {if(((((adressarray+i)->adressof)->timetaken)==time))
                {l++;
            (((adressarray+i)->adressof)->exit)=time;
                fprintf(fptralloc,"The request number %d entered buffer of counter %d at time %d and exited at time %d.His time spent in queue is %d and time spent in buffer is %d  \n",(((adressarray+i)->adressof)->requestnumber),i+1,(((adressarray+i)->adressof)->entry),(((adressarray+i)->adressof)->exit),(((adressarray+i)->adressof)->entry),(((adressarray+i)->adressof)->exit)-(((adressarray+i)->adressof)->entry)-(((adressarray+i)->adressof)->selfnum));
                fprintf(fptrlog,"The request number %d has exited the system at %d \n",(((adressarray+i)->adressof)->requestnumber),time);



         move((adressarray+i)->adressof,b);
         fprintf(fptrlog,"The request number %d has moved to the counter from queue at time %d \n",(((adressarray+i)->adressof)->requestnumber),time);
                ((((adressarray+i)->adressof)+b-1))->timetaken=(head->integer)+((((adressarray+i)->adressof)+b-2)->timetaken);
            ((((adressarray+i)->adressof)+b-1))->entry=time;
            ((((adressarray+i)->adressof)+b-1))->exit=0;
            ((((adressarray+i)->adressof)+b-1))->requestnumber=dumming;
            fprintf(fptrlog,"The request number %d has moved to buffercounter from queue at time %d\n",((((adressarray+i)->adressof)+b-1)->requestnumber),time);
            head=head->next;

            dumming++;
        if(head==NULL){break;}


                }

         }
   if(l==0)
    {fprintf(fptrlog,"At time %d 0 requests moved to counter from buffer,0 requests moved to buffer from queue and 0 of the requests exited the system \n",time);}
    if(head==NULL){break;}
    time++;

        }
time++;
int poll=0;
 int k=1;
 while(k<=n*b)//printing the information of entry exit for last n*b elements//
    {l=0;
        for(i=0;i<n;i++)
            {if((((adressarray+i)->adressof)->timetaken)==time)
                {
        (((adressarray+i)->adressof)->exit)=time;
         fprintf(fptralloc,"The request number %d entered buffer of counter %d at time %d and exited at time %d.His time spent in queue is %d and time spent in buffer is %d  \n",(((adressarray+i)->adressof)->requestnumber),i+1,(((adressarray+i)->adressof)->entry),(((adressarray+i)->adressof)->exit),(((adressarray+i)->adressof)->entry),(((adressarray+i)->adressof)->exit)-(((adressarray+i)->adressof)->entry)-(((adressarray+i)->adressof)->selfnum));
           fprintf(fptrlog,"The request number %d has exited the system at %d \n",(((adressarray+i)->adressof)->requestnumber),time);
                move((adressarray+i)->adressof,b);
                fprintf(fptrlog,"The request number %d has moved to the counter from queue at time %d \n",(((adressarray+i)->adressof)->requestnumber),time);
                fprintf(fptrlog,"At time %d 0 requests moved to counter from buffer,0 requests moved to buffer from queue and 0 of the requests exited the system ",time);
        k++;
        l++;
    }
    }
if((l==0)&&(poll=0)){fprintf(fptrlog,"At time %d 0 requests moved to counter from buffer,0 requests moved to buffer from queue and 0 of the requests exited the system \n",time);}
time++;
poll++;
}
}

	

