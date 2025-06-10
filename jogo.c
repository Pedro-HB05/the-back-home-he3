/*
 * Jogo: The Back Home: He3
 * Descrição: Jogo de perguntas sobre astronomia com tema espacial,
 *            onde o jogador precisa recuperar peças de uma nave
 *            enquanto gerencia o oxigênio em um ambiente hostil.
 */
//biblioteca nescessaria
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

//biblioteca escrever devagar windows
#ifdef _WIN32
#include <windows.h>  // Necessário para Sleep()
//biblioteca escrever devagar linux
#else
#include <unistd.h>   // Necessário para usleep()
#endif

// Struct para armazenar perguntas
typedef struct {
    char enunciado[256];
    char alternativas[4][100];
    char correta;
} Pergunta;

// Perguntas fáceis
Pergunta perguntasFaceis[11] = {
    {"Qual o nome do maior planeta do sistema solar?", {"Júpiter", "Saturno", "Urano", "Netuno"}, 'A'},
    {"Qual é o planeta mais próximo do Sol?", {"Vênus", "Mercúrio", "Terra", "Marte"}, 'B'},
    {"Qual é o planeta conhecido como o 'Planeta Vermelho'?", {"Vênus", "Júpiter", "Marte", "Terra"}, 'C'},
    {"Qual é o nome do planeta que tem anéis visíveis?", {"Urano", "Saturno", "Netuno", "Marte"}, 'B'},
    {"Qual planeta é conhecido como o 'Planeta Azul'?", {"Netuno", "Marte", "Terra", "Urano"}, 'C'},
    {"Quantos planetas existem no Sistema Solar?", {"Sete", "Oito", "Nove", "Dez"}, 'B'},
    {"Quantas luas tem a Terra?", {"Uma", "Duas", "Nenhuma", "Três"}, 'A'},
    {"Planeta gasoso gigante?", {"Terra", "Júpiter", "Marte", "Vênus"}, 'B'},
    {"O que são asteroides?", {"Corpos rochosos que orbitam o Sol", "Satélites", "Estrelas", "Cometas"}, 'A'},
    {"O que é um cometa?", {"Astro de gelo e poeira", "Planeta anão", "Satélite natural", "Estrela pequena"}, 'A'},
    {"Missão que levou o homem à Lua?", {"Apollo 11", "Venera", "New Horizons", "Voyager"}, 'A'}
};

// Perguntas difíceis
Pergunta perguntasDificeis[12] = {
    {"Qual planeta é mais distante do Sol?", {"Saturno", "Netuno", "Urano", "Júpiter"}, 'B'},
    {"Planeta com atmosfera mais densa e quente?", {"Terra", "Vênus", "Marte", "Netuno"}, 'B'},
    {"Em que planeta chove diamantes?", {"Saturno", "Netuno", "Urano", "Vênus"}, 'B'},
    {"Maior planeta rochoso?", {"Marte", "Vênus", "Terra", "Mercúrio"}, 'C'},
    {"Primeira sonda enviada ao Sistema Solar?", {"Voyager", "Apollo 11", "Venera 1", "Sputnik"}, 'C'},
    {"Maior planeta anão?", {"Eris", "Haumea", "Plutão", "Ceres"}, 'C'},
    {"Maior diferença térmica entre dia e noite?", {"Vênus", "Mercúrio", "Terra", "Urano"}, 'B'},
    {"Menor planeta?", {"Mercúrio", "Vênus", "Marte", "Urano"}, 'A'},
    {"O que é um ano?", {"Volta ao redor do Sol", "Volta sobre o eixo", "Tempo entre eclipses", "Ciclo lunar"}, 'A'},
    {"Planeta mais quente do sistema solar?", {"Mercúrio", "Vênus", "Terra", "Júpiter"}, 'B'},
    {"Planeta com a Grande Mancha Vermelha?", {"Saturno", "Netuno", "Júpiter", "Urano"}, 'C'},
    {"Quando um planeta se alinha com Sol e Terra?", {"Trânsito planetário", "Eclipse", "Conjunção", "Oposição"}, 'A'}
};

// Função para escrever devagar
void escreverDevagar(const char *mensagem) {
    for (int i = 0; mensagem[i] != '\0'; i++) {
        putchar(mensagem[i]);
        fflush(stdout);
#ifdef _WIN32
        Sleep(40);  // No Windows
#else
        usleep(40000);  // No Linux/Unix
#endif
    }
    printf("\n");
}

// Função para apresentar uma pergunta e avaliar a resposta
void perguntas(Pergunta pergunta, int *pecas, int *oxigenio) {
    char alternativa;

    printf("\n%s\n", pergunta.enunciado);
    printf("A) %s\n", pergunta.alternativas[0]);
    printf("B) %s\n", pergunta.alternativas[1]);
    printf("C) %s\n", pergunta.alternativas[2]);
    printf("D) %s\n", pergunta.alternativas[3]);

    do {
        printf("Sua resposta (A, B, C, D): ");
        scanf(" %c", &alternativa);
        alternativa = toupper(alternativa);
        if (alternativa != 'A' && alternativa != 'B' && alternativa != 'C' && alternativa != 'D') {
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (alternativa != 'A' && alternativa != 'B' && alternativa != 'C' && alternativa != 'D');

    if (alternativa == pergunta.correta) {
        printf("Correto! Você ganhou uma peça de foguete!\n");
        (*pecas)++;
    } else {
        printf("Errado! Você perdeu uma barra de oxigênio.\n");
        (*oxigenio)--;
    }
}

// Função para exibir a barra de oxigênio
void exibirOxigenio(int oxigenio) {
    printf("Oxigênio: [");
    for (int i = 0; i < oxigenio; i++) {
        printf("?");
    }
    for (int i = oxigenio; i < 5; i++) {
        printf("-");
    }
    printf("] %d/5\n", oxigenio);
}

// Função para exibir o progresso do foguete
void exibirFoguete(int pecas) {
    printf("Peças do foguete: %d/5\n", pecas);
}

// Limpa a tela
void limparTela() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

// Texto introdutório com base na dificuldade
void textoImersivo(int dificuldade) {
    if (dificuldade == 1) {
        printf("\nVocê escolheu a dificuldade Fácil. Você começa com 5 barras de oxigênio!\n");
        printf("Aqui, o caminho será tranquilo. O acidente não causou dano no cilindro de oxigênio, ele está cheio!\n");
    } else if (dificuldade == 2) {
        printf("\nVocê escolheu a dificuldade Média. Você começa com 3 barras de oxigênio.\n");
        printf("Aqui o caminha será mais complicado, no acidente acabou causando dano no cilindrode oxigênio!\n");
    } else {
        printf("\nVocê escolheu a dificuldade Difícil. Você começa com 2 barras de oxigênio.\n");
        printf("A pressão é alta, o foguete precisa de peças e você tem pouco oxigênio. Boa sorte!\n");
    }
}

// Função para introdução de cada fase
void introduzirFase(int fase, int *dificuldade) {
    int escolha;  // Declarando a variável escolha aqui
    
    switch(fase) {
        case 0:
            printf("\nFase 1 - O Limiar do Desconhecido\n");
            printf("\nVocê se encontra no limiar de uma vastidão desconhecida. À sua frente, duas rotas: uma escura, envolta em névoa espessa, e outra iluminada por uma luz fraca, mas que desaparece rapidamente.\n");
            printf("Você deve escolher o caminho:\n");
            printf("1. Caminho Iluminado\n");
            printf("2. Caminho Escuro\n");
            printf("Escolha: ");
            scanf("%d", &escolha);
            if (escolha == 1) {
                *dificuldade = 1; // Caminho fácil, perguntas fáceis
                printf("Caminho iluminado. A luz suave proporciona um certo conforto, mas à medida que avança, você sente como se estivesse sendo observado. Em um ponto do caminho, um pilar brilha à sua frente. Ele emite um zumbido e, ao tocá-lo, uma tela holográfica se acende:\n");
                printf("Para prosseguir, você deve responder corretamente à questão...\n");
            } else if (escolha == 2) {
                *dificuldade = 2; // Caminho difícil, perguntas difíceis
                printf("Caminho escuro. A névoa espessa envolve rapidamente sua visão. De repente, um pilar metálico aparece no seu caminho, iluminando-se com uma luz fria. O tablet na superfície do pilar brilha, e uma voz robótica ecoa:\n");
                printf("Você se aproxima do pilar. Para avançar, responda à seguinte questão sobre o espaço...\n");
            }
            break;
        case 1:
            printf("\nFase 2 - O Caminho da Cratera\n");
            printf("\nO caminho se bifurca novamente. À esquerda, uma cratera estranha, com uma sensação desconfortante no ar. À direita, um campo aberto, mas uma tempestade de poeira avança ao longe.\n");
            printf("Você deve escolher o caminho:\n");
            printf("1. Cratera Estranha\n");
            printf("2. Tempestade de Poeira\n");
            printf("Escolha: ");
            scanf("%d", &escolha);
            if (escolha == 1) {
                *dificuldade = 1; // Caminho fácil, perguntas fáceis
                printf("Cratera Estranha. Você se aproxima da cratera, mas logo percebe que não está sozinho. Ruídos estranhos ecoam ao seu redor. O tablet em um pilar próximo se acende e uma voz robótica diz:\n");
                printf("Você chegou à cratera. Para continuar, responda corretamente à seguinte pergunta...\n");
            } else if (escolha == 2) {
                *dificuldade = 2; // Caminho difícil, perguntas difíceis
                printf("Tempestade de Poeira. Você decide seguir pela tempestade de poeira. A visibilidade é baixa, mas você segue com cuidado. Um pilar de cristal aparece no seu caminho, iluminado por um brilho forte. A tela do tablet nele começa a brilhar com uma mensagem:\n");
                printf("Para continuar sua jornada, responda à seguinte questão sobre o cosmos...\n");
            }
            break;
        case 2:
            printf("\nFase 3 - A Rocha Estranha\n");
            printf("\nÀ sua frente, uma formação rochosa estranha. Algo se move nas sombras. Você deve escolher entre explorar a formação ou seguir em frente.\n");
            printf("Você deve escolher o caminho:\n");
            printf("1. Rocha Estranha\n");
            printf("2. Destroços de Naves Antigas\n");
            printf("Escolha: ");
            scanf("%d", &escolha);
            if (escolha == 1) {
                *dificuldade = 1; // Caminho fácil, perguntas fáceis
                printf("Rocha Estranha. Você se aproxima da formação rochosa, mas algo se move nas sombras. O tablet próximo se acende, e uma voz eletrônica fala:\n");
                printf("Você encontrou algo incomum. Para seguir, você deve responder corretamente a uma pergunta...\n");
            } else if (escolha == 2) {
                *dificuldade = 2; // Caminho difícil, perguntas difíceis
                printf("Destroços de Naves Antigas. Você decide explorar os destroços. Dentro deles, uma tela de pilar se ilumina e uma voz ecoa na caverna:\n");
                printf("A cada pedaço que você toca, o passado se revela. Para continuar, responda corretamente...\n");
            }
            break;
        case 3:
            printf("\nFase 4 - A Passagem dos Cristais\n");
            printf("\nÀ sua frente, um corredor iluminado por cristais misteriosos. Você ouve um som distante, como se algo estivesse se arrastando. Você deve decidir entre a estrutura metálica estranha ou o caminho iluminado pelos cristais.\n");
            printf("Você deve escolher o caminho:\n");
            printf("1. Estrutura Metálica Estranha\n");
            printf("2. Passagem Iluminada por Cristais\n");
            printf("Escolha: ");
            scanf("%d", &escolha);
            if (escolha == 1) {
                *dificuldade = 1; // Caminho fácil, perguntas fáceis
                printf("Estrutura Metálica Estranha. Você se aproxima da estrutura metálica, que emite um som de energia fraca. A tela de um tablet se acende diante de você e uma voz ecoa:\n");
                printf("Para ativar o mecanismo, você deve responder corretamente à pergunta... \n");
            } else if (escolha == 2) {
                *dificuldade = 2; // Caminho difícil, perguntas difíceis
                printf("Você escolhe o caminho iluminado por cristais. A luz parece reconfortante, mas há algo estranho na atmosfera. O tablet se acende diante de você:\n");
                printf("Para passar, responda corretamente...\n");
            }
            break;
        case 4:
            printf("\nFase 5 - O Caminho da Nuvem de Poeira\n");
            printf("\nO ar se torna mais pesado. À esquerda, algo brilha em meio a uma cratera coberta por névoa espessa. À direita, o terreno parece estável, mas há uma vibração no solo.\n");
            printf("Você deve escolher o caminho:\n");
            printf("1. Sinal Distante\n");
            printf("2. Caverna Escura\n");
            printf("Escolha: ");
            scanf("%d", &escolha);
            if (escolha == 1) {
                *dificuldade = 1; // Caminho fácil, perguntas fáceis
                printf("Sinal Distante. Você segue em direção ao sinal, superando a névoa espessa. O tablet ao longe se ilumina com uma nova mensagem:\n");
                printf("Para continuar sua busca, você deve responder corretamente... \n");
            } else if (escolha == 2) {
                *dificuldade = 2; // Caminho difícil, perguntas difíceis
                printf("Caverna Escura. Você escolhe a caverna escura. Dentro, algo se move nas sombras. O tablet acende sua tela com uma pergunta sobre o cosmos:\n");
                printf("Para seguir em frente, você deve responder corretamente...\n");
            }
            break;
        default:
            printf("\nFase desconhecida. Boa sorte!\n");
    }
}

int main() {
    setlocale(LC_ALL, "");
    
    int dificuldade, oxigenio, pecas = 0, fase = 0, indicePergunta = 0;
    
    printf("=====================================================\n");
    printf("      Bem-vindo ao jogo Back Home He3!              \n");
    printf("=====================================================\n");

    printf("=====================================================\n");
    printf("||                                                    ||\n");
    printf("||  Você é um astronauta americano, designado para    ||\n");
    printf("||  uma missão histórica: viajar até a Lua em busca   ||\n");
    printf("||  de uma fonte de energia rara e poderosa chamada   ||\n");
    printf("||  Hélio-3.                                          ||\n");
    printf("||                                                    ||\n");
    printf("||  O Hélio-3 é um combustível vital para a           ||\n");
    printf("||  humanidade, prometendo resolver a crise energética||\n");
    printf("||  que aflige a Terra.                               ||\n");
    printf("||                                                    ||\n");
    printf("||  A missão parecia perfeita. Sua nave estava        ||\n");
    printf("||  equipada com a mais avançada tecnologia e você    ||\n");
    printf("||  estava pronto para trazer uma solução para o      ||\n");
    printf("||  futuro da Terra.                                  ||\n");
    printf("||  Mas o inesperado aconteceu...                     ||\n");
    printf("||                                                    ||\n");
    printf("||  Durante a descida na superfície lunar, um erro    ||\n");
    printf("||  crítico no sistema de navegação causou uma        ||\n");
    printf("||  colisão brutal com a Lua.                         ||\n");
    printf("||  Sua nave foi destruída, e suas peças e            ||\n");
    printf("||  componentes essenciais foram espalhadas por       ||\n");
    printf("||  diferentes regiões da Lua, criando uma situação   ||\n");
    printf("||  desesperadora.                                    ||\n");
    printf("||                                                    ||\n");
    printf("||  Agora, você se encontra isolado, sem comunicação  ||\n");
    printf("||  com a Terra, e sem a nave que poderia levá-lo de  ||\n");
    printf("||  volta. A única esperança de sobrevivência é       ||\n");
    printf("||  reunir todas as peças da nave espalhadas pela     ||\n");
    printf("||  vastidão lunar e reconstruí-la.                   ||\n");
    printf("||  Mas a Lua é um lugar perigoso e inexplorado.      ||\n");
    printf("||  Enfrentando ambientes hostis, falta de recursos   ||\n");
    printf("||  e possíveis obstáculos desconhecidos, sua missão  ||\n");
    printf("||  de volta para casa será extremamente desafiadora. ||\n");
    printf("||                                                    ||\n");
    printf("||  Você precisará resolver enigmas, enfrentar        ||\n");
    printf("||  perigos e superar desafios enquanto busca por     ||\n");
    printf("||  cada parte perdida da nave. Cada segundo conta,   ||\n");
    printf("||  e cada decisão pode ser crucial para sua          ||\n");
    printf("||  sobrevivência.                                    ||\n");
    printf("||                                                    ||\n");
    printf("||  O destino da Terra e sua vida estão em suas       ||\n");
    printf("||  mãos. Está pronto para a aventura?                ||\n");
    printf("||                                                    ||\n");
    printf("||  Escolha sua dificuldade e prepare-se para         ||\n");
    printf("||  enfrentar o desconhecido.                         ||\n");
    printf("||                                                    ||\n");
    printf("=====================================================\n");
   

    // Menu de dificuldade
    do {
        printf("=====================================================\n");
        printf("      Bem-vindo ao jogo Back Home He3!              \n");
        printf("=====================================================\n");
        printf("ESCOLHA A DIFICULDADE QUE DESEJA JOGAR\n");
        printf("1. Fácil\n");
        printf("2. Médio\n");
        printf("3. Difícil\n");
        printf("=====================================================\n");
        printf("Digite sua escolha: ");
        scanf("%d", &dificuldade);
        if (dificuldade < 1 || dificuldade > 3) {
            printf("Número inválido! Por favor, escolha novamente.\n\n");
        }
    } while (dificuldade < 1 || dificuldade > 3);

    // Mensagem de introdução com base na dificuldade
    textoImersivo(dificuldade);
    printf("\nPressione Enter para continuar...\n");
    getchar(); // captura Enter pendente
    getchar(); // aguarda o usuário apertar Enter

    // A quantidade de oxigênio varia com a dificuldade
    if (dificuldade == 1) oxigenio = 5;
    else if (dificuldade == 2) oxigenio = 3;
    else oxigenio = 2;

    // Loop do jogo com controle manual da fase
    while (fase < 5) {
        if (oxigenio <= 0) {
            printf("\nVocê ficou sem oxigênio. A missão acabou. GAME OVER\n");
            break;
        }

        limparTela();

    // Chama a função para introduzir a fase, passando o ponteiro para dificuldade
    introduzirFase(fase, &dificuldade);
    
    // Salva a quantidade de peças antes de responder a pergunta
    int pecasAntes = pecas;

    // Escolhe a pergunta com base na dificuldade definida pela escolha do caminho
    if (dificuldade == 1) {
        perguntas(perguntasFaceis[indicePergunta], &pecas, &oxigenio);
    } else {
        perguntas(perguntasDificeis[indicePergunta], &pecas, &oxigenio);
    }
        indicePergunta++;

        exibirOxigenio(oxigenio);
        exibirFoguete(pecas);

        if (pecas > pecasAntes) {
            printf("Você avançou para a próxima fase!\n");
            fase++;
        } else {
            printf("Você ainda tem %d barra(s) de oxigênio. Tente novamente!\n", oxigenio);
        }

        if (fase < 5 && oxigenio > 0) {
            printf("\nPressione Enter para continuar...\n");
            getchar();
            getchar();
        }
        
        limparTela();

        // Verifica se o jogador reuniu todas as peças
        if (pecas >= 5) {
			
    escreverDevagar("==============================================\n");
    escreverDevagar("  Todas as peças foram coletadas com sucesso!  ");
    escreverDevagar("==============================================\n");
    escreverDevagar("Você superou a solidão, o medo e os perigos da Lua.");
    escreverDevagar("Cada decisão difícil, cada enigma resolvido e cada passo dado");
    escreverDevagar("foram prova da sua coragem, determinação e inteligência.");
    escreverDevagar("Você não apenas sobreviveu... você venceu.\n");
    escreverDevagar("Agora que a nave foi reparada, um último sistema foi ativado...");
    escreverDevagar("Um compartimento oculto se abre, revelando um documento digital...\n");
    escreverDevagar("Pressione Enter para acessá-lo.");
getchar();
getchar();
limparTela();
escreverDevagar("=============================================================");
escreverDevagar("               ARQUIVO DE PESQUISA - SIGILO NÍVEL 5          ");
escreverDevagar("             CENTRO INTERNACIONAL DE PESQUISAS LUNARES       ");
escreverDevagar("-------------------------------------------------------------");
escreverDevagar("                     ARQUIVO: H3-EnergiaFinal.dat            ");
escreverDevagar("                     DATA: 27 de março de 2136               ");
escreverDevagar("                     PESQUISADOR: Dr. Elio Nakamura          ");
escreverDevagar("=============================================================\n");

escreverDevagar("TÍTULO: Potencial do Isótopo Hélio-3 como Fonte de Energia para a Terra\n");

escreverDevagar("RESUMO:");
escreverDevagar("O Hélio-3 (³He) é um isótopo não radioativo, leve e extremamente raro na Terra,");
escreverDevagar("mas abundante na superfície da Lua. Ele se tornou o principal foco de pesquisas");
escreverDevagar("sobre energia limpa, devido ao seu imenso potencial para reações de fusão nuclear controladas.");
escreverDevagar("Essas reações não produzem radiação prejudicial significativa e oferecem uma alternativa viável");
escreverDevagar("às fontes atuais de energia baseadas em combustíveis fósseis e fissão nuclear.\n");

escreverDevagar("BENEFÍCIOS ENERGÉTICOS DO HÉLIO-3:");
escreverDevagar("- Reações de fusão com Hélio-3 geram energia com pouquíssima radiação residual;");
escreverDevagar("- Não produzem resíduos radioativos de longa duração;");
escreverDevagar("- Não emitem gases poluentes;");
escreverDevagar("- Eficiência energética extremamente alta: 1 tonelada de Hélio-3 pode gerar cerca de 10 TWh;");
escreverDevagar("- A estabilidade e controle da fusão são superiores às reações com deutério-trítio.\n");

escreverDevagar("DADOS DE DISPONIBILIDADE:");
escreverDevagar("- A Terra possui quantidades insignificantes de Hélio-3;");
escreverDevagar("- Estima-se que a Lua contenha mais de 1 milhão de toneladas no regolito;");
escreverDevagar("- A mineração lunar pode suprir a demanda energética do planeta por séculos.");
escreverDevagar("- A cada 100 toneladas de regolito, estima-se a extração de até 10 gramas de ³He.\n");

escreverDevagar("CONCLUSÃO:");
escreverDevagar("O Hélio-3 representa uma revolução energética em escala global.");
escreverDevagar("Sua aplicação segura, limpa e eficiente pode garantir a sobrevivência da civilização humana");
escreverDevagar("diante do colapso iminente dos recursos energéticos terrestres.");
escreverDevagar("Este documento contém as evidências científicas e projeções energéticas que justificam");
escreverDevagar("a exploração lunar como prioridade da humanidade no século XXI.\n");

escreverDevagar("=======================================================================");
escreverDevagar("        FIM DO DOCUMENTO - Pressione Enter para construir o foguete.   ");
escreverDevagar("=======================================================================\n");
 
getchar();
limparTela();

        }
    }

    return 0;
}