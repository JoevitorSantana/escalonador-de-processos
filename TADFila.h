struct NoFila
{
    Processo info;
    NoFila *prox;
};

struct Fila
{
    NoFila *inicio, *fim;
};

struct Estatisticas {
    int processos_finalizados;
    int processos_bloqueados;
    int processos_alternados;
    float tempo_medio_bloqueio;
    int tempo_total_simulacao;
};

Fila *CriaFila (void) {
    Fila *fila = new Fila;
    fila->inicio = fila->fim = NULL;
    return fila;
}

void enqueue(Fila *fila, Processo valor) {
    NoFila *Novo = new NoFila;
    Novo->info = valor;
    Novo->prox = NULL;

    if (fila->fim != NULL)
        fila->fim->prox = Novo;
    else
        fila->inicio = Novo;
    
    fila->fim = Novo;
}

Processo dequeue(Fila *fila) {
    NoFila *Aux;
    Processo valor;

    if (fila->inicio != NULL) {
        Aux = fila->inicio;
        valor = Aux->info;
        fila->inicio = Aux->prox;
        
        if (fila->inicio == NULL)
            fila->fim = NULL;
        delete Aux;
    }
    return valor;
}

int isEmpty(Fila queue) {
    return (queue.inicio == NULL);
}

Processo primeiroDaFila(Fila F) {
    Processo valor;
    if (!isEmpty(F))
        valor = F.fim->info;
    return valor;
}
