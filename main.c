#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#define MAX 30

struct list{
  int area2;//1.전주 2.서울 3.부산 4.울산 5.대전 6.수원
  int area1;//1.전주 2.서울 3.부산 4.울산 5.대전 6.수원
	int tran; //1.기차 2.버스 3.비행기
	char sp[30];
  int price;
  int minute;
};
struct plan{
  int dest;//1.전주 2.서울 3.부산 4.울산 5.대전 6.수원
	int tran; //1.기차 2.버스 3.비행기
	char sp[30];
  int price;
  int minute;
};
struct spe{
  int area;//1.전주 2.서울 3.부산 4.울산 5.대전 6.수원
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
  int choose;//선택
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
      printf("Transportation budget? ");
      scanf("%d",&cost);
        if(cost>0)check=1;
        }
      printf("출발지점을 선택해 주세요\n1.전주 2.서울 3.부산 4.울산 5.대전 6.수원\n출발지점 번호: ");
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
      printf("예산을 초과하셧습니다\n");
      count--;
      cost+=myplan[count]->price;
    }
    printf("남은 교통비는 %d원입니다.\n계획짜기를 끝내시고 싶으시다면 0을 아니라면 다른 숫자를 입력해주세요 ",cost);
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
  if(a==1)printf("1.전주 ");
  else if(a==2)printf("2.서울 ");
  else if(a==3)printf("3.부산 ");
  else if(a==4)printf("4.울산 ");
  else if(a==5)printf("5.대전 ");
  else if(a==6)printf("6.수원 ");
}
void printarea2(int a){
  if(a==1)printf("전주 ");
  else if(a==2)printf("서울 ");
  else if(a==3)printf("부산 ");
  else if(a==4)printf("울산 ");
  else if(a==5)printf("대전 ");
  else if(a==6)printf("수원 ");
}
void printtrans(int a){
  if(a==1)printf("1. 기차 ");
  else if(a==2)printf("2. 버스 ");
  else if(a==3)printf("3. 비행기 ");
}
void printtrans2(int a){
  if(a==1)printf("기차 ");
  else if(a==2)printf("버스 ");
  else if(a==3)printf("비행기 ");
}

int choosedest(struct list* l[],int list_count,int* start, struct plan* p[],int pcount){
  int flag[6]={0,0,0,0,0,0};
  int flag2[3]={0,0,0};
  int dest;
  int method;
  int sp;
  p[pcount] = (struct plan*)malloc(sizeof(struct plan));

  while(1){
    printf("다음 여행장소를 선택해 주세요\n");
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
    printf("여행장소 번호: ");
    scanf("%d",&dest);
    printf("\n");
    if(dest>=1&&dest<=6&&flag[dest-1]==1)break;
  }
  p[pcount]->dest=dest;
  while(1){
    printf("교통수단을 선택해 주세요\n");
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
    printf("\n이동방법 번호: ");
    scanf("%d",&method);
    printf("\n");
    if(method>=1&&method<=3&&flag2[method-1]==1)break;
  }
  p[pcount]->tran=method;
  
  while(1){
    printf("이용하실 곳을 선택해주세요\n");
    for(int i=0; i<list_count;i++){
      if(l[i]->area1==*start&&l[i]->area2==dest&&l[i]->tran==method){
        printf("%d. %s 금액: %d원 소요시간: %d분\n",i+1,l[i]->sp,l[i]->price,l[i]->minute);
      }
      else if(l[i]->area2==*start&&l[i]->area1==dest&&l[i]->tran==method){
        printf("%d. %s 금액: %d원 소요시간: %d분\n",i+1,l[i]->sp,l[i]->price,l[i]->minute);
      }
    }
    printf("\n이용할 곳에 번호: ");
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
  printf("\n여행 이동계획 총요약\n");
  printf("출발 지점: ");
  printarea2(start);
  printf("\n");
  for(int i=0; i<pcount; i++){
    printf("%d번째 여행지: ",i+1);
    printarea2(p[i]->dest);
    printf("\n");
    printf("이동방법: ");
    printtrans2(p[i]->tran);
    printf("(%s)\n",p[i]->sp);
    printf("금액: %d원 소요시간: %d분\n",p[i]->price,p[i]->minute);
    printf("관광명소: %s %s %s\n",s[p[i]->dest-1]->spe[0],s[p[i]->dest-1]->spe[1],s[p[i]->dest-1]->spe[2]);
  }
  int price=0;
  int min=0;
  for(int i=0; i<pcount; i++){
    price+=p[i]->price;
    min+=p[i]->minute;
  }
  printf("교통예산: %d",price+cost);
  printf("\n총 교통비: %d원\n총 이동시간: %d분\n남은 교통비: %d원",price,min,cost);

  FILE*file=fopen("travel.txt","w");
  fprintf(file,"여행 이동계획 총요약\n출발 지점: ");
  int a= start;
  if(a==1)fprintf(file,"전주\n\n");
  else if(a==2)fprintf(file,"서울\n\n");
  else if(a==3)fprintf(file,"부산\n\n");
  else if(a==4)fprintf(file,"울산\n\n");
  else if(a==5)fprintf(file,"대전\n\n");
  else if(a==6)fprintf(file,"수원\n\n");

  for(int i=0; i<pcount; i++){
    fprintf(file,"%d번째 여행지: ",i+1);
    a=p[i]->dest;
    if(a==1)fprintf(file,"전주 ");
    else if(a==2)fprintf(file,"서울 ");
    else if(a==3)fprintf(file,"부산 ");
    else if(a==4)fprintf(file,"울산 ");
    else if(a==5)fprintf(file,"대전 ");
    else if(a==6)fprintf(file,"수원 ");
    fprintf(file,"\n이동방법: ");
    if(p[i]->tran==1)fprintf(file,"기차 ");
    else if(p[i]->tran==2)fprintf(file,"버스 ");
    else if(p[i]->tran==3)fprintf(file,"비행기 ");
    fprintf(file,"(%s)\n",p[i]->sp);
    fprintf(file, "금액: %d원 소요시간: %d분\n",p[i]->price,p[i]->minute);
    fprintf(file,"관광명소: %s %s %s\n\n",s[p[i]->dest-1]->spe[0],s[p[i]->dest-1]->spe[1],s[p[i]->dest-1]->spe[2]);
  }
  fprintf(file,"교통예산: %d",price+cost);
  fprintf(file,"\n총 교통비: %d원\n총 이동시간: %d분\n남은 교통비: %d원",price,min,cost);
  fclose(file);
}
