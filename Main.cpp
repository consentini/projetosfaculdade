//
// Created by GabrielConsentini on 04/11/2023.
//


verificar codigo com posições corrigidas

#include <iostream>
#include <vector>
#include <string>

class AgenteAspirador {
public:
    AgenteAspirador() : energia(100), capacidade_bolsa(10), posicao_x(0), posicao_y(0), energia_gasta(0) {}

    // Função para determinar qual ação tomar
    void tomarAcao(std::vector<std::vector<std::string>>& ambiente) {
        if (energia <= 0) {
            voltarParaCasa();
            return;
        }

        if (bolsaCheia()) {
            voltarParaCasa();
            return;
        }

        if (ambiente[posicao_x][posicao_y] == "sujo") {
            aspirar(ambiente);
        } else {
            mover(ambiente);
        }
    }

    int getEnergiaGasta() const {
        return energia_gasta;
    }

private:
    int energia;
    int capacidade_bolsa;
    int posicao_x;
    int posicao_y;
    int energia_gasta;

    bool bolsaCheia() {
        return capacidade_bolsa <= 0;
    }

    void aspirar(std::vector<std::vector<std::string>>& ambiente) {
        energia--;
        capacidade_bolsa--;
        ambiente[posicao_x][posicao_y] = "limpo";
        energia_gasta++;
        std::cout << "Aspirou a sujeira na posicao (" << posicao_x << ", " << posicao_y << ")" << std::endl;
    }

    void mover(std::vector<std::vector<std::string>>& ambiente) {
        energia--;
        if (posicao_x % 2 == 0) { // Move para a direita
            if (posicao_y < ambiente[0].size() - 1) {
                posicao_y++;
            } else {
                posicao_x++;
            }
        } else { // Move para a esquerda
            if (posicao_y > 0) {
                posicao_y--;
            } else {
                posicao_x++;
            }
        }
        if (posicao_x < ambiente.size()) {
            std::cout << "Moveu para a posicao (" << posicao_x << ", " << posicao_y << ")";
            if (ambiente[posicao_x][posicao_y] == "limpo") {
                std::cout << " - Nao ha sujeira" << std::endl;
            } else {
                std::cout << std::endl;
            }
        }
    }

    void voltarParaCasa() {
        energia -= posicao_x + posicao_y; // Custo do movimento de volta para casa
        posicao_x = 0;
        posicao_y = 0; // Retorna para a posicao inicial (Casa)
        capacidade_bolsa = 10; // Esvazia a bolsa
        std::cout << "Voltou para Casa (posicao (0, 0))" << std::endl;
    }
};

bool objetivoAlcancado(const std::vector<std::vector<std::string>>& ambiente) {
    for (const auto& linha : ambiente) {
        for (const std::string& localizacao : linha) {
            if (localizacao == "sujo") {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::vector<std::vector<std::string>> ambiente(4, std::vector<std::string>(4, "limpo"));

    ambiente[1][0] = "sujo"; // Posicao 3
    ambiente[2][1] = "sujo"; // Posicao 6
    ambiente[2][0] = "sujo"; // Posicao 8
    ambiente[3][1] = "sujo"; // Posicao 9
    ambiente[0][2] = "sujo"; // Posicao 11
    ambiente[1][3] = "sujo"; // Posicao 13
    ambiente[2][2] = "sujo"; // Posicao 14

    AgenteAspirador agente;

    while (!objetivoAlcancado(ambiente)) {
        agente.tomarAcao(ambiente);
    }

    std::cout << "Objetivo alcancado!" << std::endl;
    std::cout << "Energia gasta: " << agente.getEnergiaGasta() << std::endl;

    return 0;
}
