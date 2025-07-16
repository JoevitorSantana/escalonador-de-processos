# TRABALHO SISTEMAS OPERACIONAIS I - UNOESTE(FIPP)
# [cite_start]OPERATING SYSTEMS I WORK - UNOESTE(FIPP) [cite: 1]

## CICLO DE VIDA DE PROCESSO
## [cite_start]PROCESS LIFE CYCLE [cite: 1]

## INTRODUÇÃO
## [cite_start]INTRODUCTION [cite: 7]
[cite_start]Este programa simula o comportamento de um escalonador de processos em um sistema operacional, incluindo a criação, escalonamento, bloqueio e desbloqueio de processos, além da interação entre processos pai e filho e a visualização do estado de cada um. [cite: 8]
[cite_start]Foram utilizadas estruturas de filas para gerenciar os estados (pronto, espera e finalizado), demonstrando como um escalonador organiza os processos, equilibrando e controlando a execução e espera de cada um. [cite: 9]

[cite_start]This program simulates the behavior of a process scheduler in an operating system, including the creation, scheduling, blocking, and unblocking of processes, as well as the interaction between parent and child processes and the visualization of each process's state. [cite: 8]
[cite_start]Queue structures were used to manage the states (ready, waiting, and finished), demonstrating how a scheduler organizes processes, balancing and controlling the execution and waiting of each. [cite: 9]

## ESTRUTURA DE DADOS
## [cite_start]DATA STRUCTURE [cite: 10]

* [cite_start]**Processo**: Armazena todas as informações de um processo em execução. [cite: 11]
    * [cite_start]**Process**: Stores all information of a running process. [cite: 11]
* [cite_start]**Filas**: Simulam os diferentes estados no ciclo de vida de um processo, foram usadas 3 filas para gerenciar a transição dos processos entre os estados: [cite: 12]
    * **Queues**: Simulate the different states in a process's life cycle; [cite_start]3 queues were used to manage the transition of processes between states: [cite: 12]
    * [cite_start]**Fila de Prontos**: Guarda os processos que estão prontos para executar. [cite: 12]
        * [cite_start]**Ready Queue**: Holds processes that are ready to execute. [cite: 12]
    * [cite_start]**Fila de Espera**: Contém os processos que foram bloqueados, essa fila é monitorada para identificar quando um processo pode ser desbloqueado e inserido na fila de prontos. [cite: 13, 15]
        * [cite_start]**Waiting Queue**: Contains processes that have been blocked; this queue is monitored to identify when a process can be unblocked and reinserted into the ready queue. [cite: 13, 15]
    * [cite_start]**Fila de Finalizados**: Possui todos os processos que completaram sua execução, a mesma auxilia na coleta de estatísticas do sistema. [cite: 16]
        * [cite_start]**Finished Queue**: Contains all processes that have completed their execution, assisting in collecting system statistics. [cite: 16]

## MANIPULAÇÃO DE FILAS (TADFila.h)
## [cite_start]QUEUE MANIPULATION (TADFila.h) [cite: 17]

* [cite_start]**NoFila**: Nó individual da fila que contém um processo e um ponteiro para o próximo nó. [cite: 18]
    * [cite_start]**QueueNode**: Individual queue node that contains a process and a pointer to the next node. [cite: 18]
* [cite_start]**Fila**: Contém ponteiros para o início e fim da fila, permitindo a inserção e remoção de processos. [cite: 19]
    * [cite_start]**Queue**: Contains pointers to the beginning and end of the queue, allowing insertion and removal of processes. [cite: 19]
* [cite_start]As funções `CriaFila`, `enqueue`, `dequeue`, `isEmpty` e `primeiroDaFila`, fazem a adição, remoção e verificação do estado da fila. [cite: 20]
    * [cite_start]The functions `CriaFila`, `enqueue`, `dequeue`, `isEmpty`, and `primeiroDaFila` perform the addition, removal, and status checking of the queue. [cite: 20]

## FUNÇÕES UTILITÁRIAS (main.cpp)
## [cite_start]UTILITY FUNCTIONS (main.cpp) [cite: 21]

* [cite_start]`Sortear`, `Desbloquear`, `Bloquear` e `CriarProcessoFilho`: utilizam valores aleatórios espelhando os sistemas operacionais. [cite: 22]
    * [cite_start]`Sortear` (Draw), `Desbloquear` (Unblock), `Bloquear` (Block), and `CriarProcessoFilho` (CreateChildProcess): use random values mirroring operating systems. [cite: 22]
* [cite_start]**Inicialização de processos**: A função `CriarProcesso` inicializa a estrutura processo com os parâmetros necessários. [cite: 23] [cite_start]Já a função `GerarTempoCPU` gera um valor aleatório para o tempo de CPU de um processo. [cite: 24]
    * [cite_start]**Process initialization**: The `CriarProcesso` (CreateProcess) function initializes the process structure with the necessary parameters. [cite: 23] [cite_start]The `GerarTempoCPU` (GenerateCPUTime) function generates a random value for a process's CPU time. [cite: 24]
* [cite_start]**Manipular Filas**: A função `InserirFilaDeProntos` faz a leitura do número de processos que serão criados e insere na fila de prontos. [cite: 25] [cite_start]A função `Imprime` percorre uma fila e exibe os identificadores dos processos. [cite: 26]
    * [cite_start]**Queue Manipulation**: The `InserirFilaDeProntos` (InsertReadyQueue) function reads the number of processes to be created and inserts them into the ready queue. [cite: 25] [cite_start]The `Imprime` (Print) function traverses a queue and displays the process identifiers. [cite: 26]

## CONTROLE DO SIMULADOR (Função Execucao)
## [cite_start]SIMULATOR CONTROL (Execution Function) [cite: 27]

[cite_start]Uma das partes mais importantes da simulação é a função `execucao()`, ela gerencia o andamento dos processos ao longo da simulação, garantindo que cada um seja tratado de acordo com seu estado atual e o tempo de CPU disponível. [cite: 28] [cite_start]A cada nova iteração a função verifica primeiro se algum processo que está na fila de espera pode ser desbloqueado e, assim, retornar à fila de prontos. [cite: 29]
[cite_start]A função `execucao()` garante que os processos passem corretamente pelos seus estados (pronto, executando, bloqueado ou finalizado) respeitando a lógica de tempo e eventos. [cite: 30] [cite_start]É a principal responsável por manter a ordem e a eficiência do simulador, imitando com fidelidade o comportamento de um escalonador em um sistema operacional. [cite: 31]
[cite_start]Quando todos os processos são finalizados, o sistema apresenta um resumo com estatísticas importantes, como o tempo total de execução, o número de bloqueios ocorridos e quantas vezes os processos transitaram entre os diferentes estados. [cite: 32]

[cite_start]One of the most important parts of the simulation is the `execucao()` (execution) function, which manages the progress of processes throughout the simulation, ensuring that each is handled according to its current state and available CPU time. [cite: 28] [cite_start]With each new iteration, the function first checks if any process in the waiting queue can be unblocked and thus return to the ready queue. [cite: 29]
[cite_start]The `execucao()` function ensures that processes correctly transition through their states (ready, executing, blocked, or finished), respecting time and event logic. [cite: 30] [cite_start]It is primarily responsible for maintaining the order and efficiency of the simulator, faithfully imitating the behavior of a scheduler in an operating system. [cite: 31]
[cite_start]When all processes are finalized, the system presents a summary with important statistics, such as total execution time, the number of blockages that occurred, and how many times processes transitioned between different states. [cite: 32]

## CONCLUSÃO
## [cite_start]CONCLUSION [cite: 33]

[cite_start]O comportamento do programa imita um sistema operacional real, onde os processos são constantemente alternados entre os estados de prontos, execução e bloqueio, enquanto o sistema gerencia esses estados de forma dinâmica e eficiente. [cite: 34]

[cite_start]The program's behavior imitates a real operating system, where processes are constantly alternated between ready, execution, and blocked states, while the system manages these states dynamically and efficiently. [cite: 34]