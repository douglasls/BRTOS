#include <msp430.h> 
#include <stdint.h>

/**
 * main.c
 */

uint16_t nRegTask = 0; // marca numero de tarefas a serem feitas
uint16_t TarefaAtual;

typedef struct{
    uint16_t *taskpointer;
    uint16_t *stackpointer;
    volatile uint16_t wait;
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

void wait( uint16_t wait)
{
    tarefas[TarefaAtual].wait = wait;
    while(tarefas[TarefaAtual].wait);
}

void IDLE()
{
    while(1);
}

void BlinkLED_RED(){
    P1DIR |= BIT0;

    while(1){
        wait(250);
        P1OUT ^= BIT0;
    }
}

void BlinkLED_GREEN(){
    P4DIR |= BIT7;
    while(1){
        wait(250);
        P4OUT ^= BIT7;
    }
}



__attribute__((naked))
__attribute__  ((interrupt(WDT_VECTOR)))
void WDT_ISR()
{
    int i;

    asm ("pushm.a #12, R15"); //salvar o contexto colocando os registradores na pilha
    asm("movx.a SP, %0" :  "=m" (tarefas[TarefaAtual].stackpointer) ); //mover o ponteiro da pilha para a pilha do escalonador



    for(i = 0; i < nRegTask; i++ ) //Decrementa um tick para cada tarefa
    {

        if(tarefas[i].wait > 0){
            tarefas[i].wait--;
        }
    }

    do {
            TarefaAtual = (TarefaAtual + 1) % nRegTask; // executar escalonador e nova tarefa
    } while(tarefas[TarefaAtual].wait > 0);

    asm("movx.a %0,SP" :: "m" (tarefas[TarefaAtual].stackpointer)); // salvando o ponteiro da pilha do escalonador
    asm ("popm.a #12, R15"); //restaura o contexto da nova tarefa
    asm ("RETI"); //Retorna da interrupção
}

void startBRTOS()
{
    WDTCTL = WDTPW | WDTSSEL__ACLK | WDTTMSEL | WDTIS_7;           // stop watchdog timer
    SFRIE1 |= WDTIE;

    __enable_interrupt();

    tarefas[0].stackpointer += 26;
    asm("movx.a %0,SP" :: "m" (tarefas[0].stackpointer));
    asm("movx.a %0, PC" :: "m" (tarefas[0].taskpointer));



}



int main(void)
{

    registerTask(BlinkLED_RED);
    registerTask(BlinkLED_GREEN);
    registerTask(IDLE);

    startBRTOS();

    while(1);

    return 0;
}

