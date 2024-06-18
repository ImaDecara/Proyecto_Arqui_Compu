#include <stdio.h>
#include <string.h> /* gets, strcmp */
#include <stdlib.h> /* system */
#include <conio.h> /* Para que tome el GETCH() */
#include <stdbool.h> /*Para usar bool*/
#include <windows.h>


#define CLAVE "1"
#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#define LONGITUD 5
#define MAX_INTENTOS 3
#define NUM_LEDS 8
#define DELAY_MS 200

#define DELAY_MS_DEFAULT 500
#define DELAY_INCREMENT 100
#define DELAY_MIN 100
#define DELAY_MAX 2000

#define NUMERO_USUARIOS 5

void menu() {
    system("cls");
    printf(" ------------------------------------------------------\n");
    printf(" P R O Y E C T O - A R Q U I. C O M P U T A D O R A\n");
    printf(" ------------------------------------------------------\n");
    printf("\n");
    printf("-> MENU DE OPCIONES <- \n");
    printf("\n");
    printf("1- Auto-Fantastico\n");
    printf("2- EL Choque\n");
    printf("3- Fuegos Artificiales\n");
    printf("4- Señal\n");
    printf("5- Salir\n");
}

bool controlContrasena() {
    char usuario[LONGITUD + 1];
    char clave[LONGITUD + 1];
    int intento = 0;
    int ingresa = 0;
    char caracter;
    int i = 0;

    /* Declaración e inicialización de arreglos de usuarios y claves */

    do {
        i = 0;
        system("cls");
        printf("\n\t\t\tINICIO DE SESION\n");
        printf("\t\t\t---------------\n");
        // Aquí podrías añadir la lógica para pedir el nombre de usuario si es necesario
        printf("\tCLAVE: ");
        while ((caracter = getch())) {
            if (caracter == TECLA_ENTER) {
                clave[i] = '\0';
                break;
            } else if (caracter == TECLA_BACKSPACE) {
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
            } else {
                if (i < LONGITUD) {
                    printf("*");
                    clave[i] = caracter;
                    i++;
                }
            }
        }

        /* El usuario y clave debe coincidir con alguno de los que se encuentran en el array */
        if (strcmp(clave, CLAVE) == 0) {
            ingresa = 1;
        } else {
            printf("\n\n\t\t\tCLAVE INCORRECTA\n");
            intento++;
            system("pause"); // o getchar();
        }

    } while (intento < MAX_INTENTOS && ingresa == 0);

    if (ingresa == 1) {
        printf("\n\n\t\t\tBienvenido al Sistema\n");
        return true;
    } else {
        printf("\n\n\t\t\tHa sobrepasado el numero maximo de intentos permitidos\n");
        return false;
    }
}

int ajustarDelay(int *delay) {
    if (_kbhit()) {
        int ch = _getch();
        if (ch == 224) {  // Detectar flechas
            ch = _getch();
            if (ch == 72) {  // Flecha hacia arriba
                *delay -= DELAY_INCREMENT;
                if (*delay < DELAY_MIN) *delay = DELAY_MIN;
            } else if (ch == 80) {  // Flecha hacia abajo
                *delay += DELAY_INCREMENT;
                if (*delay > DELAY_MAX) *delay = DELAY_MAX;
            } else if (ch == 77) {  // Flecha hacia la derecha
                return 1;  // Señal de salida
            }
        }
    }
    return 0;  // Continuar ejecutando
}

void estadoLeds(int num) {
    const char led[] = {14, 15, 10, 23, 24, 25, 8, 7}; // Debe declararse nuevamente aquí
    for (int i = 0; i < 8; i++) {
        int numval = (num >> i) & 0x01;
        //digitalWrite(led[i], numval);
    }
}

void mostrarSecuencia(unsigned char secuencia) {
    char ledConsola;
    int estadoLed;

    for (int i = NUM_LEDS - 1; i >= 0; --i) {
        if (secuencia & (1 << i)) {
            ledConsola = '*'; // LED encendido
        } else {
            ledConsola = '_'; // LED apagado
        }

        printf("%c ", ledConsola); // Muestra el estado del LED inmediatamente cuando se ejecuta "ledConsola"
    }
    printf("\n");
}

void autoFantastico() {
    printf("\nAUTO FANTASTICO: \n");
    char tablaAutoFantastico[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    int delay = DELAY_MS_DEFAULT;

    while (1) {
        for (int i = 0; i < 8; i++) {
            mostrarSecuencia(tablaAutoFantastico[i]);
            estadoLeds(tablaAutoFantastico[i]);
            Sleep(delay);
            if (ajustarDelay(&delay)) return;  // Salir si se presionó la flecha derecha
        }
        for (int i = 7; i != 0; i--) {
            mostrarSecuencia(tablaAutoFantastico[i]);
            estadoLeds(tablaAutoFantastico[i]);
            Sleep(delay);
            if (ajustarDelay(&delay)) return;  // Salir si se presionó la flecha derecha
        }
    }
}

void choque() {

    printf("\nCHOQUE: \n");
    char tablaChoque[] = {0x81, 0x42, 0x24, 0x10, 0x10, 0x24, 0x42, 0x81};
    for (int i = 0; i < 8; i++) {
        mostrarSecuencia(tablaChoque[i]);
        estadoLeds(tablaChoque[i]);
        Sleep(DELAY_MS);
    }
}

void fuegoArtifial(){

    printf("\nFUEGOS ARTIFICIALES: \n");
    char tablaChoque[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x14, 0x22, 0x41};
    for (int i = 0; i < 8; i++) {
        mostrarSecuencia(tablaChoque[i]);
        estadoLeds(tablaChoque[i]);
        Sleep(DELAY_MS);
    }
}

void prendeApaga() {
    unsigned char luces = 0xFF;
    for (int veces = 0; veces < 8; veces++) {
        mostrarSecuencia(luces);
        estadoLeds(luces);
        luces = ~luces;
        Sleep(DELAY_MS);
    }

}

int main() {
    int opcionMenu = 0, i=0;
    bool controlContra = false;

   /* pioInit();

    for(i=0; i<8; i++){
        pinMode(led[i], output);
    }
    leds(0xff);*/

    controlContra = controlContrasena();

    if (controlContra == true) {
        do{
            menu(); // Llamo al menú
            printf("\nIngrese una opcion: ");
            scanf("%d", &opcionMenu);

            switch (opcionMenu) {
                case 1:
                    autoFantastico();
                    break;
                case 2:
                    choque();
                    break;
                case 3:
                    fuegoArtifial();
                    break;
                case 4:
                    prendeApaga();
                    break;
                case 5:
                    exit(0);
                    break;
                default:
                    printf("Opcion no valida. Intente nuevamente.\n");
            }
            system("pause");

        }while(opcionMenu != 5);

    } else {
        exit(0);
    }

    return 0;
}
