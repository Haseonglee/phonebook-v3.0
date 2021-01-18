#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 3 /*재할당을 테스트 하기 위해 아주 작은 값으로 */
#define BUFFER_SIZE 50 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*사용자의 명령을 받을때 라인 단위로 명령을 받도록 한다*/
/*저장된 사람 수가 배열의 용량을 초과할 경우 동적 메모리 할당으로 배열의 크기를 키운다.
*/ 

void init_directory();
int read_line(char str[],int limit);
void process_command();
void reallocate();
void load(char *fileName);
void add(char * name,char *number);
void find(char *name);
void remover(char *name);
void save(char *fileName);
void status();

char **names;//char* 타입의 배열의 이름이므로 char**타입의 변수이다.
char **numbers;

int capacity=INIT_CAPACITY; //배열의 크기
int n=0; //사람 수

char delim[]=" "; 
int main(int argc, char *argv[]) {
	
	init_directory();//names와 numbers 생성
	process_command();//사용자의 명령을 받아 처리하는 부분을 별개로 함수로 만듦
	 
	return 0;
}

void init_directory(){//3칸짜리 배열 생성 
	names=(char **)malloc(INIT_CAPACITY*sizeof(char *));
	numbers=(char **)malloc(INIT_CAPACITY*sizeof(char *));
	/*할당할 메모리의 byte 수를 지정한다.
	직접 숫자로 지정하는 것보다 sizeof 를 쓰는게 좋다.
	*/
}

int read_line(char str[],int limit){/*limit보다 긴 line의 경우에는 뒷부분이 짤린다.*/
	int ch,i=0;
	
	while((ch=getchar())!='\n'){//줄바꿈 문자가 나올 떄까지 읽는다.
		if(i<limit-1)//배열의 용량을 초과하지 않을 떄만 저장한다.
			str[i++]=ch;
		}
		
		str[i]='\0';
		//마지막에 null character을 추가한다.
	return i;//실제로 읽은 문자수를 반환한다.
	
}
/*라인 단위의 입력은 fgets,getline도 가능 */

void process_command(){
	char command_line[BUFFER_SIZE];//한 라인을 통쨰로 읽어오기 위한 버퍼
	char *command, *argument1, *argument2;
	
	while(1){
	printf("명령을 입력하세요:\n");
	
	if(read_line(command_line,BUFFER_SIZE)<=0)//명령줄을 통쨰로 읽는다.
		continue;
	command=strtok(command_line,delim);//첫 번째 토큰은 명령어
	//strtok를 이용하여 잘라낸 첫번째 토큰의 주소를 command 포인터 변수에 저장
	//if(command=NULL) continue; 
	
	if(strcmp(command,"read")==0){
		argument1=strtok(NULL,delim);//read명령에서 두번 쨰 토큰은 파일 명이다.
		if(argument1==NULL){
		printf("파일 이름이 필요합니다.\n");
		continue;
	}
	load(argument1);//파일 명을 인자로 주면서 load함수 호출
}
	else if(strcmp(command,"add")==0){
	argument1=strtok(NULL,delim);
	argument2=strtok(NULL,delim);
	/*명령어에 이어지는 2개의 토큰은 각각 이름과 전화번호
	*/
	if(argument1==NULL||argument2==NULL){
	printf("Invalid arguments.\n");
	continue;
}

	add(argument1,argument2);
	/*이름과 전화번호를 인자로 주면서 add를 호출한다.*/
	printf("%s님은  성공적으로 추가되었습니다.\n",argument1);
}

	else if(strcmp(command,"find")==0){
		argument1=strtok(NULL,delim);
		if(argument1==NULL){
			printf("Invalid arguments.\n");
			continue;
		}
		
		find(argument1);
	}
	
	else if(strcmp(command,"status")==0)
		status();
	else if(strcmp(command,"delete")==0){
		argument1=strtok(NULL,delim);
		if(argument1==NULL){
			printf("Invalid arguments.\n");
			continue;
		}
		remover(argument1);
	}

	else if(strcmp(command,"save")==0){
		argument1=strtok(NULL,delim);
		argument2=strtok(NULL,delim);
		
		if(argument1==NULL||strcmp("as",argument1)!=0
			||argument2==NULL){
				printf("잘못된 형식입니다\n");
				continue;
			}
			save(argument2);
		}
		else if(strcmp(command,"exit")==0)
			break;
		}
	}

void reallocate(){
	int i;
	capacity*=2;
	char **tmp1=(char **)malloc(capacity*sizeof(char *));
	char **tmp2=(char **)malloc(capacity*sizeof(char *));
	//먼저 크기가 2인 배열들을 할당한다.
	 
	for(i=0;i<n;i++){
		tmp1[i]=names[i];
		tmp2[i]=numbers[i];
	}
	//원본 배열 names와 numbers의 값을 새로운 배열에 복사한다.
	 
	free(names);
	free(numbers);
	/* 원본 배열 names와 numbers는 더이상 필요없다.
	하지만 두 배열은 init_directory()함수에서 동적 메모리 할당으로 만들어진
	배열이므로 그냥 두면 없어지지 않고 존재한다. 이런 메모리를 garbage라고 부르고
	free를 통해 반환한다.*/
	 
	names=tmp1;
	numbers=tmp2;
	
/*names와 numbers가 새로운 배열을 가리키도록 한다.
(배열의 이름은 포인터 변수이다.)*/
}


void load(char *fileName){
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];
	
	FILE *fp=fopen(fileName,"r");
	if(fp==NULL){
		printf("Open fail.\n");
		return ;
	}
	
	while(fscanf(fp,"%s",buf1)!=EOF){
		fscanf(fp,"%s",buf2);
		add(buf1,buf2);
	}
	fclose(fp);
}

void add(char * name,char *number){
	if(n>=capacity)
	reallocate(); //배열이 꽉 찬 경우 재할당
	
	int i=n-1;
	while(i>=0&&strcmp(names[i],name)>0){
		names[i+1]=names[i];
		numbers[i+1]=numbers[i];
		i--;
	}
	
	names[i+1]=strdup(name);
	numbers[i+1]=strdup(number);
	/*name과 number에 들어갈 변수는 지역변수이기 때문에
	계속해서 유지되게 하기 위해 strdup를 사용*/ 
	
	n++;
}
void find(char *name){
	int index=search(name);
	if(index==-1)
		printf("'%s'님은 존재하지 않습니다.\n",name);
	else
		printf("%s\n",numbers[index]);
	}
	int search(char *name){
		int i;
		for(i=0;i<n;i++){
			if(strcmp(name,names[i])==0){
				return i;
			}
		}
		return -1;
	}

void remover(char *name){
	int i=search(name);
	if(i=-1){
		printf(" 이름이 '%s'인 사람은 존재하지 않습니다.\n",name);
		return ;
	}
	
	int j=i;
	for(;j<n-1;j++){
		names[j]=names[j+1];
		numbers[j]=numbers[j+1]; //하나씩 당겨옴
	}
	n--;
	printf("'%s'는 성공적으로 삭제되었습니다.\n",name);
}

void save(char *fileName){
	int i;
	FILE *fp=fopen(fileName,"w");
	if(fp==NULL){
		printf("Open failed\n");
		return;
	}
	
	for(i=0;i<n;i++){
		fprintf(fp,"%s %s\n",names[i],numbers[i]);
	}
	fclose(fp);
}

void status(){
	int i;
	for(i=0;i<n;i++){
		printf("%s %s\n",names[i],numbers[i]);
	}
	printf("총 %s 명.\n",n);
}

