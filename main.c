#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define FALSE 1
#define TRUE 0
#define DELIMITADORES ";";

typedef struct _cliente
{
    int numero;
    char *nome;
    char *telefone;
    float maxcred;
    struct _cliente *next;
}cliente;

cliente *head=NULL;

void imprimelista()
{
    cliente *ptr;
    ptr=head;
    printf("***Dados dos clientes***\n");

    while(ptr!=NULL)
        {
            printf("-----------------------------------------\n");
            printf("Numero: %d\n",ptr->numero);
            printf("Nome: %s\n",ptr->nome);
            printf("Contacto telefonico: %s\n",ptr->telefone);
            printf("Valor maximo de credito: %.2f\n",ptr->maxcred);
            printf("-----------------------------------------\n");
            ptr=ptr->next;
        }
}

char verifica_conteudo()
{
    if (head!=NULL)
    {
        return FALSE;
    }
    return TRUE;
}

void criar_cliente()
{
    int numero;
    char nome[51];
    char telefone[14];
    float maxcred;

    FILE *fp;
    fp = fopen("dados.txt","a");

    cliente *ptr;
    cliente *ptraux;

    printf("Numero de cliente: ");
    scanf("%d", &numero);
    fflush(stdin);

    printf("Nome do cliente: ");
    scanf("%50[^\n]", nome);
    fflush(stdin);

    printf("Contacto telefonico do cliente: ");
    scanf("%13[^\n]", telefone);
    fflush(stdin);

    printf("Valor maximo de credito do cliente: ");
    scanf("%f", &maxcred);
    fflush(stdin);

    ptr=(cliente*)malloc(sizeof(cliente));

    if(ptr!=NULL)
    {
        ptr->numero=numero;
        ptr->nome=(char*)malloc(sizeof(char)*(strlen(nome)+1));

        if(ptr->nome==NULL)
        {
            printf("Nao foi possivel guardar o nome!\n");
        }
        strcpy(ptr->nome,nome);

        ptr->telefone=(char*)malloc(sizeof(char)*(strlen(telefone)+1));

        if(ptr->telefone==NULL)
        {
            printf("Nao foi possivel guardar o numero de telefone!\n");
        }
        strcpy(ptr->telefone,telefone);

        ptr->maxcred=maxcred;
        ptr->next=NULL;
    }
    else
    {
        printf("Memoria nao alocada!\n");
        free(ptr);
        return;
    }

    if(head==NULL)
    {
        ptr->next=NULL;
        head=ptr;
    }
    else
    {
        if(head->numero==ptr->numero)
        {
        printf("Este numero ja foi associado a outro cliente!\n");
        return;
        }

        else
        {
            ptraux=head;

            while(ptraux->next!=NULL)
            {
                ptraux=ptraux->next;
                if(ptraux->numero==ptr->numero)
                {
                    printf("Este numero ja foi associado a outro cliente!\n");
                    return;
                }
            }
            ptraux->next=ptr;
            ptr->next=NULL;
        }
    }
    fprintf(fp, "%d;%s;%s;%.2f\n", ptr->numero, ptr->nome, ptr->telefone, ptr->maxcred);
    fclose(fp);
}

void eliminar_cliente()
{
    cliente *ptr;
    cliente *ptraux;
    int numero;

    printf("Insira o numero do cliente que pretende apagar: ");
    scanf("%d", &numero);
    fflush(stdin);

    if(head==NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    ptraux=head;

    while(ptraux->numero!=numero)
    {
        if(ptraux->next==NULL)
        {
            printf("\nCliente nao encontrado\n");
            return;
        }
        else
        {
            ptr=ptraux;
            ptraux=ptraux->next;
        }
    }
    if(ptraux==head)
    {
        head=head->next;
    }
    else
    {
        ptr->next=ptraux->next;
    }
    free(ptraux);
}

void alterar_nome()
{
    cliente *ptraux = head;
    char nome[51];
    int numero;

    printf("Insira o numero do cliente ao qual pretende alterar dados: ");
    scanf("%d", &numero);
    fflush(stdin);

    if(head == NULL)
    {
        printf("\nLista Vazia...\n");
        return;
    }

    while(ptraux->numero!=numero)
    {
        if (ptraux->next==NULL)
        {
            printf("\nCliente nao encontrado\n");
            return;
        }
        ptraux = ptraux->next;
    }
    printf("\nInsira o novo nome para o cliente numero %d: ",ptraux->numero);
    scanf("%50[^\n]", nome);
    fflush(stdin);
    strcpy(ptraux->nome,nome);
}

void alterar_telefone()
{
    cliente *ptraux = head;
    char telefone[14];
    int numero;

    printf("Insira o numero do cliente ao qual pretende alterar dados: ");
    scanf("%d", &numero);
    fflush(stdin);

    if(head == NULL)
    {
        printf("\nLista Vazia...\n");
        return;
    }

    while(ptraux->numero != numero)
    {
        if (ptraux->next == NULL)
        {
            printf("\nCliente nao encontrado\n");
            return;
        }
        ptraux = ptraux->next;
    }
    printf("\nInsira o novo contacto telefonico para o cliente numero %d:",ptraux->numero);
    scanf("%13[^\n]", telefone);
    fflush(stdin);

   strcpy(ptraux->telefone,telefone);
}

void alterar_maxcred()
{
    cliente *ptraux = head;
    int numero;
    float maxcred;

    printf("Insira o numero do cliente ao qual pretende alterar dados: ");
    scanf("%d", &numero);
    fflush(stdin);

    if(head == NULL)
    {
        printf("\nLista Vazia...\n");
        return;
    }

    while(ptraux->numero != numero)
    {
        if (ptraux->next == NULL)
        {
            printf("\nCliente não encontrado\n");
            return;
        }
        ptraux = ptraux->next;
    }
    printf("\nInsira o novo valor maximo de credito para o cliente numero %d:",ptraux->numero);
    scanf("%f", &maxcred);
    fflush(stdin);

    ptraux->maxcred = maxcred;
}

void le_ficheiro()
{
    FILE *fp;
    cliente *ptr;
    cliente *ptraux;

    char delimitadores[]=DELIMITADORES;
    char *token;
    char frase[100];
    int token_pos;

   fp = fopen("dados.txt","r");

    while(fgets(frase,100,fp)!=NULL)
    {
        ptr=(cliente*)malloc(sizeof(cliente));

        if(ptr==NULL)
        {
            printf("Memoria nao alocada!\n");
            free(ptr);
            return;
        }

        token=strtok(frase,delimitadores);
        token_pos=0;

        while(token!=NULL)
        {
            if(token_pos==0) //numero int
            {
                ptr->numero=atoi(token);
                token_pos++;
            }
            else if(token_pos==1) //nome char
            {
                ptr->nome=(char*)malloc(sizeof(char)*(strlen(token)+1));
                strcpy(ptr->nome,token);
                token_pos++;
            }
            else if(token_pos==2) //telefone char
            {
                ptr->telefone=(char*)malloc(sizeof(char)*(strlen(token)+1));
                strcpy(ptr->telefone,token);
                token_pos++;
            }
            else //maxcred float
            {
                ptr->maxcred=atof(token);
                token_pos++;
            }
            token=strtok(NULL,delimitadores);
        }

        if(head==NULL)
        {
            head=ptr;
            ptr->next=NULL;
        }
        else
        {
            ptraux=head;

            while(ptraux->next!=NULL)
            {
                ptraux=ptraux->next;
            }
            ptr->next=NULL;
            ptraux->next=ptr;
        }
    }
}

int main()
{
    FILE *fp;
    char frase[100];
    int opcao;

    fp = fopen("dados.txt","r");

    if(fp==NULL)
    {
        printf("Nao foi possivel abrir o ficheiro de texto!\n");
        return 0;
    }

    fgets(frase,100,fp);
    le_ficheiro(fp);
    fclose(fp);

    while(1)
    {

        printf("\nOpcoes disponiveis:\n");
        printf("> 1 - Listar Clientes\n");
        printf("> 2 - Inserir novo Cliente\n");
        printf("> 3 - Alterar Cliente Existente\n");
        printf("> 4 - Eliminar Cliente\n");
        printf("> 0 - Sair do Programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        fflush(stdin);
        system("cls");

        switch(opcao)
        {
        case 1:
            if(verifica_conteudo()==TRUE)
            {
                printf("Lista vazia!\n");
                break;
            }
            else
            {
                imprimelista();
            }
            break;

        case 2:
            criar_cliente();
            break;

        case 3:
            printf("\nOpcoes disponiveis:\n");
            printf("> 1 - Alterar nome\n");
            printf("> 2 - Alterar telefone\n");
            printf("> 3 - Alterar valor maximo de credito\n");
            printf("> 0 - Voltar ao menu principal\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
            fflush(stdin);
            system("cls");

            switch(opcao)
            {
            case 1:
                alterar_nome();
                break;
            case 2:
                alterar_telefone();
                break;
            case 3:
                alterar_maxcred();
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            }
            break;
        case 4:
            eliminar_cliente();
            break;
        case 0:
            printf("Saindo do programa... Adeus!\n");
            return 0;
        }
    }
}














