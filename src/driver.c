#include "driver.h"

#include <stdio.h>
#include <string.h>

/* Função principal de um Motorista. Deve executar um ciclo infinito onde em
 * cada iteração lê uma operação dos restaurantes e se a mesma tiver id
 * diferente de -1 e se data->terminate ainda for igual a 0, processa-a e
 * escreve a resposta para os clientes. Operações com id igual a -1 são
 * ignoradas (op inválida) e se data->terminate for igual a 1 é porque foi
 * dada ordem de terminação do programa, portanto deve-se fazer return do
 * número de operações processadas. Para efetuar estes passos, pode usar os
 * outros métodos auxiliares definidos em driver.h.
 */
int execute_driver(int driver_id, struct communication_buffers* buffers, struct main_data* data) {
    int counter = 0;
    while (1) {
        struct operation op;
        op.id = -1;
        driver_receive_operation(&op, buffers, data);
        if (*data->terminate) {
            return counter;
        } else if (op.id != -1) {
            driver_process_operation(&op, driver_id, data, &counter);
            driver_send_answer(&op, buffers, data);
        }
    }
}

/* Função que lê uma operação do buffer de memória partilhada entre restaurantes e motoristas.
 * Antes de tentar ler a operação, deve verificar se data->terminate tem valor 1.
 * Em caso afirmativo, retorna imediatamente da função.
 */
void driver_receive_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data) {
    if (!data->terminate) {
        read_rest_driver_buffer(buffers->rest_driv, data->buffers_size, op);
    } else {
        return;
    }
}

/* Função que processa uma operação, alterando o seu campo receiving_driver para o id
 * passado como argumento, alterando o estado da mesma para 'D' (driver), e
 * incrementando o contador de operações. Atualiza também a operação na estrutura data.
 */
void driver_process_operation(struct operation* op, int driver_id, struct main_data* data, int* counter) {
    op->receiving_driver = driver_id;
    op->status = 'D';
    *(counter)++;
    memcpy(data->results + op->id, op, sizeof(struct operation));
}

/* Função que escreve uma operação no buffer de memória partilhada entre
 * motoristas e clientes.
 */
void driver_send_answer(struct operation* op, struct communication_buffers* buffers, struct main_data* data) {
    write_driver_client_buffer(buffers->driv_cli, data->buffers_size, op);
}