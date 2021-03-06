#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getch.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <assert.h>

FILE *fp1,*fp2,*fp;
DIR *dir1;
char fn[50],dn[50],*path,c;
char t[5]=".txt";
char cwd[BUFSIZ];
int m;
char newline;

void Crear(char path[500])
{
    long n;
    char *buf;

    n = pathconf(".", _PC_PATH_MAX);
    assert(n != -1);
    buf = malloc(n * sizeof(*buf));
	// Guardamos la dirección actual de la computadora
	// es similar al pwd
    assert(buf);
	if (getcwd(buf, n) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
  printf("\nIngresa nombre del archivo: ");
  scanf("%s",fn);
  strcat(fn,t);	// nombre.txt
  // Anteponemos '/' para poder direccionar correctamente
  // la dirección de la carpeta y archivo
  if(path[0] != '/' || path[0] != '\0'){
	  strcat(buf,"/");
  }
  strcat(buf,path);
  strcat(buf,"/");
  strcat(buf,fn);
  // Aqui ya se guarda la dirección de guardado completa
  // "directorio/completo/para/guardar/archivo.txt"
  fp1=fopen(buf,"w");
  // Cambiar a otro caracter que no se use demasiado y que sea facil
  // de ingresar 
  printf("\nIngresa el contenido y '0' para guardar.\n");

  while(1)
	{
		c=getch();
		
		if(c=='0')
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
	path = getcwd(NULL, BUFSIZ);  //obtener directorio actual
	printf("\nIngresa nombre del directorio. Si quieres directorio actual, ingresa 0: ");  
	scanf("%s",dn);
	if(*dn =='0')
	{
		strcat(path,"/");
	}
	else
	{
		strcat(path,"/");
		strcat(path,dn);
		strcat(path,"/");  //con esto tendria como /home/usuraio/nombrededirectoroio/	
	}
	printf("\nIngresa nombre del archivo: ");
	scanf("%s",fn);
	strcat(path,fn);
	strcat(path,t);
	 //con esto tendria completo /home/usuraio/nombrededirectoroio/texto.txt
	fp1=fopen(path,"r");

	if(fp1==NULL)
	{
		perror("\nNo Existe");
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
	
 
void Eliminar(char path[500])
{
	long n;
    char *buf;
    n = pathconf(".", _PC_PATH_MAX);
    assert(n != -1);
    buf = malloc(n * sizeof(*buf));
    assert(buf);
	
	if (getcwd(buf, n) == NULL) 
	{
        perror("error");
        exit(EXIT_FAILURE);
    	}
	printf("\nIngresa nombre del archivo: ");
	scanf("%s",fn);
	strcat(fn,t);	
	if(path[0] != '/' || path[0] != '\0')
	{
		strcat(buf,"/");
	}
	strcat(buf,path);
	strcat(buf,"/");
	strcat(buf,fn);

	fp1=fopen(buf,"r");
	
	if(fp1==NULL)
	{
		printf("\nNo Existe");
		goto end2;
	}
	
	fclose(fp1);
	
	if(remove(buf)==0)
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
	/*igual que hizo en funcion VER*/
	path = getcwd(NULL, BUFSIZ);  //obtener directorio actual
	printf("\nIngresa nombre del directorio. Si quieres directorio actual, ingresa 0: ");  
	scanf("%s",dn);
	if(*dn=='0')
	{
		strcat(path,"/");
	}
	else
	{
		strcat(path,"/");
		strcat(path,dn);
		strcat(path,"/");  //con esto tendria como /home/usuraio/nombrededirectoroio/	
	}
	printf("\nIngresa nombre del archivo: ");
	scanf("%s",fn);
	strcat(path,fn);
	strcat(path,t);
 	
	fp1=fopen(path,"r");
	
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
	printf("\nIngresa el contenido y 0 para guardar.\n");
	fp1=fopen(path,"a");
	
	while(1)
	{
		c=getch();
		
		if(c=='0')
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

void createDirectory(char path[500])
{
    long n;
    char *buf;
    n = pathconf(".", _PC_PATH_MAX);
    assert(n != -1);
    buf = malloc(n * sizeof(*buf));
    assert(buf);
    
    assert(buf);
	if (getcwd(buf, n) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
    
    char name[100];
    printf("Ingrese el nombre de la carpeta: ");
    scanf("%s", name);
    scanf("%c", &newline);

    if(path[0] != '/' || path[0] != '\0'){
	  strcat(buf,"/");
    }
     
    strcat(buf,path);
    strcat(buf,"/");
    strcat(buf,name);	
    
    // create a directory
    // mkdir(nombre,permisos de usuario)
    // 777 todos puedener leer, editar
    mkdir(name,0777);
    printf("Carpeta %s creada.\n", name);
}

void _ls(const char *dir,int op_a,int op_l)
{
    struct dirent *d;
    DIR *dh = opendir(dir);

    if (!dh)
	{
		if (errno = ENOENT)
		{
			//Si no se encuentra el directorio
			perror("No existe el directorio");
		}
		else
		{
			//si el directorio no se puede leer 
			perror("No se pudo leer el directorio");
		}
		exit(EXIT_FAILURE);
	}
    while ((d = readdir(dh)) != NULL)
	{
		//Si hay archivos ocultos continuamos 
		if (!op_a && d->d_name[0] == '.')
			continue;
		printf("%s\n", d->d_name);
		if(op_l) printf("\n");
	}

}

void eliminateDirectory()
{
    char name[100],o;
     char inst[100];

    printf("Ingrese el nombre de la carpeta: ");
    scanf("%s", name);
    scanf("%c", &newline);
    dir1=opendir(name);
   
     if(dir1!=NULL)
     {
        printf("Esto es lo que tiene actualmente en la carpeta:\n");
        _ls(name,0,0);
        printf("¿Desea Continuar?");
        printf("[S]i\t[N]o\n");
        scanf("%c",&o);
	if(o=='S' || o=='s'){
	   // delete a directory
	   sprintf(inst,"rm -rf %s",name);
    	   system(inst);
    	   printf("Carpeta %s eliminada.\n", name);
        }else{
	   printf("La carpeta no se eliminará\n"); 
	}      
     }
     else
     {
	printf("La carpeta no existe");
     }
}

void openDirectory()
{
    char name[100];
    char o;
    int opc;
    printf("Ingrese el nombre de la carpeta:");
    scanf("%s", name);
    scanf("%c", &newline);
    dir1=opendir(name);
    

    if(dir1==NULL)
	{
	   printf("Error al abrir carpeta\n");
	}

    printf("Carpeta %s abierta.\n",name);
    _ls(name,0,0);
    printf("¿Quiere crear un archivo dentro de esta carpeta?\n");
    printf("[S]i\t[N]o\n");
    scanf("%c",&o);

    if(o=='S' || o=='s')
    {
	// Se le pasa como parámetro el nombre de la carpeta
        Crear(name);
    }else if(o=='N' || o=='n')
    {
	printf("¿Quiere ver un archivo dentro de esta carpeta?\n");
        printf("Presione 1 para ver un archivo. En caso contrario presione 2\n");
        scanf("%d",&opc);   
	if(opc==1)
	{
	    Ver("/");            
	}else if(opc==2){
	   printf("No se hará alguna acción\n"); 
	}
    }else{
	printf("Opcion no valida\n");
    }
    printf("\n");
    printf("Ahora tiene lo siguiente dentro de la carpeta %s \n",name);
    _ls(name,0,0);
    closedir(dir1);
   
}

void main()
{
  do 
  {
    printf("\n\nPRACTICA 8\n\n");
    printf("\n1.CREAR DIRECTORIO\n2.CREAR ARCHIVO\n3.VER ARCHIVO\n4.VER DIRECTORIO\n5.APPEND\n6.ELIMINAR ARCHIVO\n7.ELIMINAR DIRECTORIO\n8.SALIR\n");
    printf("\nIngresa numero: ");
    scanf("%d",&m);
    switch(m)
    {
      case 1:
	createDirectory("/");
	break;

      case 2:
	  	// Solo se le pasa el parametro de la barra
		// Indicando que el archivo se creará
		// En la carpeta raiz del programa ejecutado
        Crear("/");
        break;

      case 3:
        Ver();
        break;
      
      case 4:
	openDirectory();
	break;

      case 5:
        Append();
        break;

      case 6:
        Eliminar("/");
        break;

      case 7:
	eliminateDirectory();
	break;

      case 8:
        exit(0);
    }
  }while(1);
}


