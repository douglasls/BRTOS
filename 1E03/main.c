#include <msp430.h> 
#include <stdint.h>

/**
 * main.c
 */
 uint16_t nRegTask = 0; // marca numero de tarefas a serem feitas

typedef struct{
    uint16_t *taskpointer;
    uint16_t *stackpointer;
}task_t;

task_t tarefas[10];



void registerTask(void* tarefa)
{

//INICIALIZAÇÃO
    (tarefas[nRegTask].taskpointer) = tarefa;
    tarefas[nRegTask].stackpointer = (uint16_t *) 0x2800 + 0x80*nRegTask; //inicio da pilha

//SALVA PC
    tarefas[nRegTask].stackpointer--;
    *(tarefas[nRegTask].stackpointer) = (uint16_t) tarefa; //ponteiro????

//SALVA SR E BITS MAIS SIGNIFICATIVOS DE PC
    tarefas[nRegTask].stackpointer--;
    *(tarefas[nRegTask].stackpointer) = ((uint32_t)tarefa>>4) & 0xF000;
    *(tarefas[nRegTask].stackpointer) |= GIE;                            //SR


//REGISTRADORES
    tarefas[nRegTask].stackpointer = tarefas[nRegTask].stackpointer - 12*2;
    nRegTask++;

}

int main(void)
{
    WDTCTL = WDTPW | WDTSSEL__ACLK | WDTTMSEL | WDTIS_4;           // stop watchdog timer
    SFRIE1 |= WDTIE;

    __enable_interrupt();


    while(1);

    return 0;
}

__attribute__((naked))
__attribute__  ((interrupt(WDT_VECTOR)))
void escalonador() {

}
