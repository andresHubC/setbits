#include <stdio.h>

#define MSIZE 4	 /* Tamaño del arreglo utilizado para leer los datos que se le piden al usuario. */
#define MAXP 7	 /* Posicion mas alta del bit inicial, ingresada por el usuario. */
#define MAXB 8	 /* Maximo valor de n que puede ingresar el usuario. */
#define HVAL 255 /* Valor maximo que puede tomar las variables x, y. */
#define LVAL 0 	 /* Valor minimo que puede tomar las variables x, y, n, p. */
#define ON 1
#define OFF 0 

void LeerNum(char cad[], int);
int ctoi(char cad[]);
int setbits(int, int, int, int);
int VerifNumero(int, int, int);

int main(void)
{
	int x, y, p, n, err; 	/* err notifica al programa cuando hay un error al convertir un numero ingresado */
	char cad[MSIZE];
	printf("El programa realiza el encendido de un \"n\" numero de bits en una variable entera \"x\".\n"
			"El encendido de bits en x comienza desde la posicion de bit \"p\".\n"
			"Los n bits encendidos en x son respecto a los n bits a la derecha de la variable entera \"y\".\n");
	printf("El valor de \"x\" y \"y\" son ingresados por el usuario. Los valores permitidos para estas variables son de %d - %d.\n", LVAL, HVAL);
	printf("El valor de \"n\" es ingresado por el usuario. El valor de n esta entre %d - %d.\n", LVAL, MAXB);
	printf("El valor de \"p\" es ingresado por el usuario. La posicion #%d es la menos significativa y la #%d es la mas significativa.\n\n", LVAL, MAXP);
	do {
		printf("Ingresa el valor de x:");
		LeerNum(cad, MSIZE);
		x = ctoi(cad);
		err = VerifNumero(x, LVAL, HVAL);
		if (err == ON) {
			if (cad[0])
				printf("ERROR: El valor de x: %s es invalido, debe ser un valor entero entre %d - %d.\n", cad, LVAL, HVAL);
			else
				printf("ERROR: No ingresaste el numero.\n");
		}
	}
	while (err == ON); 
	do {
		printf("Ingresa el valor de y:");
		LeerNum(cad, MSIZE);
		y = ctoi(cad);
		err = VerifNumero(y, LVAL, HVAL);
		if (err == ON) {
			if (cad[0])
				printf("ERROR: El valor de y: %s es invalido, debe ser un valor entero entre %d - %d.\n", cad, LVAL, HVAL);
			else
				printf("ERROR: No ingresaste el numero.\n");
		}
	}
	while (err == ON);
	do {
		printf("Ingresa la posicion del bit inicial:");
		LeerNum(cad, MSIZE - 2);
		p = ctoi(cad);
		err = VerifNumero(p, LVAL, MAXP);
		if (err == ON) {
			if (cad[0])
				printf("El valor de p: %s es invalido, debe ser un valor entero entre %d - %d.\n", cad, LVAL, MAXP);
			else
				printf("ERROR: No ingresaste el numero.\n");
		}
	}
	while (err == ON);
	do {
		printf("Ingresa el valor de n:");
		LeerNum(cad, MSIZE - 2);
		n = ctoi(cad);
		err = VerifNumero(n, LVAL, MAXB);
		if (err == ON) {
			if (cad[0])
				printf("El valor de n: %s es invalido, debe ser un valor entero entre %d - %d.\n", cad, LVAL, MAXB);
			else
				printf("ERROR: No ingresaste el numero.\n");
		}
		else if (n > p + 1) {
			err = ON;
			printf("No se pueden encender %d bits desde la posicion del bit %d en la variable x.\n", n, p);
		}
	}
	while (err == ON);
	printf("\nDatos ingresados:\nx:%d\ny:%d\nPosicion inicial:%d\nnumero de bits:%d\n\n", x, y, p, n);
	x = setbits(x, p, n, y);
	printf("El valor de x despues de encender los bits especificados es: %d", x); 
	return 0; 
}

/* LeerNum: Lee la linea ingresada por el usuario. msize indica la cantidad de caracteres almacenados en cad[] */
void LeerNum(char cad[], int msize)
{
	int c, i = 0;
	
	while ((c = getchar()) == ' ' || c == '\t')	  /* Se ignoran los espacios en blanco al inicio de un numero */
		;
	/* Se ignoran los ceros al inicio de un numero y posibles espacios en blanco despues de este digito */
	while (c == '0' || c == ' ' || c == '\t')	 
		if ((c = getchar()) == '\n')			  /* Se guarda el valor nulo en caso de leer el final de linea */
			cad[i++] = '0';
	while (c != '\n') {
		if (i < msize - 1 && c != ' ' && c != '\t') 	
			cad[i++] = c;
		c = getchar();
	}
	cad[i] = '\0';
}

/*VerifNumero: Comprueba que val este entre el rango dado por low - high */
int VerifNumero(int val, int low, int high)
{
	if (val >= low && val <= high)
		return 0;
	else
		return 1;
}

/* ctoi: Convierte la cadena numerica en un numero entero */
int ctoi(char cad[])
{
	int i, num;
	
	num = i = 0;
	if (cad[i] == '\0')		/* Se notifica del error al recibir una cadena nula */
		num = -1;
	for ( ; cad[i] >= '0' && cad[i] <= '9'; i++)
		num = 10 * num + (cad[i] - '0');
	if (cad[i] != '\0')
		num = -1;			/* Se notifica del error al encontrar un caracter que no es digito */
	return num;
}

/* setbits: Enciende los n bits en x, comenzando desde la posicion p, a partir de los ultimos n bits en y */
int setbits(int x, int p, int n, int y)
{
	return x | (y & ~(~0 << n)) << (p + 1 - n);
}