/*
*
*   @autor JoevitorSantana
*
*   This script simulates the scheduler, with Ready, Running, Block Queues and preemptive behavior
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <windows.h>

#define QUANTUM 10
#define MAX_NOVOS_PROCESSOS 5

struct Processo
{
    int pid;
    int tempo_cpu;
    int pai; // 1 = Sim | 0 = Nao 
    int pid_pai;
    int tempo_total_execucao;
    int tempo_bloqueado;
    int tempo_em_execucao;
    int tempo_em_pronto;
    int vezes_bloqueado;
    int filhos_criados;
    int finalizado;
};

#include "TADFila.h"

int Sortear() { return rand() % 2; }

int Desbloquear() { return Sortear() && Sortear(); }

int Bloquear() { return Sortear() && Sortear(); }

int CriarProcessoFilho() { return Sortear() && Sortear(); }

int isPai(Processo processo) { return processo.pai; }

int ExisteEmProntos(int pidPai, Fila *prontos) {
    NoFila *aux = prontos->inicio;

    while (aux != NULL && aux->info.pid_pai != pidPai)
        aux = aux->prox;
    
    if (aux != NULL && aux->info.pid_pai == pidPai)
        return 1;
    return 0;
}

int ExisteEmEspera(int pidPai, Fila *espera) {
    NoFila *aux = espera->inicio;

    while (aux != NULL && aux->info.pid_pai != pidPai)
        aux = aux->prox;
    
    if (aux != NULL && aux->info.pid_pai == pidPai)
        return 1;
    return 0;
}

int PossuiFilhosAtivos(int pidPai, Fila *prontos, Fila *espera) {
    return ExisteEmProntos(pidPai, prontos) || ExisteEmEspera(pidPai, espera);
}

void Imprime(Fila *fila) {
    NoFila *aux;
    for (aux = fila->inicio; aux != NULL; aux = aux->prox)
        printf("%d ", aux->info.pid);
    printf("\n");
}

int GerarTempoCPU() {
    return (rand() % 50) + 1;
}

Processo CriarProcesso(int pid, int tempoCPU, int pai, int pidPai) {
    Processo novoProcesso;
    novoProcesso.pid = pid;
    novoProcesso.tempo_cpu = tempoCPU;
    novoProcesso.pai = pai;
    novoProcesso.pid_pai = pidPai;
    novoProcesso.tempo_total_execucao = 0;
    novoProcesso.tempo_bloqueado = 0;
    novoProcesso.tempo_em_execucao = 0;
    novoProcesso.tempo_em_pronto = 0;
    novoProcesso.vezes_bloqueado = 0;
    novoProcesso.filhos_criados = 0;
    novoProcesso.finalizado = 0;
    printf("Criando processo: %d - pai %d\n", novoProcesso.pid, novoProcesso.pid_pai);
    return novoProcesso;
}

void InicializarEstatisticas(Estatisticas *est) {
    est->processos_finalizados = 0;
    est->processos_bloqueados = 0;
    est->processos_alternados = 0;
    est->tempo_medio_bloqueio = 0;
    est->tempo_total_simulacao = 0;
}

void ProcessoBloqueado(Processo *p, int tempo_bloqueio, Estatisticas *est) {
    if (p->vezes_bloqueado < 1){ // Só atualiza a estatística se nunca foi bloqueado
        est->processos_bloqueados++;
    }
    p->vezes_bloqueado++;
    p->tempo_bloqueado += tempo_bloqueio;
    est->tempo_medio_bloqueio += tempo_bloqueio;
}

void ProcessoFinalizado(Processo *p, Estatisticas *est) {
    p->finalizado = 1;
    est->processos_finalizados++;
    
    if (p->tempo_em_execucao > 0 && p->tempo_em_pronto > 0 && p->vezes_bloqueado == 0) {
        est->processos_alternados++;
    }
}

void MostrarFilhosCriados(Fila *finalizados) {
    printf("\nQuantidade de filhos criados por processo:\n");
    
    bool nenhumFilho = true;
    NoFila *aux = finalizados->inicio;
    
    while (aux != NULL) {
        if (aux->info.filhos_criados > 0) {
            printf("Processo %d criou %d filhos\n", 
                   aux->info.pid, 
                   aux->info.filhos_criados);
            nenhumFilho = false;
        }
        aux = aux->prox;
    }
    
    if (nenhumFilho) {
        printf("Nenhum processo criou filhos durante a simulacao\n");
    }
}

void ProcessoFinalizado(Processo *p, Estatisticas *est, Fila *finalizados) {
    p->finalizado = 1;
    est->processos_finalizados++;
    
    if (p->tempo_em_execucao > 0 && p->tempo_em_pronto > 0 && p->vezes_bloqueado == 0) {
        est->processos_alternados++;
    }
    
    enqueue(finalizados, *p);  // Adiciona � fila de finalizados
}

void ExibirEstatisticas(Fila *prontos, Fila *espera, Fila *finalizados, Estatisticas *est) {
	
    printf("\n===== RELATORIO =====\n");
    
    printf("\nProcessos finalizados: %d\n", est->processos_finalizados);
    
    if (est->processos_bloqueados > 0) {
        est->tempo_medio_bloqueio /= est->processos_bloqueados;
        printf("Processos bloqueados: %d\n", est->processos_bloqueados);
        printf("Tempo medio de bloqueio: %.2f unidades de tempo\n", est->tempo_medio_bloqueio);
    } else {
        printf("Nenhum processo foi bloqueado.\n");
    }
    
    printf("Processos que alternaram entre execucao e pronto: %d\n", est->processos_alternados);
    
    
    NoFila *aux = finalizados->inicio;
    while (aux != NULL) {
        printf("Processo %d: %d unidades de tempo (%.1f%% execucao, %.1f%% pronto)\n", 
               aux->info.pid, 
               aux->info.tempo_total_execucao,
               (float)aux->info.tempo_em_execucao / aux->info.tempo_total_execucao * 100,
               (float)aux->info.tempo_em_pronto / aux->info.tempo_total_execucao * 100);
        aux = aux->prox;
    }
    
    aux = espera->inicio;
    while (aux != NULL) {
        printf("Processo %d: %d unidades de tempo (%.1f%% execucao, %.1f%% pronto, %.1f%% bloqueado)\n", 
               aux->info.pid, 
               aux->info.tempo_total_execucao,
               (float)aux->info.tempo_em_execucao / aux->info.tempo_total_execucao * 100,
               (float)aux->info.tempo_em_pronto / aux->info.tempo_total_execucao * 100,
               (float)aux->info.tempo_bloqueado / aux->info.tempo_total_execucao * 100);
        aux = aux->prox;
    }
    
    MostrarFilhosCriados(finalizados);
    
}

void Execucao(Fila *prontos, Fila *espera, Fila *finalizados, int &seqPid) {
    Estatisticas est;
    InicializarEstatisticas(&est);
    int novosProcessosFilhos = 0;

    while (!isEmpty(*prontos) || !isEmpty(*espera)) {
        est.tempo_total_simulacao++;
        
        // Atualiza tempos dos processos em espera
        NoFila *auxEspera = espera->inicio;
        while (auxEspera != NULL) {
            auxEspera->info.tempo_bloqueado++;
            auxEspera->info.tempo_total_execucao++;
            auxEspera = auxEspera->prox;
        }
        
        // Atualiza tempos dos processos em prontos
        NoFila *auxProntos = prontos->inicio;
        while (auxProntos != NULL) {
            auxProntos->info.tempo_em_pronto++;
            auxProntos->info.tempo_total_execucao++;
            auxProntos = auxProntos->prox;
        }

        // Verifica se pode desbloquear algum processo
        if (Desbloquear() && !isEmpty(*espera)) {
            Processo retiradoDeEspera;
            Processo primeiroBloqueado = primeiroDaFila(*espera);

            if (isPai(primeiroBloqueado) && PossuiFilhosAtivos(primeiroBloqueado.pid, prontos, espera)) {
                printf("Processo em bloqueio pid: %d ainda possui filhos!\n", primeiroBloqueado.pid);
                retiradoDeEspera = dequeue(espera);
                enqueue(espera, retiradoDeEspera);
            } else {
                retiradoDeEspera = dequeue(espera);
                enqueue(prontos, retiradoDeEspera);
                printf("Processo %d desbloqueado! encaminhado para fila de prontos!\n", retiradoDeEspera.pid);
                // ProcessoBloqueado(&retiradoDeEspera, retiradoDeEspera.tempo_bloqueado, &est);
            }
        }

        if (!isEmpty(*prontos)) {
            Processo emExecucao = dequeue(prontos);
            int tempoCorrido = 0;

            if (Bloquear()) {
                printf("Processo %d Enviado para espera!\n", emExecucao.pid);
                ProcessoBloqueado(&emExecucao, emExecucao.tempo_bloqueado, &est);
                enqueue(espera, emExecucao);
                continue;
            }

            if (CriarProcessoFilho() && novosProcessosFilhos < MAX_NOVOS_PROCESSOS) {
                enqueue(prontos, CriarProcesso((++seqPid), GerarTempoCPU(), 0, emExecucao.pid));
                novosProcessosFilhos++;
                emExecucao.filhos_criados++;
                emExecucao.pai = 1;
                printf("Enviando processo pai %d para espera\n", emExecucao.pid);
                ProcessoBloqueado(&emExecucao, emExecucao.tempo_bloqueado, &est);
                enqueue(espera, emExecucao);
                continue;
            }
        
            // Executa o processo
            while (emExecucao.tempo_cpu > 0 && tempoCorrido < QUANTUM) {
                emExecucao.tempo_cpu--;
                tempoCorrido++;
                emExecucao.tempo_em_execucao++;
                emExecucao.tempo_total_execucao++;
                printf("Executando processo %d - tempo decorrido: %d\n", emExecucao.pid, tempoCorrido);
                // Sleep(1000);
            }

            if (emExecucao.tempo_cpu > 0) {
                printf("Retorna para fila de prontos!\nTempo de CPU restante: %d\n", emExecucao.tempo_cpu);
                enqueue(prontos, emExecucao);
            } else {
                printf("Processo Finalizado!\n");
                ProcessoFinalizado(&emExecucao, &est, finalizados);  // Adiciona � fila de finalizados
            }
        }
    }

    ExibirEstatisticas(prontos, espera, finalizados, &est);
}

void InserirFilaDeProntos(Fila *prontos, int &seqPid) {
    int contProcessos = 0;
    int numProcessos;

    printf("Informe um numero de processos a serem criados: ");
    scanf("%d", &numProcessos);
    printf("\n");

    while (contProcessos < numProcessos) {
        enqueue(prontos, CriarProcesso((contProcessos + 1), GerarTempoCPU(), 0, 0));
        contProcessos++;
        ++seqPid;
    }
}

int main() {
    srand(time(NULL));
    
    Fila *prontos = CriaFila();
    Fila *espera = CriaFila();
    Fila *finalizados = CriaFila();
    int seq_pid = 0;

    InserirFilaDeProntos(prontos, seq_pid);
    Execucao(prontos, espera,finalizados, seq_pid);

    return 0;
}
