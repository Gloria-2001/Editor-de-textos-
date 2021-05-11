#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getch.h"

FILE *fp1,*fp2,*fp;
char fn[20],c;
char t[4]=".txt";
int m;

void Crear()
{
  printf("\nIngresa nombre del archivo: ");
  scanf("%s",fn);
  strcat(fn,t);
  fp1=fopen(fn,"w");
  printf("\nIngresa el contenido y ` para guardar.\n");

  while(1)
	{
		c=getch();
		
		if(c==96)
			goto end1;
		
		if(c==13)
		{
			c='\n';
			printf("\n");
			fputc(c,fp1);
		}
	
		else
		{
			printf("%c",c);
			fputc(c,fp1);
		}
	}
	
	end1: fclose(fp1);
}

void Ver()
{
	printf("\nIngresa nombre del archivo: ");
	scanf("%s",fn);
	strcat(fn,t);
	fp1=fopen(fn,"r");
	
	if(fp1==NULL)
	{
		printf("\nNo Existe");
		goto end1;
	}
		
	while(!feof(fp1))
	{
		c=getc(fp1);
		printf("%c",c);
	}
	
	end1:
	fclose(fp1);
	printf("\n\nPresiona boton para continuar\n");
	getch();
}
	
 
void Eliminar()
{
	printf("\nIngresa nombre del archivo: ");
	scanf("%s",fn);
	strcat(fn,t);
	fp1=fopen(fn,"r");
	
	if(fp1==NULL)
	{
		printf("\nNo Existe");
		goto end2;
	}
	
	fclose(fp1);
	
	if(remove(fn)==0)
	{
		printf("\n\nArchivo Eliminado");
		goto end2;
	}
	
	else
	printf("\nError!\n");
	
	end2: printf("\n\nPresiona boton para continuar\n");
	getch();
}
 
void Append()
{
	printf("\nIngresa nombre del archivo: ");
	scanf("%s",fn);
	strcat(fn,t);
	fp1=fopen(fn,"r");
	
	if(fp1==NULL)
	{
		printf("\nNo Existe");
		fclose(fp1);
		goto end3;
	}
	
	while(!feof(fp1))
	{
		c=getc(fp1);
		printf("%c",c);
	}
	
	fclose(fp1);
	printf("\nIngresa el contenido y `para guardar.\n");
	fp1=fopen(fn,"a");
	
	while(1)
	{
		c=getch();
		
		if(c==19)
			goto end3;
		
		if(c==13)
		{
			c='\n';
			printf("\n");
			fputc(c,fp1);
		}
	
		else
		{
			printf("%c",c);
			fputc(c,fp1);
		}
	}
	
	end3: fclose(fp1);
}

void main()
{
  do 
  {
    printf("\n\nPRACTICA 8\n\n");
    printf("\n1.CREAR\n2.VER\n3.APPEND\n4.ELIMINAR\n5.SALIR\n");
    printf("\nIngresa numero: ");
    scanf("%d",&m);
    switch(m)
    {
      case 1:
        Crear();
        break;

      case 2:
        Ver();
        break;

      case 3:
        Append();
        break;

      case 4:
        Eliminar();
        break;

      case 5:
        exit(0);
    }
  }while(1);
}

