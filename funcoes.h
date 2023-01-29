#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <locale.h>
#include "structs.h"

using namespace std;

//setlocale(LC_ALL, "portuguese-brazilian");//Utilizando caracteres e acentua��o da l�ngua portuguesa.

//Declaracao de todas as funcoes
void Menu();
void Leitura();
void JogoPrincipal();
void Piloto();
void Interface();
void InterfaceCombate();
void Capitulo1();
void Capitulo2();
    void VilarejoCap1();
    void VilarejoCap1parte2();
void Capitulo3();
    void FinalN1();
    void FinalN2();
    void FinalN3();
    void BatalhaFinal();
    void CreditosFinais();
void Combate();
void GameOver();

//Declarando structs/classes como variaveis
Jogador player;
Entidades inimigos;
Equipamentos itens;
//FUNCOES GENERICA QUE SAO USADAS MAIS DE UMA VEZ

//Funcao para leitura de arquivos txt ou csv
void Leitura(string path){

    fstream Print;
    string texto;

    Print.open(path);

    while(!Print.eof()){
        getline(Print, texto);
        cout << texto << endl;
        Sleep(100);
    }
    Print.close();
}

//Esta funcao sera chamada caso sua vida chegue a 0
void GameOver(){
    system("cls");
    cout << "Voce morreu e sua aventura chegou ao fim";
    exit (0);
}

//Interface
void Interface(Jogador &player, Equipamentos &itens){
    cout << "Nome: " << player.nome << "\nVida: " << player.vida << "\nAtaque: " << player.ataque << "\nDefesa: " << player.defesa << "\nAgilidade: " << player.agilidade << "\nPocoes de Cura: " << itens.cura << "\nMoedas: " << itens.moedas << "\n\n"; //Adicionar itens aqui depois
}

//Interface de Combate
void InterfaceCombate(Jogador &player, Entidades inimigos, Equipamentos &itens){
    system ("cls");
    cout << "Nome: " << player.nome << "\t\t\t\t\t\t" << "Nome do inimigo: " << inimigos.nome << "\nVida: " << player.vida << "\t\t\t\t\t\t" << "Vida do Inimigo: "
    << inimigos.vida << "\nPo��es de cura: " << itens.cura;
}

//Funcao de Combate
void Combate(Jogador &player, Entidades inimigos, Equipamentos &itens){ //
    InterfaceCombate(player, inimigos, itens);

    int escolhaCombate;
    float danoPlayer = player.ataque;//* (inimigos.defesa/4);
    float danoMonstro = inimigos.ataque;//* (player.defesa/4);

    while(player.vida > 0 && inimigos.vida > 0){//A vida do player e do inimigo agem como contadores, quando um deles chegar a zero o loop eh interrompido
        int dado = rand()%100; //Aleatoriedade(como se fosse um dado de RPG)
        cout << "\n";
        cout << "1-Atacar" << endl;
        cout << "2-Bloquear" << endl;
        cout << "3-Fugir da batalha" << endl;

        cin >> escolhaCombate;

        //Ataque
        if(escolhaCombate == 1){
            if(dado > inimigos.defesa){ //Voce so ataca se o dado gerado for maior que a defesa do inimigo
                cout << "\n";
                cout << "Voce atacou e tirou " << danoPlayer << " do inimigo: " << inimigos.nome << endl;
                inimigos.vida = inimigos.vida - danoPlayer;
                Sleep(1000);
                InterfaceCombate(player, inimigos, itens); //Atualizando a interface para mostrar os novos valores
                }
            if(inimigos.vida > 0){ //Turno do inimigo atacar
                cout << "\n";
                cout << "O inimigo esta atacando..." << endl;
                player.vida = player.vida - danoMonstro;
                    cout << "Voce tomou " << danoMonstro << " de dano" << endl;
                    Sleep(1000);
                    InterfaceCombate(player, inimigos, itens); //Atualizando a interface para mostrar os novos valores
                if(player.vida < 0){ //Voce morreu
                    player.vida = 0;
                    InterfaceCombate(player, inimigos, itens); //Atualizando a interface para mostrar os novos valores
                    Sleep(1000);
                    GameOver();
                }
            }else if(inimigos.vida < 0){ //Aqui voce derrota o inimigo
                inimigos.vida = 0;
                itens.moedas = itens.moedas + 300; //Voce ganha dinheiro cada vez que derrota um inimigo (Talvez eu mude este valor)
                system("cls");
                Interface(player, itens);
                cout << "\nVoce derrotou " << inimigos.nome << " e ganhou 200 moedas" << endl;
            }
            Sleep(1000);
        }
        //Bloquear
        else if(escolhaCombate == 2){
                cout << "Bloqueando..." << endl;
                if(dado > 25){
                    cout << "Voce bloqueou o ataque" << endl;
                    if(itens.cura > 0){
                        cout << "Voce utilizou uma po��o de vida" << endl;
                        player.vida = player.vida + 30; //Voce ganha 10 de vida
                        itens.cura--; //Voce consumi um item de cura
                        Sleep(1000);
                        InterfaceCombate(player, inimigos, itens); //Atualizando a interface para mostrar os novos valores
                    }
                    else{
                        Sleep(1000);
                        InterfaceCombate(player, inimigos, itens); //Atualizando a interface para mostrar os novos valores
                    }
                }
                else {
                    cout << "O seu bloqueio falhou" << endl;
                    player.vida = player.vida - danoMonstro;
                    cout << "Voce tomou " << danoMonstro << " de dano" << endl;
                    Sleep(1000);
                    Combate(player, inimigos, itens);
                }
        }
        //Fugir
        else if(escolhaCombate == 3){
                cout << "Voce tenta fugir..." << endl;
                Sleep(1000);
                if(dado > inimigos.inteligencia){ //Todos os inimigos tem 50 de inteligencia exceto a bruxa e o boss final, eles possuem 100 de inteligencia para evitar que o jogador fuja da batalha
                    cout << "Voce conseguiu fugir" << endl;
                    Sleep(1000);
                    system("cls");
                    Interface(player, itens);
                    return;
                }
                else{
                    cout << "Voce nao conseguiu fugir" << endl;
                    player.vida = player.vida - danoMonstro;
                    cout << "Voce tomou " << danoMonstro << " de dano" << endl;
                    Sleep(1000);
                    InterfaceCombate(player, inimigos, itens); //Atualizando a interface para mostrar os novos valores
                }
        }
        else {
            cout << "Opicao invalida";
            Combate(player, inimigos, itens);
        }
    }
}

//Funcao creditos finais
void CreditosFinais(){
    system("cls");
    cout << "Obrigado por jogar Darkwar: Moonbass" << endl;
    Sleep(1000);
    cout << "Jogo desenvolvido por Cau� Ribas" << endl;
}

//FUNCOES DA HISTORIA DO CAPITULO 3

//Funcao da batalha final
void BatalhaFinal(){
    cout << "Voce finalmente encontra a temida Hidra..." << endl;
    cout << "Uma batalha mortal esta prestes a comecar" << endl;
    system("pause");

    int i = 0;
    while(i<7){
        inimigos.nome = "Hidra";
        inimigos.vida = 10;
        inimigos.ataque = 20;
        inimigos.defesa = 30;
        inimigos.inteligencia = 100;
        Combate(player, inimigos, itens);
        i++;

        cout << "Voce destruiu a " << i << " cabeca da Hidra" << endl;

        system("pause");
        system("cls");
    }
    cout << "Voce destruiu todas as cabecas da Hidra," << endl;
    cout << "agora e hora de voltar para casa e dar um fim a esta aventeura" << endl;
    system("pause");
}

//FUNCOES FINAIS DA HISTORIA
void FinalN1(){
    cout << "Voce decide nao ir atras do monstro supremo e " <<
    "volta pra sua casa viver sua vida comum";
}
void FinalN2(){
    Interface(player, itens);
    if(itens.mapa == true){
        cout << "Voce segue o caminho do mapa e encontra a casa de uma bruxa" << endl;
        cout << "Voce bate na porta de sua casa e ela atende com um olhar vazio" << endl;
        string path = "Capitulo3-1.txt";
        Leitura(path);

        system("pause");
        system("cls");

        Interface(player, itens);
        cout << "Agora voce deve escolher se vai desistir da recompensa milionaria e salvar o filho da bruxa " <<
        " ou se vai destrui-lo para ganhar a recompensa" << endl;

        cout << "[1]-Salva-lo \t\t\t\t [2]-Destrui-lo" << endl;
        int escolhaBruxa;
        cin >> escolhaBruxa;

        if(escolhaBruxa == 1){//Voce decide salvar o filho da bruxa
            system("cls");
            Interface(player, itens);
            cout << "Voce aceita a magia da bruxa para tentar desfazer a transformcao de Hidra do filho dela" << endl;
            cout << "Com estes poderes voce ficou mais poderoso" << endl;

            player.vida = 160;
            player.ataque = 80;
            player.defesa = 50;
            player.agilidade = 50;
            system ("pause");
            system("cls");

            Interface(player, itens);
            cout << "Voce parte em direcao a caverna que a hidra se esconde" << endl;
            Sleep(1000);
            system("pause");
            system("cls");
            Interface(player, itens);
            Sleep(1000);

            BatalhaFinal();

        }else{//Voce escolhe destruir a hidra
            system("cls");
            Interface(player, itens);
            cout << "Voce decide destruir a Hidra para ganhar a recompensa" << endl;
            cout << "A bruxa nao vai deixar voce ir atras da Hidra tao facilmente, voce tera que passar por ela antes" << endl;
            system("pause");
            inimigos.nome = "Bruxa";
            inimigos.vida = 10;
            inimigos.ataque = 20;
            inimigos.defesa = 30;
            inimigos.inteligencia = 100;
            Combate(player, inimigos, itens);
            cout << "\n\n";
            system("pause");
            system("cls");

            Interface(player, itens);
            cout << "Voce derrotou a bruxa, e absorveu seus poderes, se tornando assim muito poderoso" << endl;
            Sleep(1000);
            player.vida = 160;
            player.ataque = 80;
            player.defesa = 50;
            player.agilidade = 50;
            cout << "Voce parte em direcao a caverna que a hidra se esconde" << endl;
            Sleep(1000);
            system("pause");
            system("cls");
            Interface(player, itens);
            Sleep(1000);

            BatalhaFinal();
        }

    }else{ //Voce conseguiu escapar da ravina porem nao possuia um mapa
        cout << "Voce segue procurando a Hidra pelo pantano..." << endl;
        Sleep(1000);
        cout << "Voce se depara com um Cerbero no pantano..." << endl;
        system("pause");
            inimigos.nome = "Cerbero";
            inimigos.vida = 60;
            inimigos.ataque = 30;
            inimigos.defesa = 20;
            inimigos.inteligencia = 50;
            Combate(player, inimigos, itens);
            system("pause");
            system("cls");

            Interface(player, itens);
            cout << "Apos derrotar o Cerbero, voce decide armar um acampamento no pantano para descansar..." << endl;
            Sleep(500);
            cout << "Voce recuperou e aumentou sua vitalidade apos descansar" << endl;
            player.vida = 130;
            system("pause");
            system("cls");

            Interface(player, itens);
            cout << "Agora que voce esta no pantano" << endl;
            Sleep(500);
            cout << "Voce comeca sua busca pela Hidra..." << endl;
            Sleep(500);
            system("pause");
            system("cls");
            cout << "Vagando pelo pantano em busca da caverna da Hidra..." << "\n\n";
            Sleep(2000);
            cout << "Vagando pelo pantano em busca da caverna da Hidra..." << "\n\n";
            Sleep(2000);
            cout << "Vagando pelo pantano em busca da caverna da Hidra..." << "\n\n";
            Sleep(2000);
            cout << "Vagando pelo pantano em busca da caverna da Hidra..." << "\n\n";
            Sleep(2000);
            cout << "Vagando pelo pantano em busca da caverna da Hidra..." << "\n\n";
            Sleep(2000);
            system("cls");


        Interface(player, itens);
        cout << "Voce encontra a caverna da Hidra..." << endl;
        Sleep(1000);
        BatalhaFinal();
    }
}
void FinalN3(){
    cout << "Enquanto vagava pelo sistema de cavernas voce se depara com um grande e feroz dragao..." << endl;
    system("pause");
            inimigos.nome = "Dragao";
            inimigos.vida = 50;
            inimigos.ataque = 20;
            inimigos.defesa = 30;
            inimigos.inteligencia = 50;
            Combate(player, inimigos, itens);
            system("pause");
            system("cls");

            Interface(player, itens);
            cout << "Apos derrotar o Dragao, voce decide armar um acampamento dentro da caverna para descansar..." << endl;
            Sleep(500);
            cout << "Voce recuperou e aumentou sua vitalidade apos descansar" << endl;
            player.vida = 130;
            Sleep(1000);

            cout << "Quando voce menos espera..." << endl;
            system("pause");
            BatalhaFinal();
}

//Capitulo 3
void Capitulo3(){
    cout << "Parabens, voce concluiu o Capitulo 2 e chegou no Capitulo 3" << endl;
    system("pause");
    system("cls");

    Interface(player, itens);
    cout << "Agora que voce esta no pantano" << endl;
    Sleep(500);
        cout << "Voce comeca sua busca pela Hidra..." << endl;
        Sleep(500);
        system("pause");
        system("cls");
        cout << "Vagando pelo pantano..." << "\n\n";
        Sleep(2000);
        cout << "Vagando pelo pantano..." << "\n\n";
        Sleep(2000);
        cout << "Vagando pelo pantano..." << "\n\n";
        Sleep(2000);
        cout << "Vagando pelo pantano..." << "\n\n";
        Sleep(2000);
        cout << "Vagando pelo pantano..." << "\n\n";
        Sleep(2000);
        system("cls");

    Interface(player, itens);
    cout << "Enquanto voce vagava pelo pantano, voce cai em uma ravina" << "\n\n";
    player.vida = player.vida - 10;
    system("pause");
    system("cls");

    Interface(player, itens);
    cout << "Voce ve que ha uma abertura na ravina que leva a um sistema de cavernas" << endl;
    Sleep(500);
    cout << "Voce tenta escalar a ravina, ou voce tenta achar uma saida atraves do sistema de cavernas?"<< "\n\n";
    Sleep(500);
    int escolhaRavina;
    cout << "[1]-Escalar a ravina \t\t\t [2]-Achar outra saida atraves do sistema de cavernas" << endl;
    cin >> escolhaRavina;

    if(escolhaRavina == 1){
        cout << "Voce tenta escalar a ravina de volta a superficie..." << "\n\n";
        Sleep(2000);
            if(itens.corda == true || player.agilidade > 40){
                cout << "Voce conseguiu escalar a ravina e voltar para a superficie" << "\n\n";
                system("pause");
                system("cls");
                FinalN2();
            }else{
                cout << "Voce falhou em sair da ravina e foi obrigado a entrar no sistema de cavernas" << endl;
                system("pause");
                system("cls");
                FinalN3();
            }
    }else if(escolhaRavina == 2){
        cout << "Voce decide vagar pelo sistema de cavernas para tentar encontrar uma saida..." << "\n\n";
        system("pause");
        system("cls");
        FinalN3();
    }else{
        cout << "Opcao invalida" << endl;
        system("pause");
        system("cls");
        Capitulo3();
    }
}

//FUNCOES DA HISTORIA DO CAPITULO 2
//Capitulo 2
void Capitulo2(){
    cout << "Parabens, voce concluiu o Capitulo 1 e chegou no Capitulo 2" << endl;
    system("pause");
    system("cls");

    Interface(player, itens);
    cout << "Voce finalmente chega a capital de Moonbass" << endl;
    cout << "Voce fica encantado com a arquitetura do local e com quantas pessoas estao nas ruas" << endl;
    cout << "Voce vai ate uma curandeira para tratar das suas feridas" << endl;

    system ("pause");
    system("cls");
    int escolhaCurandeira;
    while(escolhaCurandeira != 3){
        system("cls");
        Interface(player, itens);
        cout << "Curandeira: \"Seja bem-vindo\""<< endl;
        cout << "[1]-Tratar suas feridas \t\t Preco: 50 moedas" << endl;
        cout << "[2]-Comprar Pocoes \t\t\t Preco: 25 moedas" << endl;
        cout << "[3]-Sair" << endl;
        cin >> escolhaCurandeira;
        if(escolhaCurandeira == 1){
            if(itens.moedas > 49){
                cout << "Voce tratou suas feridas" << endl;
                if(player.classe == 1){
                    player.vida = 100;
                    itens.moedas = itens.moedas - 50;
                }
                if(player.classe == 2){
                    player.vida = 80;
                    itens.moedas = itens.moedas - 50;
                }
                if(player.classe == 3){
                    player.vida = 80;
                    itens.moedas = itens.moedas - 50;
                }
                Sleep (1000);
            }else{
                cout << "Voce nao possui dinheiro suficiente" << endl;
                Sleep(1000);
            }
        }else if(escolhaCurandeira == 2){
            if(itens.moedas > 24){
                cout << "Voce comprou uma pocao" << endl;
                itens.cura++;
                itens.moedas = itens.moedas - 25;
                Sleep(1000);
            }else{
                cout << "Voce nao possui dinheiro suficiente" << endl;
                Sleep(1000);
            }
        }else if(escolhaCurandeira == 3){
            cout << "Voce saiu da loja da curandeira" << endl;
        }
        else{
            cout << "Opcao Invalida";
        }
    }
    Sleep(1000);
    system("cls");

    //Agora voce vai ate a taverna da capital
    Interface(player, itens);

    cout << "Apos visitar a curandeira da capital voce vai a uma hotelaria para descansar a noite..." << endl;
    Sleep(1000);
    cout << "Na manha seguinte voce sai em busca de informacoes sobre a localizacao da Hidra" << endl;
    cout << "Voce chega em uma taverna e comeca a perguntar sobre, mas ninguem parece ter informacoes concretas, apenas rumores" << endl;
    cout << "Voce vai ate o bar da taverna para beber um pouco" << endl;
    Sleep(1000);
    system("pause");
    system("cls");

    Interface(player, itens);
    cout << "Escolha uma bebida: "<< endl;
    cout << "[1]-Ess�ncia de Basil�sco da Selva" << endl;
    cout << "[2]-Hidromel Elfic" << endl;
    cout << "[3]-Frasco Espiritual" << endl;
    cout << "[4]-Receita do Anci�o" << endl;
    int escolhaBebida;
    cin >> escolhaBebida;

    switch(escolhaBebida){
        case 1:
            cout << "Voce bebeu Ess�ncia de Basil�sco da Selva" << endl;
            player.vida = player.vida + 20;
            break;
        case 2:
            cout << "Voce bebeu Hidromel Elfic" << endl;
            player.ataque = player.ataque + 20;
            break;
        case 3:
            cout << "Voce bebeu Frasco Espiritual" << endl;
            player.defesa = player.defesa + 20;
            break;
        case 4:
            cout << "Voce bebeu a Receita do Anci�o" << endl;
            player.agilidade = player.agilidade + 20;
            break;
        default:
            cout << "Voce decidiu nao beber nada" << endl;
    }
    Sleep(1000);
    system("pause");
    system("cls");

    Interface(player, itens);
    string path = "Capitulo2-1.txt";
    Leitura(path);

    Sleep(1000);
    system("pause");
    system("cls");

    Interface(player, itens);
    cout << "A taverna esta ficando sem estoque de olhos de Ciclopes" << endl;
    cout << "O dono da taverna pede que voce va ate a floresta ca�ar um cliclope" << endl;

    int escolhaMapa;
    cout << "Voce vai ate a floresta ca�ar um cliclope?"<< endl;
    cout << "[1]-Sim \t\t\t\t\t [2]-Nao" << endl;
    cin >> escolhaMapa;

    if(escolhaMapa == 1){
        cout << "Voce vai ate a floresta ca�ar um cliclope" << endl;
        Sleep(1000);
        inimigos.nome = "Ciclope";
        inimigos.vida = 75;
        inimigos.ataque = 30;
        inimigos.defesa = 30;
        inimigos.inteligencia = 50;
        Combate(player, inimigos, itens);
        cout << "Voce conseguiu matar o cliclope e levou sua iguaria ate o Dono da Taverna" << endl;
        Sleep(1000);
        system("pause");
        system("cls");
        Interface(player, itens);
        cout << "Dono da Taverna: \"Aqui esta garoto(a), como eu havia prometido, falei com um contato"
        << "e ele escreveu tudo que sabia sobre o paradeiro da Hidra neste mapa\"" << endl;
        itens.mapa = true;
    }
    else{
        cout << "Voce rejeitou a oferta do Dono da Taverna" << endl;
        Sleep(1000);
    }
    system("pause");
    system("cls");
    Interface(player, itens);
    cout << "Antes de partir em busca da Hidra voce passa em uma loja para comprar equipamentos e se fortalecer" << endl;
    system("pause");
    int escolhaLoja;

    while(escolhaLoja != 6){
        system("cls");
        Interface(player, itens);
        cout << "Vendedor: \"Seja bem-vindo e de uma olhada no catalogo\""<< endl;
        cout << "[1]-Espada \t\t\t Preco: 100 moedas" << endl;
        cout << "[2]-Armadura \t\t\t Preco: 100 moedas" << endl;
        cout << "[3]-Corda \t\t\t Preco: 50 moedas" << endl;
        cout << "[4]-Pocao de cura \t\t Preco: 50 moedas" << endl;
        cout << "[5]-Mapa do pantano \t\t Preco: 400 moedas" << endl;
        cout << "[6]-Sair" << endl;
        cin >> escolhaLoja;

        switch(escolhaLoja){
            case 1: //Comprar espada
                if(itens.moedas > 99){
                    cout << "Voce comprou uma espada e aumentou seu poder de ataque" << endl;
                    player.ataque = player.ataque + 50;
                    itens.moedas = itens.moedas - 100;
                    Sleep(1000);
                }else{
                    cout << "Voce nao possui dinheiro suficiente" << endl;
                Sleep(1000);
                }
                break;
            case 2: //Comprar armadura
                if(itens.moedas > 99){
                    cout << "Voce comprou uma armadura e aumentou sua defesa" << endl;
                    player.defesa = player.defesa + 50;
                    itens.moedas = itens.moedas - 100;
                    Sleep(1000);
                }else{
                    cout << "Voce nao possui dinheiro suficiente" << endl;
                Sleep(1000);
                }
                break;
            case 3: //Comprar corda
                if(itens.moedas > 49){
                    cout << "Voce comprou uma corda" << endl;
                    itens.corda = true;
                    itens.moedas = itens.moedas - 50;
                    Sleep(1000);
                }else{
                    cout << "Voce nao possui dinheiro suficiente" << endl;
                Sleep(1000);
                }
                break;
            case 4: //Comprar pocao de cura
                if(itens.moedas > 49){
                    cout << "Voce comprou uma pocao de cura" << endl;
                    itens.cura++;
                    itens.moedas = itens.moedas - 50;
                    Sleep(1000);
                }else{
                    cout << "Voce nao possui dinheiro suficiente" << endl;
                Sleep(1000);
                }
                break;
            case 5: //Comprar mapa
                if(itens.moedas > 399){
                    cout << "Voce comprou um mapa do pantano" << endl;
                    itens.mapa = true;
                    itens.moedas = itens.moedas - 400;
                    Sleep(1000);
                }else{
                    cout << "Voce nao possui dinheiro suficiente" << endl;
                Sleep(1000);
                }
                break;
            case 6: //Sair da loja
                cout << "Voce saiu da loja" << endl;
                break;
            default:
                cout << "Opcao invalida" << endl;
                Sleep(1000);
        }
    }
    Sleep(1000);
    system("pause");
    system("cls");
    Interface(player, itens);
    cout << "Apos visitar a capital para obter informacoes voce parte em direcao ao pantano..." << endl;
    Sleep(500);
    cout << "Sera uma batalha dificil, mas voce esta pronto pro sacrificio" << endl;
    system("pause");
    system("cls");
}

//FUNCOES DA HISTORIA DO CAPITULO 1

//Parte 2 da funcao do vilarejo
void VilarejoCap1parte2(Jogador &player, Entidades inimigos, Equipamentos &itens){
    Interface(player, itens);
    cout << "Apos o incidente com o lobo selvagem," << endl;
    cout << "voce chega a um vilarejo que fica perto da capital" << "\n\n";
    Sleep(500);
    cout << "Voce nota que o vilarejo esta vazio, a maioria dos moradores estao se escondendo dentro de suas casas" << endl;
    Sleep(500);
    cout << "Voce vai ate o fim do vilarejo e encontra um Goblin Gigante dormindo bloqueando a estrada" << endl;
    Sleep(500);
    cout << "Voce volta ao centro do vilarejo e caminha mais algumas ruas e ve as pessoas olhando pelas janelas de suas \nresidencias com medo" << endl;
    Sleep(500);
    cout << "Voce ve um homem coletando agua num po�o, voce se aproxima e pergunta se as pessoas estao com medo do Goblin" << "\n\n";
    Sleep(500);
    system ("pause");
    system ("cls");

    Interface(player, itens);
    cout << "Morador do Vilarejo: \"Nao, nao estamos com medo do Goblin, o Goblin so ataca os moradores se for acordado de maneira agressiva" << endl;
    cout << "Os morados deste vilarejo estao com medo de um Mini-Demonio que vem ao vilarejo a noite roubar comida, \neste Mini-Demonio eh estremamente agressivo\"" << "\n\n";
    Sleep(500);
    cout << "Voce questiona o morador como acordar o Goblin de maneira pacifica" << "\n\n";
    Sleep(500);
    cout << "Morador do Vilarejo: \"Voce vai precisar de uma flauta de hipnoze especial, eu sou o unico que possui esta flauta no vilarejo todo" << endl;
    cout << "mas so vou dar esta flauta a voce se voce acabar com o Mini-Demonio e livrar o vilarejo deste mal\"" << endl;
    Sleep(1000);
    system("pause");
    system ("cls");

    Interface(player, itens);
    cout << "[1]-Ajudar o vilarejo e ganhar a flauta especial" << "\t\t" << "[2]-Nao ajudar" << endl;
    int escolhaBatalhaVilarejo;
    cin >> escolhaBatalhaVilarejo;

    Sleep(1000);
    system("cls");
    if(escolhaBatalhaVilarejo == 1){
        cout << "Voce esperou ate o anoitecer para acabar com o Mini-Demonio" << endl;
        Sleep(1000);
        inimigos.nome = "Mini-Demonio";
        inimigos.vida = 50;
        inimigos.ataque = 12;
        inimigos.defesa = 25;
        inimigos.inteligencia = 50;
        Combate(player, inimigos, itens);
        cout << "Voce livrou o vilarejo do Mini-Demonio e ganhou a flauta especial" << endl;
        itens.flauta = true;
        Sleep(500);
    }else if(escolhaBatalhaVilarejo == 2){
        cout << "Voce decidiu nao ajudar o vilarejo" << endl;
        Sleep(1000);
    }else{
        VilarejoCap1parte2(player, inimigos, itens);
    }
    system("pause");
    system("cls");
    Interface(player, itens);
    cout << "Voce chega ate o final do vilarejo novamento" << endl;
    cout << "O Goblin continua no mesmo lugar dormindo" << endl;

    if(itens.flauta == true){
        cout << "Voce usou a flauta e acordou o Goblin pacificamente.... Ele saiu do caminho" << endl;
        Sleep(1000);
    }else if(player.agilidade > 20){
        cout << "Voce nao tinha a flauta para acordar o Goblin pacificamente," << endl;
        cout << "porem foi agil o suficiente para achar outro caminho" << endl;
        Sleep(1000);
    }
    else{
        cout << "Voce nao tinha a flauta para acordar o Goblin pacificamente," << endl;
        cout << "e nao foi agil o suficiente para achar outro caminho" << endl;
        cout << "Voce acorda o Goblin com um graveto e ele se levanta furioso e agressivo" << endl;
        Sleep(1000);
        system ("pause");
        inimigos.nome = "Goblin Gigante";
        inimigos.vida = 80;
        inimigos.ataque = 16;
        inimigos.defesa = 5;
        inimigos.inteligencia = 50;
        Combate(player, inimigos, itens);
        Sleep(1000);
    }
}

//Parte 1 da funcao do vilarejo
void VilarejoCap1(Jogador &player, Entidades inimigos, Equipamentos &itens){
    Interface(player, itens);
    cout << "Finalmente chegou a hora de voce partir em sua aventura em busca" << endl;
    Sleep(500);
    cout << "do terrivel monstro que trouxe medo, caos e ang�stia para a popula��o de Moonbass..." << endl;
    Sleep(500);
    system("pause");
    system("cls");

    Interface(player, itens);
    cout << "Agora voce parte atras de mais informacoes sobre a localizacao da Hidra" << endl;
    Sleep(500);
        cout << "Voce comeca sua viagem em direcao a capital..." << endl;
        Sleep(500);
        system("pause");
        system("cls");
        cout << "Viajando ate a capital..." << "\n\n";
        Sleep(2000);
        cout << "Viajando ate a capital..." << "\n\n";
        Sleep(2000);
        cout << "Viajando ate a capital..." << "\n\n";
        Sleep(2000);
        cout << "Viajando ate a capital..." << "\n\n";
        Sleep(2000);
        cout << "Viajando ate a capital..." << "\n\n";
        Sleep(2000);
        system("cls");

    Interface(player, itens);
    cout << "Enquanto voce caminha por uma trilha na floresta voce ouve um barulho vindo das arvores" << endl;
    Sleep(500);
    cout << "[1]-Voce vai ate as arvores investigar o barulho" << "\t\t" << "[2]-Voce ignora e continua a trilha normalmente" << endl;
    int escolhaBatalhaFloresta;
    cin >> escolhaBatalhaFloresta;

    Sleep(1000);
    system("cls");
    Interface(player, itens);
    if(escolhaBatalhaFloresta == 1){
        cout << "Voce foi ate as arvores investigar o barulho e encontrou um lobo" << endl;
        cout << "O lobo ataca voce..." << endl;
        system ("pause");
        inimigos.nome = "Lobo selvagem";
        inimigos.vida = 50;
        inimigos.ataque = 12;
        inimigos.defesa = 25;
        inimigos.inteligencia = 50;
        Combate(player, inimigos, itens);
        Sleep(1000);
    }else if(escolhaBatalhaFloresta == 2){
        cout << "Voce ignora o barulho vindo das arvores e continua a trilha" << endl;
        Sleep(500);
        cout << "Um lobo lhe ataca de surpresa pelas costas, mas voce consegue fugir" << endl;
        Sleep(500);
        cout << "Voce perdeu 10 pontos de vida" << endl;
        Sleep(1000);
        player.vida = player.vida - 10;
        if(player.vida <= 0)
            GameOver();
    }else{
        VilarejoCap1(player, inimigos, itens);
    }
    system("pause");
    system("cls");
    VilarejoCap1parte2(player, inimigos, itens);
}

//Capitulo 1
void Capitulo1(){
    //Interface(player, itens);
    string path = "Capitulo1-1.txt";
    Leitura(path);
    //system ("pause");
    //system("cls");
    Sleep(1000);
    cout << "Este guerreiro se chama " << player.nome << endl;
    Sleep(1000);
    system("pause");
    system("cls");
    Interface(player, itens);
    cout << "Um certo dia voc� vai caminhar ao centro do vilarejo onde mora e encontra um velho guerreiro do pa�s" << endl;
    Sleep(500);
    cout << "Ele se aproxima de voce e conta sobre o terrivel monstro que assombra Moonbass a tempos..." << endl;
    system("pause");
    system("cls");

    Interface(player, itens);
    {string path = "Capitulo1-2.txt";
    Leitura(path);}
    system ("pause");
    system("cls");

    Interface(player, itens);
    cout << "Voce aceita embarcar em uma jornada para ir atras da recompensa e derrotar este terrivel mal?" << endl;
    cout << "[1]-Sim" << "\t\t" << "[2]-Nao" << "\n\n";

    int escolhaCap1;
    cin >> escolhaCap1;

    switch(escolhaCap1){
    case 1:
        system("cls");
        break;
    case 2:
        FinalN1();
        break;
    default:
        system("cls");
        Capitulo1();
    }

    Interface(player, itens);
    cout << "Antes de voce embarcar em sua aventura, o velho guerreiro deseja testar suas habilidades e batalhar com voce." << endl;
    Sleep(1000);
    cout << "Voce aceita o desafio?" << endl;
    cout << "[1]-Sim" << "\t\t" << "[2]-Nao" << "\n\n";

    int escolhaCap1_2;
    cin >> escolhaCap1_2;

    switch(escolhaCap1_2){
    case 1:
        inimigos.nome = "Mestre Guerreiro";
        inimigos.vida = 35;
        inimigos.ataque = 8;
        inimigos.defesa = 10;
        inimigos.inteligencia = 50;
        Combate(player, inimigos, itens);
        cout << "Voce ganhou uma po��o de cura por derrotar o mestre guerreiro." << endl;
        Sleep(1000);
        system("pause");
        itens.cura++;
        system("cls");
        break;
    case 2:
        system("cls");
        Interface(player, itens);
        cout << "Voce nao aceitou o combate" << endl;
        cout << "Mestre guerreiro: \"Tudo bem se voce quiser se preservar para sua viagem\"" << endl;
        Sleep(1000);
        system("pause");
        system("cls");
        break;
    default:
        system("cls");
        Capitulo1();
    }
    VilarejoCap1(player, inimigos, itens);

    system("pause");
    system("cls");
    //cout << "\nFunction ended";
}

//Escolha de nome/classe
void Piloto(Jogador &player){
    cout << "Digite o nome do seu personagem: ";
    cin >> player.nome;
    cout << "Agora escolha sua classe: " << endl;
    cout << "[1]-WintWarrer(possui grande vitalidade e resistencia)" << endl;
    cout << "[2]-Godstroyer(possui grande for�a)" << endl;
    cout << "[3]-Focksnife(possui grande agilidade)" << endl;
    cin >> player.classe;
    if(player.classe == 1){//Colocando s valores para os atributos do jogador de acordo com sua escolha de classe
        cout << "Voce escolheu WintWarrer" << endl;
        Sleep(500);
        system("cls");
        player.vida = 100;
        player.ataque = 20;
        player.defesa = 38;
        player.agilidade = 18;
    }
    else if(player.classe == 2){//Colocando s valores para os atributos do jogador de acordo com sua escolha de classe
        cout << "Voce escolheu Godtroyer" << endl;
        Sleep(500);
        system("cls");
        player.vida = 80;
        player.ataque = 30;
        player.defesa = 20;
        player.agilidade = 20;
    }
    else if(player.classe == 3){//Colocando s valores para os atributos do jogador de acordo com sua escolha de classe
        cout << "Voce escolheu Focksnife" << endl;
        Sleep(500);
        system("cls");
        player.vida = 80;
        player.ataque = 24;
        player.defesa = 16;
        player.agilidade = 30;
    }
    else {
        cout << "Opicao invalida!" << endl;
        Sleep(1000);
        Piloto(player);
    }
}

//Menu Principal
void Menu (){
    string path = "menu.txt";
    Leitura(path);
    int menuOp;
    cin >> menuOp;
    system ("cls");

        switch(menuOp){
    case 1:
        cout << "Carregando o jogo..." << "\n\n";
        Sleep(2000);
        cout << "Carregando o jogo..." << "\n\n";
        Sleep(2000);
        cout << "Carregando o jogo..." << "\n\n";
        Sleep(2000);
        system("cls");
        break;
    case 2:
        cout << "Game desenvolvido por Cau� Ribas" << "\n";
        system ("pause");
        system ("cls");
        Menu();
        break;
    case 3:
        cout << "Jogo encerrado" << endl;
        //system("pause");
        //system("cls");
        exit(0); //Termina o jogo (processo).
        break;
    default:
        cout << "Opcao invalida."<< endl;
        system("pause");
        system("cls");
        Menu(); //Funcao chama a si mesmo novamento se houver um input invalido.
    }
}

//Funcao principal que chama outras funcoes
void JogoPrincipal(){
    Menu();
    Piloto(player);
    Capitulo1();
    Capitulo2();
    Capitulo3();
    CreditosFinais();
}
