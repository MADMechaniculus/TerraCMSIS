#include <main.h>

/**
 * @brief Установка режима чтения с шины данных
 * 
 */
void bus_read_mode(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /*Configure GPIO pins : LCD_RS_Pin LCD_RW_Pin LCD_D7_Pin */
    GPIO_InitStruct.Pin = LCD_D7_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : LCD_D0_Pin LCD_D1_Pin LCD_D2_Pin LCD_D3_Pin
                           LCD_D6_Pin */
    GPIO_InitStruct.Pin = LCD_D0_Pin | LCD_D1_Pin | LCD_D2_Pin | LCD_D3_Pin | LCD_D6_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /*Configure GPIO pins : LCD_D4_Pin LCD_D5_Pin */
    GPIO_InitStruct.Pin = LCD_D4_Pin | LCD_D5_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/**
 * @brief Установка режима записи для шины данных
 * 
 */
void bus_write_mode(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /*Configure GPIO pins : LCD_RS_Pin LCD_RW_Pin LCD_D7_Pin */
    GPIO_InitStruct.Pin = LCD_D7_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : LCD_D0_Pin LCD_D1_Pin LCD_D2_Pin LCD_D3_Pin
                           LCD_D6_Pin */
    GPIO_InitStruct.Pin = LCD_D0_Pin | LCD_D1_Pin | LCD_D2_Pin | LCD_D3_Pin | LCD_D6_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /*Configure GPIO pins : LCD_D4_Pin LCD_D5_Pin */
    GPIO_InitStruct.Pin = LCD_D4_Pin | LCD_D5_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void send_cmd(char cmd_char)
{
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET);

    int i = 0;
    int set = 0;
    for (i = 0; i < 8; i++)
    {
        if ((cmd_char | 0x80) == 0x80)
        {
            set = 1;
        }

        switch (i)
        {
        case 0:
            HAL_GPIO_WritePin(LCD_D0_GPIO_Port, LCD_D0_Pin, set);
            break;
        case 1:
            HAL_GPIO_WritePin(LCD_D1_GPIO_Port, LCD_D1_Pin, set);
            break;
        case 2:
            HAL_GPIO_WritePin(LCD_D2_GPIO_Port, LCD_D2_Pin, set);
            break;
        case 3:
            HAL_GPIO_WritePin(LCD_D3_GPIO_Port, LCD_D3_Pin, set);
            break;
        case 4:
            HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, set);
            break;
        case 5:
            HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, set);
            break;
        case 6:
            HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, set);
            break;
        case 7:
            HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, set);
            break;

        default:
            break;
        }

        set = 0;
    }

    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET);
}

/**
 * @brief Стартовая процедура (отпрака инициирующей последовательности)
 * 
 */
void init_sequence(void) {
    send_cmd(0b00110000);       // CLS
    HAL_Delay(5);
    send_cmd(0b00110000);       // RET
    HAL_Delay(5);
    send_cmd(0b00110000);       // Install 8Bit mode, 2 rows, 5x10 style
    HAL_Delay(2);
    send_cmd(0b00111100);       // Install auto-increment, shift
    HAL_Delay(2);
    send_cmd(0b00001000);       // Install auto-increment, shift
    HAL_Delay(2);
    send_cmd(0b00000111);       // Install auto-increment, shift
    HAL_Delay(2);
    send_cmd(0b00001100);       // Install auto-increment, shift
    HAL_Delay(2);
}

/**
 * @brief Отправка символа на дисплей
 * 
 * @param symbol Отправляемый символ
 */
void send_symbol(char symbol) {
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET);

    int i = 0;
    int set = 0;
    for (i = 0; i < 8; i++)
    {
        if ((symbol | 0x80) == 0x80)
        {
            set = 1;
        }

        switch (i)
        {
        case 0:
            HAL_GPIO_WritePin(LCD_D0_GPIO_Port, LCD_D0_Pin, set);
            break;
        case 1:
            HAL_GPIO_WritePin(LCD_D1_GPIO_Port, LCD_D1_Pin, set);
            break;
        case 2:
            HAL_GPIO_WritePin(LCD_D2_GPIO_Port, LCD_D2_Pin, set);
            break;
        case 3:
            HAL_GPIO_WritePin(LCD_D3_GPIO_Port, LCD_D3_Pin, set);
            break;
        case 4:
            HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, set);
            break;
        case 5:
            HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, set);
            break;
        case 6:
            HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, set);
            break;
        case 7:
            HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, set);
            break;

        default:
            break;
        }

        set = 0;
    }

    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET);
}