#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"
#include "hardware/irq.h"
#include "lib/ssd1306.h"
#include "lib/font.h"

// Definição dos pinos
#define BUTTON_A 5
#define BUTTON_B 6
#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define DISPLAY_ADDR 0x3C

// Constantes
#define MAX_MEASUREMENTS 10
#define PWM_WRAP 255
#define DEBOUNCE_TIME_MS 200
#define AVERAGE_TOLERANCE 0.1

// Variaveis globais
static volatile uint32_t measurement_start = 0;
static volatile uint32_t measurements[MAX_MEASUREMENTS];
static volatile int measurement_count = 0;
static volatile uint32_t last_button_time = 0;
static volatile float current_average = 0;
static volatile bool system_paused = false;
static ssd1306_t display;

// Prototipos das funções
void init_hardware(void);
void init_pwm(uint gpio);
void set_led_color(float red, float green, float blue);
float calculate_average(void);
void update_led_status(uint32_t time);
void button_callback(uint gpio, uint32_t events);
void update_display(void);

// Inicializa o PWM para LED RGB
void init_pwm(uint gpio)
{
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(gpio);
    pwm_set_wrap(slice, PWM_WRAP);
    pwm_set_enabled(slice, true);
}

// Definir cor LED RGB usando PWM
void set_led_color(float red, float green, float blue)
{
    pwm_set_gpio_level(LED_RED, (uint16_t)(red * PWM_WRAP));
    pwm_set_gpio_level(LED_GREEN, (uint16_t)(green * PWM_WRAP));
    pwm_set_gpio_level(LED_BLUE, (uint16_t)(blue * PWM_WRAP));
}

// Atualizar o display com informações atuais
void update_display(void)
{
    char buf[32];
    ssd1306_fill(&display, false);

    // Título do display
    ssd1306_draw_string(&display, "Production Timer", 10, 0);

    // Exibir estado atual
    const char *state_str = system_paused ? "PAUSED" : (current_state == STATE_MEASURING ? "MEASURING" : "READY");
    ssd1306_draw_string(&display, state_str, 10, 16);

    // Exibir medição atual se estiver medindo
    if (current_state == STATE_MEASURING && !system_paused)
    {
        uint32_t current_time = to_ms_since_boot(get_absolute_time()) - measurement_start;
        snprintf(buf, sizeof(buf), "Time: %lu ms", current_time);
        ssd1306_draw_string(&display, buf, 10, 32);
    }

    // Exibir contagem de medições e média
    snprintf(buf, sizeof(buf), "Count: %d/10", measurement_count);
    ssd1306_draw_string(&display, buf, 10, 48);

    if (current_average > 0)
    {
        snprintf(buf, sizeof(buf), "Avg: %.1f ms", current_average);
        ssd1306_draw_string(&display, buf, 10, 56);
    }

    ssd1306_send_data(&display);
}

// Inicializa o hardware
void init_hardware(void)
{
    stdio_init_all();

    // Inicializa o I2C para display OLED
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicializa o display
    ssd1306_init(&display, 128, 64, false, DISPLAY_ADDR, I2C_PORT);
    ssd1306_config(&display);
    ssd1306_fill(&display, false);
    ssd1306_send_data(&display);

    // Inicializa os buttões
    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);

    // Inicializa o PWM for RGB LED
    init_pwm(LED_RED);
    init_pwm(LED_GREEN);
    init_pwm(LED_BLUE);
}

int main()
{
    init_hardware();

    // Atualização inicial do display
    update_display();

    while (true)
    {
        if (current_state == STATE_MEASURING && !system_paused)
        {
            update_display();
        }
        sleep_ms(100);
    }
    return 0;
}
