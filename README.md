# Projeto: Semáforo com Raspberry Pi Pico

## Descrição
Este projeto implementa um semáforo utilizando um **Raspberry Pi Pico** e LEDs para representar os sinais de trânsito. O código faz uso da biblioteca **pico/stdlib.h** e do **hardware/gpio.h** para controle dos pinos GPIO do microcontrolador. O funcionamento baseia-se em um temporizador repetitivo que alterna entre os estados do semáforo em intervalos de 3 segundos.

## Funcionamento
1. Ao iniciar o sistema, o LED vermelho acende por **3 segundos**.
2. Em seguida, o LED vermelho apaga e o LED azul acende por **3 segundos**.
3. Depois, o LED azul apaga e o LED verde acende por **3 segundos**.
4. O LED verde apaga e o ciclo recomeça com o LED vermelho.

O ciclo continua indefinidamente.

## Estrutura do Código

### Definição dos pinos dos LEDs
Os LEDs estão conectados a pinos específicos do Raspberry Pi Pico:
```c
const uint led_pin_red = 13;
const uint led_pin_blue = 12;
const uint led_pin_green = 11;
```

### Enumeração dos estados do semáforo
Foi definida uma enumeração para facilitar o controle do estado atual do semáforo:
```c
typedef enum {
    RED,
    BLUE,
    GREEN
} TrafficLightState;
```
A variável global `current_state` é utilizada para armazenar o estado atual.

### Função de callback do temporizador
A função `repeating_timer_callback()` é chamada automaticamente a cada 3 segundos para alternar entre os LEDs:
```c
bool repeating_timer_callback(struct repeating_timer *t) {
    gpio_put(led_pin_red, false);
    gpio_put(led_pin_blue, false);
    gpio_put(led_pin_green, false);

    switch (current_state) {
        case RED:
            gpio_put(led_pin_red, true);
            current_state = BLUE;
            break;
        case BLUE:
            gpio_put(led_pin_blue, true);
            current_state = GREEN;
            break;
        case GREEN:
            gpio_put(led_pin_green, true);
            current_state = RED;
            break;
    }
    return true;
}
```
Essa função apaga todos os LEDs e liga apenas aquele correspondente ao novo estado do semáforo.

### Inicialização no `main()`
O `main()` realiza as seguintes etapas:
1. Configura os pinos dos LEDs como saída.
2. Liga o LED vermelho no início.
3. Inicializa a comunicação serial com `stdio_init_all()`.
4. Configura um temporizador que chama `repeating_timer_callback()` a cada 3 segundos.
5. Entra em um loop infinito imprimindo "**esperando....**" a cada 1 segundo na porta serial:

```c
while (true) {
    printf("esperando....\n");
    sleep_ms(1000);
}
```

## Dependências
Para compilar e rodar este código, é necessário ter o SDK do **Raspberry Pi Pico** configurado corretamente.

## Como Compilar e Executar
1. Clone este repositório:
   ```sh
   git clone https://github.com/marcelofainor/semaforo_1.git
   ```
2. Navegue até a pasta do projeto:
   ```sh
   cd semaforo_1
   ```
3. Compile o código utilizando o CMake e o SDK do Raspberry Pi Pico.
4. Envie o arquivo `.uf2` para a placa.
5. O semáforo começará a funcionar automaticamente.

## Autor
Desenvolvido por Marcelo B. de Almeida.

---
Caso tenha alguma dúvida ou sugestão, fique à vontade para contribuir ou abrir uma issue no repositório. 🚀

