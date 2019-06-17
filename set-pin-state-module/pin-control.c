/*  
 *  pin-control.c - Módulo destinado a controlar el estado (H/L) de un pin a elección.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <bcm2835.h>        /* Needed for control Pi's GPIO */
#include <stdio.h>

/* Definicion de cantidad de pines a controlar */
#define NPINS 1

/* Definicion de pines */
#define PIN0 RPI_GPIO_P1_03
#define PIN1 RPI_GPIO_P1_05
#define PIN4 RPI_GPIO_P1_07
#define PIN7 RPI_GPIO_P1_26
#define PIN8 RPI_GPIO_P1_24
#define PIN9 RPI_GPIO_P1_21
#define PIN10 RPI_GPIO_P1_19
#define PIN11 RPI_GPIO_P1_23
#define PIN14 RPI_GPIO_P1_08
#define PIN15 RPI_GPIO_P1_10
#define PIN17 RPI_GPIO_P1_11
#define PIN18 RPI_GPIO_P1_12
#define PIN21 RPI_GPIO_P1_13
#define PIN22 RPI_GPIO_P1_15
#define PIN23 RPI_GPIO_P1_16
#define PIN24 RPI_GPIO_P1_18
#define PIN25 RPI_GPIO_P1_22

/* Funcion init, se ejecuta cuando se ejecuta "insmod" */
int init_module(void)
{
    int code = 0;

    /* Lista de pines a controlar, argumento de la funcion que controla los pines */
    int pin_list[NPINS] = {PIN0};

    /* Imprimimos mje para debug. Lo podemos ver en el dmesg */
	printk(KERN_INFO "Controlador de Pin instanciado.\n");

    /* Pasar la cantidad de pins a controlar y un vector los pines */
    code = pin_controller(pin_list);

    /* Si retornamos un nmb distinto 0, indica error.*/
    if(!code)
        return 0;
}

/* @param [in] indica el numero de pin que se quiere controlar 
 * @return [out] - 0 indica ejecucion normal del programa
 */
int pin_controller(int *pin_list)
{    
    /* Error handling */
    if (!bcm2835_init())
        return 1;
    
    /* Seteamos los pines pasados como argumentos como salida */
    for (int iter = 0, iter < NPINS, iter++)
        bcm2835_gpio_fsel(pin_list[iter], BCM2835_GPIO_FSEL_OUTP);

    /* Seteamos al primer pin de la lista en alto */
    bcm2835_gpio_write(pin_list[0], HIGH);

    /* Para setear a un en bajo ejecutamos: 
    bcm2835_gpio_write(pin_list[0], LOW);
    */

   bcm2835_close();

   return 0;
}

/* Funcion cleanup, se ejecuta cuando se ejecuta "rmmod" */
void cleanup_module(void)
{
	printk(KERN_INFO "Controlador de Pin removido.\n");
}

