#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 3 /*���Ҵ��� �׽�Ʈ �ϱ� ���� ���� ���� ������ */
#define BUFFER_SIZE 50 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*������� ����� ������ ���� ������ ����� �޵��� �Ѵ�*/
/*����� ��� ���� �迭�� �뷮�� �ʰ��� ��� ���� �޸� �Ҵ����� �迭�� ũ�⸦ Ű���.
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

char **names;//char* Ÿ���� �迭�� �̸��̹Ƿ� char**Ÿ���� �����̴�.
char **numbers;

int capacity=INIT_CAPACITY; //�迭�� ũ��
int n=0; //��� ��

char delim[]=" "; 
int main(int argc, char *argv[]) {
	
	init_directory();//names�� numbers ����
	process_command();//������� ����� �޾� ó���ϴ� �κ��� ������ �Լ��� ����
	 
	return 0;
}

void init_directory(){//3ĭ¥�� �迭 ���� 
	names=(char **)malloc(INIT_CAPACITY*sizeof(char *));
	numbers=(char **)malloc(INIT_CAPACITY*sizeof(char *));
	/*�Ҵ��� �޸��� byte ���� �����Ѵ�.
	���� ���ڷ� �����ϴ� �ͺ��� sizeof �� ���°� ����.
	*/
}

int read_line(char str[],int limit){/*limit���� �� line�� ��쿡�� �޺κ��� ©����.*/
	int ch,i=0;
	
	while((ch=getchar())!='\n'){//�ٹٲ� ���ڰ� ���� ������ �д´�.
		if(i<limit-1)//�迭�� �뷮�� �ʰ����� ���� ���� �����Ѵ�.
			str[i++]=ch;
		}
		
		str[i]='\0';
		//�������� null character�� �߰��Ѵ�.
	return i;//������ ���� ���ڼ��� ��ȯ�Ѵ�.
	
}
/*���� ������ �Է��� fgets,getline�� ���� */

void process_command(){
	char command_line[BUFFER_SIZE];//�� ������ �뤊�� �о���� ���� ����
	char *command, *argument1, *argument2;
	
	while(1){
	printf("����� �Է��ϼ���:\n");
	
	if(read_line(command_line,BUFFER_SIZE)<=0)//������� �뤊�� �д´�.
		continue;
	command=strtok(command_line,delim);//ù ��° ��ū�� ��ɾ�
	//strtok�� �̿��Ͽ� �߶� ù��° ��ū�� �ּҸ� command ������ ������ ����
	//if(command=NULL) continue; 
	
	if(strcmp(command,"read")==0){
		argument1=strtok(NULL,delim);//read��ɿ��� �ι� �� ��ū�� ���� ���̴�.
		if(argument1==NULL){
		printf("���� �̸��� �ʿ��մϴ�.\n");
		continue;
	}
	load(argument1);//���� ���� ���ڷ� �ָ鼭 load�Լ� ȣ��
}
	else if(strcmp(command,"add")==0){
	argument1=strtok(NULL,delim);
	argument2=strtok(NULL,delim);
	/*��ɾ �̾����� 2���� ��ū�� ���� �̸��� ��ȭ��ȣ
	*/
	if(argument1==NULL||argument2==NULL){
	printf("Invalid arguments.\n");
	continue;
}

	add(argument1,argument2);
	/*�̸��� ��ȭ��ȣ�� ���ڷ� �ָ鼭 add�� ȣ���Ѵ�.*/
	printf("%s����  ���������� �߰��Ǿ����ϴ�.\n",argument1);
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
				printf("�߸��� �����Դϴ�\n");
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
	//���� ũ�Ⱑ 2�� �迭���� �Ҵ��Ѵ�.
	 
	for(i=0;i<n;i++){
		tmp1[i]=names[i];
		tmp2[i]=numbers[i];
	}
	//���� �迭 names�� numbers�� ���� ���ο� �迭�� �����Ѵ�.
	 
	free(names);
	free(numbers);
	/* ���� �迭 names�� numbers�� ���̻� �ʿ����.
	������ �� �迭�� init_directory()�Լ����� ���� �޸� �Ҵ����� �������
	�迭�̹Ƿ� �׳� �θ� �������� �ʰ� �����Ѵ�. �̷� �޸𸮸� garbage��� �θ���
	free�� ���� ��ȯ�Ѵ�.*/
	 
	names=tmp1;
	numbers=tmp2;
	
/*names�� numbers�� ���ο� �迭�� ����Ű���� �Ѵ�.
(�迭�� �̸��� ������ �����̴�.)*/
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
	reallocate(); //�迭�� �� �� ��� ���Ҵ�
	
	int i=n-1;
	while(i>=0&&strcmp(names[i],name)>0){
		names[i+1]=names[i];
		numbers[i+1]=numbers[i];
		i--;
	}
	
	names[i+1]=strdup(name);
	numbers[i+1]=strdup(number);
	/*name�� number�� �� ������ ���������̱� ������
	����ؼ� �����ǰ� �ϱ� ���� strdup�� ���*/ 
	
	n++;
}
void find(char *name){
	int index=search(name);
	if(index==-1)
		printf("'%s'���� �������� �ʽ��ϴ�.\n",name);
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
		printf(" �̸��� '%s'�� ����� �������� �ʽ��ϴ�.\n",name);
		return ;
	}
	
	int j=i;
	for(;j<n-1;j++){
		names[j]=names[j+1];
		numbers[j]=numbers[j+1]; //�ϳ��� ��ܿ�
	}
	n--;
	printf("'%s'�� ���������� �����Ǿ����ϴ�.\n",name);
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
	printf("�� %s ��.\n",n);
}

