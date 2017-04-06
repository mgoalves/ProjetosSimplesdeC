Abstrair hora atual

char *Dia_Atual(void){
    int dia;
    struct tm *local;
    time_t t;
    t = time(NULL);
    local = localtime(&t);
    dia = local -> tm_mday;
    return dia;
}

char *Mes_Atual(void){
    int mes;
    struct tm *local;
    time_t t;
    t = time(NULL);
    local = localtime(&t);
    mes = local -> tm_mon + 1;
    return mes;
}

char *Ano__Atual(void){
    int ano;
    struct tm *local;
    time_t t;
    t = time(NULL);
    local = localtime(&t);
    ano = local -> tm_year + 1900;
    return ano;
}

char *Hora_Atual(void){
    int   hora;
    struct tm *local;
    time_t t;
    t = time(NULL);
    local = localtime(&t);
    hora   =   local -> tm_hour;
    return hora;
}

void *Minuto_Atual(void){
    int minuto;
    struct tm *local;
    time_t t;
    t = time(NULL);
    local = localtime(&t);
    minuto = local -> tm_min;
    return minuto;
}
