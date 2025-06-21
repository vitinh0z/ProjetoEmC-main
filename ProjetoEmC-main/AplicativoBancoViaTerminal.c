#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int agencia;
    int digito;
    char email[60];
    int senha;

} Conta;
 


void criarConta(Conta *novaConta){
    int senhaContaVerificao;
    
    getchar();
    
    printf("Digite seu email: ");
    fgets(novaConta->email, 60, stdin);
    novaConta->email[strcspn(novaConta->email, "\n")] = '\0'; // ele tira o \n que vem junto com esse fgets maldito

    
    do {
        printf("\nDigite sua senha: ");
        scanf("%d", &novaConta->senha);
        
        printf("Digite a senha novamente: ");
        scanf("%d", &senhaContaVerificao);
        
        if (novaConta->senha != senhaContaVerificao) {
            printf("Senha não são iguais. Tente novamente.\n");
        }
    } while (novaConta->senha != senhaContaVerificao);
    
    srand(time(NULL)); 
    novaConta->agencia = 10000 + rand() % 90000;
    novaConta->digito = rand() % 10;
    
    printf("\nAgência e conta: %d - %d\n", novaConta->agencia, novaConta->digito);


    FILE *arquivos = fopen("Contas.txt", "a");

    if (arquivos == NULL){
        printf("Erro ao salva o arquivo.\n");
        return;
    }
    else {
    fprintf(arquivos, "%s %d %d %d\n", novaConta-> email, novaConta-> senha, novaConta-> agencia, novaConta-> digito);

    }
    fclose(arquivos);
}


int entrarConta(Conta *contaLogada) {
    char emailDigitado[60];
    int senhaDigitada;

    getchar();

    


    printf("Digite seu Email: ");
    fgets(emailDigitado, 60, stdin);
    emailDigitado[strcspn(emailDigitado, "\n")] = '\0';  // remove o \n lido do teclado

    printf("Digite sua senha: ");
    scanf("%d", &senhaDigitada);


    FILE *arquivos = fopen("Contas.txt", "r");
    if (arquivos == NULL) {

        printf ("Erro ao abrir o arquivo.\n");
        return 0;
    }
    
    Conta temp;
    while (fscanf(arquivos, "%s %d %d %d", temp.email, &temp.senha, &temp.agencia, &temp.digito) == 4) { // so entr no looping e tiver 4 valores para ler
        if (strcmp(temp.email, emailDigitado) == 0 && temp.senha == senhaDigitada) { // strcmp compara strings. Então, se o email e senha forem iguais, entra no if
            printf("Login bem-sucedido!\n");
            printf("Agência: %d - Conta: %d\n", temp.agencia, temp.digito);
            *contaLogada = temp; 
            fclose(arquivos);
            return 1; 
           
        }
    }
    fclose(arquivos);
    return 0; // se não encontrar o email e senha
}
int main (){
    printf("----- Bem vindo ao Banco VitinhoBank -----\n");
    
    int opcao;
    Conta usuario;

    printf("Digite: 1 - Entrar | 2 - Criar Conta\n");
    scanf("%d", &opcao);
    
    if (opcao == 1){
        if (entrarConta(&usuario)){ // chama a função para entrar na conta
            printf("Login bem sucedido!\n");
            printf("Bem vindo %s\n", usuario.email);
        printf("Agência: %d - Conta: %d\n", usuario.agencia, usuario.digito);

            int acao;
            printf("1 - Consultar Saldo\n");
            printf("2 - Fazer Transferência\n");
            printf("3 - Depositar\n");
            printf("4 - Sacar\n");
            printf("5 - Sair\n");

            printf("\nOpção: ");
            scanf("%d", &acao);

            switch (acao) {
                case 1:
                    printf("Saldo: "); // saldo ser uma varivel vazia dentro do struct que se usuario receber trasnferencia ou depositar, atualiza o saque

                    break;
                case 2:
                    printf("Transferência realizada com sucesso! (Exemplo)\n"); /* usuario digita para quem deseja fazer tranferecia (acho que vou precisar criar um arquivo tranferecia.txt
                    onde usario digita o email do usuario e a quantidade de dinheiro. Dps ler com strcmp qual o valor transferido. (meudeus mto complicado ;-;) */ 
                    break;
                case 3:
                    printf("Depósito realizado com sucesso! (Exemplo)\n"); // 
                    break;
                case 4:
                    printf("Saque realizado com sucesso! (Exemplo)\n"); //
                    break;
                case 5:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opção inválida.\n");
            }







        } else {
            printf("Email ou senha incorretos. Tente novamente.\n");

        }
    }
      
    else if (opcao == 2) {
        criarConta(&usuario); // chama a função para criar a conta
        printf("Conta criada com sucesso!\n");
    }
     else {
        printf("Opção inválida. Tente novamente.\n");
    }
    
    return 0;
}
