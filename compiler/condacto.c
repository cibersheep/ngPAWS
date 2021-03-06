
#include "config.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#if (defined(__MSDOS__))||(defined(WIN32))
#include "VisualStudio/dirent/dirent.h"
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#include <dirent.h>
#endif


#include "condacto.h"
#include "errores.h"

#include "comun.h"

TipoCondacto condactos[NUMCONDACTS+USERCONDACTS];

TipoCondacto condactos_estandar[NUMCONDACTS] = {
  {"sinCondacto", condicion, nada, nada, nada, aNada}
  ,
  {"AT", condicion, locno, nada, nada, aNada}
  ,
  {"NOTAT", condicion, locno, nada, nada, aNada}
  ,
  {"ATGT", condicion, locno, nada, nada, aNada}
  ,
  {"ATLT", condicion, locno, nada, nada, aNada}
  ,
  {"PRESENT", condicion, objno, nada, nada, aNada}
  ,
  {"ABSENT", condicion, objno, nada, nada, aNada}
  ,
  {"WORN", condicion, objno, nada, nada, aNada}
  ,
  {"NOTWORN", condicion, objno, nada, nada, aNada}
  ,
  {"CARRIED", condicion, objno, nada, nada, aNada}
  ,
  {"NOTCARR", condicion, objno, nada, nada, aNada}
  ,
  {"CHANCE", condicion, percent, nada, nada, aNada}
  ,
  {"ZERO", condicion, flagno, nada, nada, aNada}
  ,
  {"NOTZERO", condicion, flagno, nada, nada, aNada}
  ,
  {"EQ", condicion, flagno, value, nada, aNada}
  ,
  {"GT", condicion, flagno, value, nada, aNada}
  ,
  {"LT", condicion, flagno, value, nada, aNada}
  ,
  {"ADJECT1", condicion, adjective, nada, nada, aNada}
  ,
  {"ADVERB", condicion, adverb, nada, nada, aNada}
  ,
  {"TIMEOUT", condicion, nada, nada, nada, aNada}
  ,
  {"ISAT", condicion, objno, locno_, nada, aNada}
  ,
  {"PREP", condicion, preposition, nada, nada, aNada}
  ,
  {"NOUN2", condicion, noun, nada, nada, aNada}
  ,
  {"ADJECT2", condicion, adjective, nada, nada, aNada}
  ,
  {"SAME", condicion, flagno, flagno, nada, aNada}
  ,
  {"NOTEQ", condicion, flagno, value, nada, aNada}
  ,
  {"NOTSAME", condicion, flagno, flagno, nada, aNada}
  ,
  {"ISNOTAT", condicion, objno, locno_, nada, aNada}
  ,
  {"INVEN", accion, nada, nada, nada, aFinDeTabla}
  ,
  {"DESC", accion, nada, nada, nada, aDescribir}
  ,
  {"QUIT", waitkey, nada, nada, nada, aNada}
  ,
  {"END", accion, nada, nada, nada, aEnd}
  ,
  {"DONE", accion, nada, nada, nada, aFinDeTabla}
  ,
  {"OK", accion, nada, nada, nada, aFinDeTabla}
  ,
  {"ANYKEY", waitkey, nada, nada, nada, aNada}
  ,
  {"GETKEY", waitkey, flagno, nada, nada, aNada}
  ,
  {"SAVE", accion, nada, nada, nada, aDescribir}
  ,
  {"LOAD", accion, nada, nada, nada, aDescribir}
  ,
  {"TURNS", accion, nada, nada, nada, aNada}
  ,
  {"SCORE", accion, nada, nada, nada, aNada}
  ,
  {"CLS", accion, nada, nada, nada, aNada}
  ,
  {"DROPALL", accion, nada, nada, nada, aNada}
  ,
  {"AUTOG", accion, nada, nada, nada, aCondicional}
  ,
  {"AUTOD", accion, nada, nada, nada, aCondicional}
  ,
  {"AUTOW", accion, nada, nada, nada, aCondicional}
  ,
  {"AUTOR", accion, nada, nada, nada, aCondicional}
  ,
  {"PAUSE", waitkey, value, nada, nada, aNada}
  ,
  {"GOTO", accion, locno, nada, nada, aNada}
  ,
  {"MESSAGE", accion, mesno, nada, nada, aNada}
  ,
  {"REMOVE", accion, objno, nada, nada, aCondicional}
  ,
  {"GET", accion, objno, nada, nada, aCondicional}
  ,
  {"DROP", accion, objno, nada, nada, aCondicional}
  ,
  {"WEAR", accion, objno, nada, nada, aCondicional}
  ,
  {"DESTROY", accion, objno, nada, nada, aNada}
  ,
  {"CREATE", accion, objno, nada, nada, aNada}
  ,
  {"SWAP", accion, objno, objno, nada, aNada}
  ,
  {"PLACE", accion, objno, locno_, nada, aNada}
  ,
  {"SET", accion, flagno, nada, nada, aNada}
  ,
  {"CLEAR", accion, flagno, nada, nada, aNada}
  ,
  {"PLUS", accion, flagno, value, nada, aNada}
  ,
  {"MINUS", accion, flagno, value, nada, aNada}
  ,
  {"LET", accion, flagno, value, nada, aNada}
  ,
  {"NEWLINE", accion, nada, nada, nada, aNada}
  ,
  {"PRINT", accion, flagno, nada, nada, aNada}
  ,
  {"SYSMESS", accion, smesno, nada, nada, aNada}
  ,
  {"COPYOF", accion, objno, flagno, nada, aNada}
  ,
  {"COPYOO", accion, objno, objno, nada, aNada}
  ,
  {"COPYFO", accion, flagno, objno, nada, aNada}
  ,
  {"COPYFF", accion, flagno, flagno, nada, aNada}
  ,
  {"LISTOBJ", accion, nada, nada, nada, aNada}
  ,
  {"RAMSAVE", accion, nada, nada, nada, aNada}
  ,
  {"RAMLOAD", accion, flagno, nada, nada, aNada}
  ,
  {"BELL", accion, nada, nada, nada, aNada}
  ,
  {"ADD", accion, flagno, flagno, nada, aNada}
  ,
  {"SUB", accion, flagno, flagno, nada, aNada}
  ,
  {"PARSE", condicion, nada, nada, nada, aNada}
  ,
  {"LISTAT", accion, locno_, nada, nada, aNada}
  ,
  {"LISTNPC", accion, locno_, nada, nada, aNada}
  ,
  {"PROCESS", accion, prono, nada, nada, aNada}
  ,
  {"MES", accion, mesno, nada, nada, aNada}
  ,
  {"MODE", accion, value, nada, nada, aNada}
  ,
  {"TIME", accion, value, value, nada, aNada}
  ,
  {"DOALL", accion, locno_, nada, nada, aFinDeTabla}
  ,
  {"PROMPT", accion, smesno, nada, nada, aNada}
  ,
  {"WEIGH", accion, objno, flagno, nada, aNada}
  ,
  {"PUTIN", accion, objno, locno, nada, aCondicional}
  ,
  {"TAKEOUT", accion, objno, locno, nada, aCondicional}
  ,
  {"NEWTEXT", accion, nada, nada, nada, aNada}
  ,
  {"ABILITY", accion, value, value, nada, aNada}
  ,
  {"WEIGHT", accion, flagno, nada, nada, aNada}
  ,
  {"RANDOM", accion, flagno, nada, nada, aNada}
  ,
  {"WHATO", accion, nada, nada, nada, aNada}
  ,
  {"RESET", accion, locno, nada, nada, aDescribir}
  ,
  {"PUTO", accion, locno_, nada, nada, aNada}
  ,
  {"NOTDONE", accion, nada, nada, nada, aFinDeTabla}
  ,
  {"AUTOP", accion, locno, nada, nada, aCondicional}
  ,
  {"AUTOT", accion, locno, nada, nada, aCondicional}
  ,
  {"MOVE", condicion, flagno, nada, nada, aNada}
  ,
/* ZX Spectrum condacts*/
  {"EXTERN", accion, string, nada, nada, aNada} // Extern now runs javascript string
  ,
  {"PAPER", accion, value, nada, nada, aNada}
  ,
  {"INK", accion, value, nada, nada, aNada}
  ,
  {"BORDER", accion, value, nada, nada, aNada}
  ,
  {"CHARSET", accion, value, nada, nada, aNada}
  ,
  {"LINE", accion, value, nada, nada, aNada}
  ,
  {"PICTURE", accion, value, nada, nada, aNada}
  ,
  {"GRAPHIC", accion, value, nada, nada, aNada}
  ,
  {"INPUT", accion, value, nada, nada, aNada}
  ,
  {"SAVEAT", accion, nada, nada, nada, aNada}
  ,
  {"BACKAT", accion, nada, nada, nada, aNada}
  ,
  {"PRINTAT", accion, value, value, nada, aNada}
  ,
  {"PROTECT", accion, nada, nada, nada, aNada}
  ,
  {"BEEP", accion, value, value, value, aNada}
  ,
  /* Inherited from Paguagl�s */
  {"SOUND", accion, value, nada, nada, aNada}
  ,
  /* Inherited from Supergl�s */
  {"OZERO", condicion, objno, value, nada, aNada}
  ,
  {"ONOTZERO", condicion, objno, value,  nada,aNada}
  ,
  {"OSET",  accion, objno, value, nada, aNada}
  ,
  {"OCLEAR",  accion, objno, value, nada, aNada}
  ,
  {"ISLIGHT",  condicion, nada, nada, nada, aNada}
  ,
  {"ISNOTLIGHT",  condicion, nada, nada, nada, aNada}
  ,
  {"DEBUG",  accion, value, nada, nada, aNada}
  ,
  {"WRITE",  accion, string, nada, nada, aNada}
  ,
  {"TRANSCRIPT",  accion, value, nada, nada, aNada}
  ,
  {"VERSION",  accion, nada, nada, nada, aNada}
  ,
  {"WRITELN",  accion, string, nada, nada, aNada}
  ,
  {"RESTART",  accion, nada, nada, nada, aNada}
  ,
  // New ngPAWS condacts:  blocks
  {"}",  blockEnd, nada, nada, nada, aNada}
  ,
  {"{",  blockStart, nada, nada, nada, aNada}
};


int ultimo_condacto;

char libFile[2024];

FILE *fplugin;

int
BuscarCondacto (const char *nombre, TipoCondacto * condacto, int mustBeCondition)
{
  int i;

  for (i = 0; i <= ultimo_condacto && strcmp (nombre, condactos[i].nombre); i++);
  if (i == ultimo_condacto+1)
    return FALSE;

  // Sharp condacts and colon condacts must be conditions
  if (mustBeCondition)  if ((condactos[i].tipo != mixto) && (condactos[i].tipo != condicion)) return FALSE;
  condacto->tipo = condactos[i].tipo;
  condacto->tipoArg1 = condactos[i].tipoArg1;
  condacto->tipoArg2 = condactos[i].tipoArg2;
  condacto->tipoArg3 = condactos[i].tipoArg3;
  return i;
};
void CargarDefinicionCondacto(char *fichero, int isLocal)
{
	FILE *f;
	char linea[32768];
	char bloque[32768];
	int inicial;
	int i , value;
	
	char *fullname;

	fullname = (char *)malloc(strlen(fichero)+6);
	fullname = strcpy(fullname, "/jsl/");
	strcat(fullname, fichero);

	if (!isLocal) strcpy(libFile,wd); else strcpy(libFile, path_archivo);
	strcat(libFile,fullname);

	
	f = fopen(libFile,"rt");
	fgets(linea,32768,f);
	if (linea[0]!=47) error(errGeneral,3);
	if (linea[1]!=47) error(errGeneral,3);
	ultimo_condacto++;
	inicial = 2;
	/* Get plugin type */
	for (i=inicial;(linea[i]!=0)&&(linea[i]!=32)&&(i<32768);i++) {};

	strncpy (bloque, linea+inicial, i-inicial);
	bloque[i-inicial]=0;
	inicial=i+1;

	if (strlen(bloque)<3) error(errGeneral,3);

	if (strcmp(bloque,"LIB")==0) /* It's a library plugin */
	{
		ultimo_condacto--;
	}

	else 

	if (strcmp(bloque,"CND")==0) /* It's a condact plugin */
	{

		/* Get condact name */
		for (i=inicial;(linea[i]!=0)&&(linea[i]!=32)&&(i<32768);i++) {};

		strncpy (bloque, linea + inicial, i - inicial);
		bloque[i - inicial]=0;
		inicial=i+1;
	
		if (strlen(bloque)<1) error(errGeneral,3);


		condactos[ultimo_condacto].nombre = (char *)malloc(strlen(bloque)+1);
		strcpy(condactos[ultimo_condacto].nombre, bloque);

		/* Get condact type */
		for (i=inicial;(linea[i]!=0)&&(linea[i]!=32)&&(i<32768);i++) {};

		strncpy (bloque, linea+inicial, i-inicial);
		bloque[i-inicial]=0;
		inicial=i+1;

		if (strlen(bloque)!=1) error(errGeneral,3);

		switch (toupper(bloque[0])) 
		{
		case 65 : condactos[ultimo_condacto].tipo = accion;  //A
				   break;
		case 67 : condactos[ultimo_condacto].tipo = condicion; //C
				   break;
		case 87 : condactos[ultimo_condacto].tipo = waitkey; //W
				   break;
		case 77 : condactos[ultimo_condacto].tipo = mixto; //M
				   break;

		default : error(errGeneral,3); 
		}

		/* Get param 1 */
		for (i=inicial;(linea[i]!=0)&&(linea[i]!=32)&&(i<32768);i++) {};

		strncpy (bloque, linea+inicial, i-inicial);
		bloque[i-inicial]=0;
		inicial=i+1;

		if (strlen(bloque)<1) error(errGeneral,3);

		value = atoi(bloque);
    
		condactos[ultimo_condacto].tipoArg1 = value;

		/* Get param 2 */
		for (i=inicial;(linea[i]!=0)&&(linea[i]!=32)&&(i<32768);i++) {};

		strncpy (bloque, linea+inicial, i-inicial);
		bloque[i-inicial]=0;
		inicial=i+1;

		if (strlen(bloque)<1) error(errGeneral,3);

		value = atoi(bloque);
    
		condactos[ultimo_condacto].tipoArg2 = value;

		/* Get param 3 */
		for (i=inicial;(linea[i]!=0)&&(linea[i]!=32)&&(i<32768);i++) {};

		strncpy (bloque, linea+inicial, i-inicial);
		bloque[i-inicial]=0;
		inicial=i+1;

		if (strlen(bloque)<1) error(errGeneral,3);

		value = atoi(bloque);
    
		condactos[ultimo_condacto].tipoArg3 = value;


		/* Get termination type */
		for (i=inicial;(linea[i]!=0)&&(linea[i]!=32)&&(i<32768);i++) {};

		strncpy (bloque, linea+inicial, i-inicial);
		bloque[i-inicial]=0;
		inicial=i+1;

		if (strlen(bloque)<1) error(errGeneral,3);

		value = atoi(bloque);
    
		condactos[ultimo_condacto].limpieza = value;
	}
	else
	{
		error(errGeneral,3); /* It wasn't LIB nor CND */
	}

	fputs(linea,fplugin); /* Copy rest of file to plugins.js file */
  
  
    while (fgets (linea, 32768, f))
	{
	  fputs (linea, fplugin);
	}
    fputs("\n",fplugin);


	fclose(f);

	free(fullname);
}

void LoadPluginCondacts ()
{
	

   DIR *dir;
   struct dirent *ent;
   
   strcpy(libFile,wd);
   strcat(libFile,"/jsl/plugin.js");

   fplugin = fopen(libFile,"wt");
   if (fplugin == NULL)    error(errGeneral,2);
   fputs("\n//   PLUGINS    ;\n\n",fplugin);

   ultimo_condacto = NUMCONDACTS - 1;

  // global plugins
  strcpy(libFile,wd);
  strcat(libFile,"/jsl/");
  if ((dir = opendir(libFile)) == NULL)
   {
     error(errGeneral,3);
   }
   while ((ent = readdir(dir)) != NULL)
   {
		if (strstr(ent->d_name,".jsp")!=NULL)
		if (strstr(ent->d_name,".jsp~")==NULL)
		{
			printf("Loading plugin %s\n",ent->d_name);
			CargarDefinicionCondacto(ent->d_name, 0);
		}
   }
	printf("\n");
   
   if (closedir(dir) != 0)
   	   error(errGeneral,2);


  // local plugins
  strcpy(libFile, path_archivo);
  strcat(libFile,"/jsl/");
  if ((dir = opendir(libFile)) != NULL)
  {
	  printf("Local plugin folder found...\n");
	  while ((ent = readdir(dir)) != NULL)
	   {
			if (strstr(ent->d_name,".jsp")!=NULL)
			if (strstr(ent->d_name,".jsp~")==NULL)
			{
				printf("Loading local plugin %s\n",ent->d_name);
				CargarDefinicionCondacto(ent->d_name, 1);
			}
	   }
	  printf("\n");
   
	  if (closedir(dir) != 0)
   	   error(errGeneral,2);
  }


   fclose(fplugin);
}
	

void
InitializeCondacts()
{
	int i;
	for (i=0;i<NUMCONDACTS;i++)
 	 condactos[i] = condactos_estandar[i];
	/* Fill condact names with empty strings so we are sure there will be not a match when comparing */
	for (i = NUMCONDACTS; i < NUMCONDACTS+USERCONDACTS; i++) condactos[i].nombre = ""; 
	LoadPluginCondacts();
	return;
}


