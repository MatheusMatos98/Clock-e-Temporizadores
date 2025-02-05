#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_BLUE 11     // GPIO para LED azul (GPIO 11)
#define LED_RED 12      // GPIO para LED vermelho (GPIO 12)
#define LED_GREEN 13    // GPIO para LED verde (GPIO 13)
#define BUTTON_PIN 5    // GPIO para o botão (GPIO 5)

// Estados dos LEDs
typedef enum {
    ALL_ON,    // Todos acesos
    BLUE_OFF,  // Azul apaga
    RED_OFF,   // Vermelho apaga
    GREEN_OFF  // Verde apaga
} state_t;

state_t current_state = GREEN_OFF; // Começa desligado
volatile bool cycle_started = false; // Indica se o ciclo está ativo

struct repeating_timer timer; // Temporizador

// Callback do temporizador (3 segundos para cada transição de LEDs)
bool timer_callback(struct repeating_timer *t) {
    switch (current_state) {
        case ALL_ON:
            gpio_put(LED_BLUE, 0);      // Apaga o LED azul
            current_state = BLUE_OFF;
            break;
        case BLUE_OFF:
            gpio_put(LED_RED, 0);       // Apaga o LED vermelho
            current_state = RED_OFF;
            break;
        case RED_OFF:
            gpio_put(LED_GREEN, 0);     // Apaga o LED verde
            current_state = GREEN_OFF;
            cycle_started = false;      // Finaliza o ciclo, permitindo nova ativação pelo botão
            return false;               // Para o temporizador
        case GREEN_OFF:
            return false; // Garante que nada aconteça se o ciclo não estiver ativo
    }
    return true; // Continua o temporizador a cada 3 segundos
}

// Função de interrupção para detectar o clique no botão
void button_callback(uint gpio, uint32_t events) {
    if (!cycle_started) { // Apenas inicia um novo ciclo se não houver um em andamento
        cycle_started = true;
        current_state = ALL_ON;

        gpio_put(LED_BLUE, 1);    // Liga todos os LEDs
        gpio_put(LED_RED, 1);
        gpio_put(LED_GREEN, 1);

        // Inicia o temporizador para 3 segundos
        add_repeating_timer_ms(3000, timer_callback, NULL, &timer);
    }
}

int main() {
    stdio_init_all();
    
    // Configuração dos GPIOs dos LEDs
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Configuração do botão
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN); // Habilita resistor de pull-up interno

    // Configura a interrupção do botão para acionar na borda de descida
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    while (1) {
        sleep_ms(100); // Pequeno atraso para reduzir carga no processador
    }
}
