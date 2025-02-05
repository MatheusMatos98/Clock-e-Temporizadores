#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define LED_RED 11     // GPIO para LED vermelho
#define LED_YELLOW 12  // GPIO para LED amarelo
#define LED_GREEN 13   // GPIO para LED verde

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

// Estados do semáforo
typedef enum {
    RED,
    YELLOW,
    GREEN
} state_t;

state_t current_state = RED; // Estado inicial do semáforo

// Callback do temporizador para o semáforo (3 segundos)
bool repeating_timer_callback(struct repeating_timer *t) {
    switch (current_state) {
        case RED:
            gpio_put(LED_RED, 0);       // Apaga o LED vermelho
            gpio_put(LED_YELLOW, 1);    // Acende o LED amarelo
            current_state = YELLOW;
            break;
        case YELLOW:
            gpio_put(LED_YELLOW, 0);    // Apaga o LED amarelo
            gpio_put(LED_GREEN, 1);     // Acende o LED verde
            current_state = GREEN;
            break;
        case GREEN:
            gpio_put(LED_GREEN, 0);     // Apaga o LED verde
            gpio_put(LED_RED, 1);       // Acende o LED vermelho
            current_state = RED;
            break;
    }
    return true; // Continua repetindo a cada 3 segundos
}

// Callback do temporizador para exibir a mensagem no monitor serial (1 segundo)
bool serial_timer_callback(struct repeating_timer *t) {
    printf("Semáforo ativo\n"); // Envia a mensagem para o monitor serial
    fflush(stdout); // Força a liberação do buffer
    return true;
}

int main() {
    // Inicializa a UART
    stdio_init_all(); // Inicializa a comunicação serial padrão (USB)
    
    // Configuração dos GPIOs
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    
    // Inicia o semáforo no vermelho
    gpio_put(LED_RED, 1);
    gpio_put(LED_YELLOW, 0);
    gpio_put(LED_GREEN, 0);
    
    // Configura o temporizador periódico para 3 segundos (3000 ms) para os LEDs
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);
    
    // Configura o temporizador periódico para 1 segundo (1000 ms) para a mensagem serial
    struct repeating_timer serial_timer;
    add_repeating_timer_ms(1000, serial_timer_callback, NULL, &serial_timer);
    
    while (1) {
        // Loop principal não precisa fazer nada, pois os callbacks dos temporizadores cuidam de tudo
        tight_loop_contents();
    }
}