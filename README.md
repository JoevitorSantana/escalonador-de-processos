# SISTEMAS OPERACIONAIS I - UNOESTE(FIPP)
## OPERATING SYSTEMS I - UNOESTE(FIPP)

## PROCESS LIFE CYCLE - CICLO DE VIDA DE PROCESSO

## INTRODUÇÃO
Este programa simula o comportamento de um escalonador de processos em um sistema operacional, incluindo a criação, escalonamento, bloqueio e desbloqueio de processos, além da interação entre processos pai e filho e a visualização do estado de cada um.
Foram utilizadas estruturas de filas para gerenciar os estados (pronto, espera e finalizado), demonstrando como um escalonador organiza os processos, equilibrando e controlando a execução e espera de cada um.

## INTRODUCTION
This program simulates the behavior of a process scheduler in an operating system, including the creation, scheduling, blocking, and unblocking of processes, as well as the interaction between parent and child processes and the visualization of each process's state.
Queue structures were used to manage the states (ready, waiting, and finished), demonstrating how a scheduler organizes processes, balancing and controlling the execution and waiting of each.

## ESTRUTURA DE DADOS
* **Processo**: Armazena todas as informações de um processo em execução.
    * **Process**: Stores all information of a running process.
* **Filas**: Simulam os diferentes estados no ciclo de vida de um processo, foram usadas 3 filas para gerenciar a transição dos processos entre os estados:
    * **Queues**: Simulate the different states in a process's life cycle; 3 queues were used to manage the transition of processes between states:
    * **Fila de Prontos**: Guarda os processos que estão prontos para executar.
        * **Ready Queue**: Holds processes that are ready to execute.
    * **Fila de Espera**: Contém os processos que foram bloqueados, essa fila é monitorada para identificar quando um processo pode ser desbloqueado e inserido na fila de prontos. 15]
        * **Waiting Queue**: Contains processes that have been blocked; this queue is monitored to identify when a process can be unblocked and reinserted into the ready queue. 15]
    * **Fila de Finalizados**: Possui todos os processos que completaram sua execução, a mesma auxilia na coleta de estatísticas do sistema.
        * **Finished Queue**: Contains all processes that have completed their execution, assisting in collecting system statistics.

## MANIPULAÇÃO DE FILAS (TADFila.h)
## QUEUE MANIPULATION (TADFila.h)

* **NoFila**: Nó individual da fila que contém um processo e um ponteiro para o próximo nó.
    * **QueueNode**: Individual queue node that contains a process and a pointer to the next node.
* **Fila**: Contém ponteiros para o início e fim da fila, permitindo a inserção e remoção de processos.
    * **Queue**: Contains pointers to the beginning and end of the queue, allowing insertion and removal of processes.
* As funções `CriaFila`, `enqueue`, `dequeue`, `isEmpty` e `primeiroDaFila`, fazem a adição, remoção e verificação do estado da fila.
    * The functions `CriaFila`, `enqueue`, `dequeue`, `isEmpty`, and `primeiroDaFila` perform the addition, removal, and status checking of the queue.

## FUNÇÕES UTILITÁRIAS (main.cpp)
## UTILITY FUNCTIONS (main.cpp)

* `Sortear`, `Desbloquear`, `Bloquear` e `CriarProcessoFilho`: utilizam valores aleatórios espelhando os sistemas operacionais.
    * `Sortear` (Draw), `Desbloquear` (Unblock), `Bloquear` (Block), and `CriarProcessoFilho` (CreateChildProcess): use random values mirroring operating systems.
* **Inicialização de processos**: A função `CriarProcesso` inicializa a estrutura processo com os parâmetros necessários. Já a função `GerarTempoCPU` gera um valor aleatório para o tempo de CPU de um processo.
    * **Process initialization**: The `CriarProcesso` (CreateProcess) function initializes the process structure with the necessary parameters. The `GerarTempoCPU` (GenerateCPUTime) function generates a random value for a process's CPU time.
* **Manipular Filas**: A função `InserirFilaDeProntos` faz a leitura do número de processos que serão criados e insere na fila de prontos. A função `Imprime` percorre uma fila e exibe os identificadores dos processos.
    * **Queue Manipulation**: The `InserirFilaDeProntos` (InsertReadyQueue) function reads the number of processes to be created and inserts them into the ready queue. The `Imprime` (Print) function traverses a queue and displays the process identifiers.

## CONTROLE DO SIMULADOR (Função Execucao)
## SIMULATOR CONTROL (Execution Function)

Uma das partes mais importantes da simulação é a função `execucao()`, ela gerencia o andamento dos processos ao longo da simulação, garantindo que cada um seja tratado de acordo com seu estado atual e o tempo de CPU disponível. A cada nova iteração a função verifica primeiro se algum processo que está na fila de espera pode ser desbloqueado e, assim, retornar à fila de prontos.
A função `execucao()` garante que os processos passem corretamente pelos seus estados (pronto, executando, bloqueado ou finalizado) respeitando a lógica de tempo e eventos. É a principal responsável por manter a ordem e a eficiência do simulador, imitando com fidelidade o comportamento de um escalonador em um sistema operacional.
Quando todos os processos são finalizados, o sistema apresenta um resumo com estatísticas importantes, como o tempo total de execução, o número de bloqueios ocorridos e quantas vezes os processos transitaram entre os diferentes estados.

One of the most important parts of the simulation is the `execucao()` (execution) function, which manages the progress of processes throughout the simulation, ensuring that each is handled according to its current state and available CPU time. With each new iteration, the function first checks if any process in the waiting queue can be unblocked and thus return to the ready queue.
The `execucao()` function ensures that processes correctly transition through their states (ready, executing, blocked, or finished), respecting time and event logic. It is primarily responsible for maintaining the order and efficiency of the simulator, faithfully imitating the behavior of a scheduler in an operating system.
When all processes are finalized, the system presents a summary with important statistics, such as total execution time, the number of blockages that occurred, and how many times processes transitioned between different states.

## CONCLUSÃO
## CONCLUSION

O comportamento do programa imita um sistema operacional real, onde os processos são constantemente alternados entre os estados de prontos, execução e bloqueio, enquanto o sistema gerencia esses estados de forma dinâmica e eficiente.

The program's behavior imitates a real operating system, where processes are constantly alternated between ready, execution, and blocked states, while the system manages these states dynamically and efficiently.