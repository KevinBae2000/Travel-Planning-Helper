#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#define MAX 30

struct list{
  int area2;//1. Jeonju 2. Seoul 3. Busan 4. Ulsan 5. Daejeon 6. Suwon
  int area1;//1. Jeonju 2. Seoul 3. Busan 4. Ulsan 5. Daejeon 6. Suwon
	int tran; //1. Train 2. Bus 3. Airplane
	char sp[30];
  int price;
  int minute;
};
struct plan{
  int dest;//1. Jeonju 2. Seoul 3. Busan 4. Ulsan 5. Daejeon 6. Suwon
	int tran; //1. Train 2. Bus 3. Airplane
	char sp[30];
  int price;
  int minute;
};
struct spe{
  int area;//1. Jeonju 2. Seoul 3. Busan 4. Ulsan 5. Daejeon 6. Suwon
  char spe[3][30];
};

int loadlist(struct list* l[]);
void loadspe(struct spe* s[], int count);
void printarea(int a);
void printarea2(int a);
void printtrans(int a);
void printtrans2(int a);
int choosedest(struct list* l[],int list_count,int* start, struct plan* p[],int pcount);
void printresult(int start,struct plan* p[],int pcount, struct spe* s[],int cost);

int main(void) {
  int count=0;
  int start;
  int dest;
  int choose;//select
  struct list* list[50];
  struct plan* myplan[10];
  int c=1;
  int cost=99999;
  int check=0;
  
  int listcount=loadlist(list);
  struct spe* spe[listcount];
  loadspe(spe, listcount);
  
  while (cost>0&&count<10)
  {
    if(count==0){
      while(check==0){
      printf("Traffic budget? ");
      scanf("%d",&cost);
        if(cost>0)check=1;
        }
      printf("Please select the departure point\n1. Jeonju 2. Seoul 3. Busan 4. Ulsan 5. Daejeon 6. Suwon\nDeparture point number: ");
      scanf("%d",&start);
      printf("\n");
    dest=choosedest(list,listcount,&start, myplan,count);
      }
    else{
      dest=choosedest(list,listcount,&dest, myplan,count);
    }
    cost-=myplan[count]->price;
    count++;
    if(cost<0){
      printf("Exceeded the budget\n");
      count--;
      cost+=myplan[count]->price;
    }
    printf("The remaining transportation budget is %d won.\nIf you want to finish the plan, please enter 0 if it is not another number. ",cost);
  scanf("%d",&c);
    if(c==0)break;
    printf("\n");
  }
    printresult(start,myplan,count,spe,cost);
  return 0;
}

int loadlist(struct list* l[]){
  int count=0;
	FILE* file;
	file=fopen("list.txt", "r");
	while(!feof(file)){
		l[count] = (struct list*)malloc(sizeof(struct list));
		int r = fscanf(file, "%d %d %d %s %d %d", &(l[count]->area1),&(l[count]->area2), &(l[count]->tran), l[count]->sp, &(l[count]->price), &(l[count]->minute));
		if(r < 4) continue;;
		count++;
	}
	fclose(file);
  return count;

}

void loadspe(struct spe* s[],int count){
  FILE* file;
	file=fopen("place.txt", "r");
  for(int i=0; i<count; i++){
    s[i] = (struct spe*)malloc(sizeof(struct spe));
    fscanf(file, "%d %s %s %s", &(s[i]->area), s[i]->spe[0], s[i]->spe[1],s[i]->spe[2]);
    }
	fclose(file);

}

void printarea(int a){
  if(a==1)printf("1.Jeonju ");
  else if(a==2)printf("2.Seoul ");
  else if(a==3)printf("3.Busan ");
  else if(a==4)printf("4.Ulsan ");
  else if(a==5)printf("5.Daejeon ");
  else if(a==6)printf("6.Suwon ");
}
void printarea2(int a){
  if(a==1)printf("Jeonju ");
  else if(a==2)printf("Seoul ");
  else if(a==3)printf("Busan ");
  else if(a==4)printf("Ulsan ");
  else if(a==5)printf("Daejeon ");
  else if(a==6)printf("Suwon ");
}
void printtrans(int a){
  if(a==1)printf("1. Train ");
  else if(a==2)printf("2. Bus ");
  else if(a==3)printf("3. Airplane ");
}
void printtrans2(int a){
  if(a==1)printf("Train ");
  else if(a==2)printf("Bus ");
  else if(a==3)printf("Airplane ");
}

int choosedest(struct list* l[],int list_count,int* start, struct plan* p[],int pcount){
  int flag[6]={0,0,0,0,0,0};
  int flag2[3]={0,0,0};
  int dest;
  int method;
  int sp;
  p[pcount] = (struct plan*)malloc(sizeof(struct plan));

  while(1){
    printf("Please select the next travel place\n");
    for(int i=0; i<list_count;i++){
      if(l[i]->area1==*start){
        flag[(l[i]->area2)-1]=1;
      }
      else if(l[i]->area2==*start){
        flag[(l[i]->area1)-1]=1;
      }
    }
    
    for(int i=0;i<6;i++){
      if (flag[i]==1)
      printarea(i+1);      
    }
    printf("\n");
    printf("Travel place number: ");
    scanf("%d",&dest);
    printf("\n");
    if(dest>=1&&dest<=6&&flag[dest-1]==1)break;
  }
  p[pcount]->dest=dest;
  while(1){
    printf("Please select the means of transportation\n");
    for(int i=0; i<list_count;i++){
      if(l[i]->area1==*start&&l[i]->area2==dest){
        flag2[l[i]->tran -1]=1;
      }
      else if(l[i]->area2==*start&&l[i]->area1==dest){
        flag2[l[i]->tran -1]=1;
      }
    }
    for(int i=0; i<3;i++){
      if(flag2[i]==1)
        printtrans(i+1);
    }
    printf("\nTransportation number: ");
    scanf("%d",&method);
    printf("\n");
    if(method>=1&&method<=3&&flag2[method-1]==1)break;
  }
  p[pcount]->tran=method;
  
  while(1){
    printf("Please select the model you want to use\n");
    for(int i=0; i<list_count;i++){
      if(l[i]->area1==*start&&l[i]->area2==dest&&l[i]->tran==method){
        printf("%d. %s price: %dWon spending time: %dminutes\n",i+1,l[i]->sp,l[i]->price,l[i]->minute);
      }
      else if(l[i]->area2==*start&&l[i]->area1==dest&&l[i]->tran==method){
        printf("%d. %s price: %dWon spending time: %dminutes\n",i+1,l[i]->sp,l[i]->price,l[i]->minute);
      }
    }
    printf("\nModel number: ");
    scanf("%d",&sp);
    sp--;
    printf("\n");
    if(sp>=0&&sp<=list_count&&l[sp]->area2==*start&&l[sp]->area1==dest&&l[sp]->tran==method)break;
    else if(sp>=0&&sp<=list_count&&l[sp]->area1==*start&&l[sp]->area2==dest&&l[sp]->tran==method)break;
  }
  strcpy(p[pcount]->sp,l[sp]->sp);
  p[pcount]->price=l[sp]->price;
  p[pcount]->minute=l[sp]->minute;
  
  
  
  return dest;
}

void printresult(int start,struct plan* p[],int pcount, struct spe* s[],int cost){
  printf("\nTotal summary of travel planning plans\n");
  printf("Departure: ");
  printarea2(start);
  printf("\n");
  for(int i=0; i<pcount; i++){
    printf("%dst destination: ",i+1);
    printarea2(p[i]->dest);
    printf("\n");
    printf("Transportation: ");
    printtrans2(p[i]->tran);
    printf("(%s)\n",p[i]->sp);
    printf("cost: %dWon spending time: %dminutes\n",p[i]->price,p[i]->minute);
    printf("Tourist attractions: %s %s %s\n",s[p[i]->dest-1]->spe[0],s[p[i]->dest-1]->spe[1],s[p[i]->dest-1]->spe[2]);
  }
  int price=0;
  int min=0;
  for(int i=0; i<pcount; i++){
    price+=p[i]->price;
    min+=p[i]->minute;
  }
  printf("Traffic budget: %d",price+cost);
  printf("\nTotal transportation cost: %dWon\nTotal moving time: %dminutes\nRemaining budget: %dWon",price,min,cost);

  FILE*file=fopen("travel.txt","w");
  fprintf(file,"Total summary of travel planning plans\nDeparture: ");
  int a= start;
  if(a==1)fprintf(file,"Jeonju\n\n");
  else if(a==2)fprintf(file,"Seoul\n\n");
  else if(a==3)fprintf(file,"Busan\n\n");
  else if(a==4)fprintf(file,"Ulsan\n\n");
  else if(a==5)fprintf(file,"Daejeon\n\n");
  else if(a==6)fprintf(file,"Suwon\n\n");

  for(int i=0; i<pcount; i++){
    fprintf(file,"%dst destination: ",i+1);
    a=p[i]->dest;
    if(a==1)fprintf(file,"Jeonju ");
    else if(a==2)fprintf(file,"Seoul ");
    else if(a==3)fprintf(file,"Busan ");
    else if(a==4)fprintf(file,"Ulsan ");
    else if(a==5)fprintf(file,"Daejeon ");
    else if(a==6)fprintf(file,"Suwon ");
    fprintf(file,"\nTransportation: ");
    if(p[i]->tran==1)fprintf(file,"Train ");
    else if(p[i]->tran==2)fprintf(file,"Bus ");
    else if(p[i]->tran==3)fprintf(file,"Airplane ");
    fprintf(file,"(%s)\n",p[i]->sp);
    fprintf(file, "cost: %dWon spending time: %dminutes\n",p[i]->price,p[i]->minute);
    fprintf(file,"Tourist attractions: %s %s %s\n\n",s[p[i]->dest-1]->spe[0],s[p[i]->dest-1]->spe[1],s[p[i]->dest-1]->spe[2]);
  }
  fprintf(file,"Traffic budget: %d",price+cost);
  fprintf(file,"\nTotal transportation cost: %dWon\nTotal moving time: %dminutes\nRemaining budget: %dWon",price,min,cost);
  fclose(file);
}
