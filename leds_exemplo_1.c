#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"

// Constantes para os pinos dos LEDs
const uint led_pin_red = 13; 
const uint led_pin_blue = 12;
const uint led_pin_green = 11;

// Definição do estado do semáforo
typedef enum {
    RED,
    BLUE,
    GREEN
} TrafficLightState;

TrafficLightState current_state = RED;

// Função de callback do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs
    gpio_put(led_pin_red, false);
    gpio_put(led_pin_blue, false);
    gpio_put(led_pin_green, false);

    // Muda para o próximo estado e acende o LED correspondente
    switch (current_state) {
        case RED:
            gpio_put(led_pin_blue, true);  // Liga o LED azul
            current_state = BLUE;          // Próximo estado: azul
            break;
        case BLUE:
            gpio_put(led_pin_green, true); // Liga o LED verde
            current_state = GREEN;         // Próximo estado: verde
            break;
        case GREEN:
            gpio_put(led_pin_red, true);   // Liga o LED vermelho
            current_state = RED;           // Próximo estado: vermelho
            break;
    }

    return true; // Mantém o temporizador ativo
}

int main() {
    // Inicializa as portas dos LEDs
    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);

    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);

    gpio_init(led_pin_green);
    gpio_set_dir(led_pin_green, GPIO_OUT);

    // Liga o LED vermelho inicialmente
    gpio_put(led_pin_red, true);
    
    // Inicializa a comunicação serial
    stdio_init_all();

    // Configura o temporizador para iniciar APÓS 3 segundos e repetir a cada 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal: imprime "esperando...." a cada segundo
    while (true) {
        printf("esperando....\n");
        sleep_ms(1000);
    }

    return 0;
}
