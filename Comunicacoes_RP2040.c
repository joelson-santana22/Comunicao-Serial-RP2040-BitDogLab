// Importação de bibliotecas
#include <stdio.h>
#include <ctype.h> 
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/i2c.h"
#include "pio_matrix.pio.h"
#include "libraries/ssd1306.h"
#include "libraries/font.h"

// Definição das pinagens GPIO
#define pin_blue 12 
#define pin_green 11

#define NUM_PIXELS 25
#define matriz5x5 7

#define botaoA 5
#define botaoB 6

#define I2C_PORT i2c1
#define ADDR 0x3C
#define I2C_SDA 14
#define I2C_SCL 15

// Criação das variáveis globais para controle do display e dos botões
volatile bool botaoA_press = false; 
volatile bool botaoB_press = false;
ssd1306_t ssd;

// Declaração de funções que serão utilizadas
void button_isr(uint gpio, uint32_t events);
void setup();


// Função para inicialização do periféricos utilizados
void setup(){
    // LED azul
    gpio_init(pin_blue);
    gpio_set_dir(pin_blue, GPIO_OUT);

    // LED verde
    gpio_init(pin_green);
    gpio_set_dir(pin_green, GPIO_OUT);

    // Botão A
    gpio_init(botaoA);
    gpio_set_dir(botaoA, GPIO_IN);
    gpio_pull_up(botaoA);

    // Configuração do callback para o botão A
    gpio_set_irq_enabled_with_callback(botaoA, GPIO_IRQ_EDGE_FALL, true, &button_isr); 

    // Botão B
    gpio_init(botaoB);
    gpio_set_dir(botaoB, GPIO_IN);
    gpio_pull_up(botaoB);

    // Configuração do callback para o botão B
    gpio_set_irq_enabled_with_callback(botaoB, GPIO_IRQ_EDGE_FALL, true, &button_isr);

    // I2C para comunicação com o display 
    i2c_init(I2C_PORT, 400 * 1000); // Configura a comunicação I2C com velocidade de 400kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SCL);

    // Inicialização e configuração do Display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ADDR, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}

// Criação das matrizes para representar os números de 0 a 9.
// Número 0
double num0[25] = {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
};

// Número 1
double num1[25] = {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0
};

// Número 2
double num2[25] = {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
};

// Número 3
double num3[25] = {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
};

// Número 4
double num4[25] = {
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0
};

// Número 5
double num5[25] = {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
};

// Número 6
double num6[25] = {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
};

// Número 7
double num7[25] = {
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
};

// Número 8
double num8[25] = {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
};

// Número 9
double num9[25] = {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
};

// Função para converção de valores RGB em um valor de 32 bits no formato específico da matriz.
uint32_t matrix_rgb(double r, double g, double b) {
    unsigned char R = r * 10 ;
    unsigned char G = g * 15;
    unsigned char B = b * 15;
    return (G << 24) | (R << 16) | (B << 8);
}


//Função que apaga a matriz de LEDs (todos os LEDs).
void apagar_leds(PIO pio, uint sm) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
    }
}

// Função que acende todos os LEDS
void acender_leds(PIO pio, uint sm, double r, double g, double b) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, matrix_rgb(b, r, g));
    }
}

// Função para formar o número na matriz
void formar_numero(double *forma, PIO pio, uint sm, double r, double g, double b){
    for(int16_t i = 0; i < NUM_PIXELS; i++){
        pio_sm_put_blocking(pio, sm, matrix_rgb(forma[i] * r, forma[i] * g, forma[i] * b));
    }   
}

// Função Switch Case responsável por imprimir o número recebido 
void imprimir_num(char caracter, PIO pio, uint sm){
    switch(caracter){
        case '0': formar_numero(num0, pio, sm, 0.5, 0.6, 0.2);
                  break;
        case '1': formar_numero(num1, pio, sm, 0.5, 0.6, 0.2);
                  break;
        case '2': formar_numero(num2, pio, sm, 0.5, 0.6, 0.2);
                  break;
        case '3': formar_numero(num3, pio, sm, 0.5, 0.6, 0.2);
                  break;
        case '4': formar_numero(num4, pio, sm, 0.5, 0.6, 0.2);
                  break;
        case '5': formar_numero(num5, pio, sm, 0.5, 0.6, 0.2);
                  break;
        case '6': formar_numero(num6, pio, sm, 0.5, 0.6, 0.2);
                  break;
        case '7': formar_numero(num7, pio, sm, 0.5, 0.6, 0.2);
                  break;
        case '8': formar_numero(num8, pio, sm, 0.5, 0.6, 0.2);
                  break;
        case '9': formar_numero(num9, pio, sm, 0.5, 0.6, 0.2);
                  break;
        default: break;
    }
}


// Função principal do código
int main()
{
    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &pio_matrix_program);
    pio_matrix_program_init(pio, sm, offset, matriz5x5);

    setup();    // Chamando a função de exercurção
    stdio_init_all();   

    while (true) {
        // Verificação de conexão com o Monitor Serial
        if(stdio_usb_connected()){
            char character = getchar(); // Leitura do caractere recebido via Seria Monitor
            
            //  Condicional para verifica se o caractere recebido é um némero 
            if(isdigit(character)){  
                imprimir_num(character, pio, sm);           // Exibição do número digitado na matriz5x5
                printf("Número: %c\n", character);          // Impressão do caracter digitado no Seria Monitor
                ssd1306_fill(&ssd, false);                  // Limpeza do display
                ssd1306_draw_char(&ssd, character, 64, 32); // O Caractere digitado é mostrado no display 
                ssd1306_send_data(&ssd);                    // Atualização do display 
            }else{
                apagar_leds(pio, sm);                       // Limpaza da matriz5x5
                printf("Caracter: %c\n", character);        // Impressão do caracter digitado no Seria Monitor
                
                ssd1306_fill(&ssd, false);                  // Limpaza do display
                ssd1306_draw_char(&ssd, character, 64, 32); // O Caractere digitado é mostrado no display 
                ssd1306_send_data(&ssd);                    //  Atualização do display 
            }
        }
    sleep_ms(50);                                           // Pausa breve para amenizar o uso da CPU   
    }
}

// Tratamento com interrupção para verificar o click no botão com debounce
void button_isr(uint gpio, uint32_t events){
    static absolute_time_t last_press = 0;                  // Aqui armazena o tempo do último click
    absolute_time_t now = get_absolute_time();              // Aqui obtem-se o tempo atual 

    if(absolute_time_diff_us(last_press, now) > 200000){    // Implemeta um debounce de 200 ms
        // Conndicional 'Se' que verifica se o botão A foi pressionado
        if(gpio == botaoA){                                 
            botaoA_press = !botaoA_press; 
            gpio_put(pin_green, botaoA_press);              // Aqui altera-se o estado do LED verde 
            if(gpio_get(pin_green)){                        // Condicional para LED verde ligado ou não
                printf("LED VERDE: LIGADO\n");  
                
                // Se ligado, o display informa: "LED verde ligado"
                ssd1306_fill(&ssd, false);  
                ssd1306_draw_string(&ssd, "LED", 5, 30);    
                ssd1306_draw_string(&ssd, "VERDE:", 35, 30);
                ssd1306_draw_string(&ssd, "LIGADO", 79, 30);
                ssd1306_send_data(&ssd);    
            }else{                                          // Se o LED verde não estiver ligado 
                printf("LED verde: desligado\n");

                // Se desligado, o display informa: "LED verde desligado"
                ssd1306_fill(&ssd, false);
                ssd1306_draw_string(&ssd, "LED", 30, 25);
                ssd1306_draw_string(&ssd, "VERDE:", 60, 25);
                ssd1306_draw_string(&ssd, "DESLIGADO", 30, 40);
                ssd1306_send_data(&ssd);
            }
        }else{
            // Condicional 'Se não' que verifica se o botão B foi pressionado
            if(gpio == botaoB){                             
                botaoB_press = !botaoB_press;
                gpio_put(pin_blue, botaoB_press);            // Aqui altera-se o estado do LED azul 
                if(gpio_get(pin_blue)){                      // Condicional para LED azul ligado ou não
                    printf("LED AZUL: LIGADO\n");

                    // Aqui faz a atualização do display com a informação "LED azul ligado"
                    ssd1306_fill(&ssd, false);
                    ssd1306_draw_string(&ssd, "LED", 8, 30);
                    ssd1306_draw_string(&ssd, "AZUL:", 37, 30);
                    ssd1306_draw_string(&ssd, "LIGADO", 73, 30);
                    ssd1306_send_data(&ssd);
                }else{                                       // Se o LED azul não estiver ligado 
                    printf("LED AZUL DESLIGADO\n");
                    
                    // Atualiza o display com a informação "LED azul desligado"
                    ssd1306_fill(&ssd, false);
                    ssd1306_draw_string(&ssd, "LED", 35, 25);
                    ssd1306_draw_string(&ssd, "AZUL", 65, 25);
                    ssd1306_draw_string(&ssd, "DESLIGADO", 30, 40);
                    ssd1306_send_data(&ssd);
                }
            }
        }
        last_press = now;                                    // Atualiza o tempo do último click
    }
}

