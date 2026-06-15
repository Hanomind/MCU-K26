/*******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "soc/gpio_reg.h"
#include "soc/gpio_periph.h"
#include "soc/io_mux_reg.h"
#include "soc/soc.h"

/*******************************************************************************
* Definitions
*******************************************************************************/
#define LED_GPIO                    (4U)
#define TTP224_GPIO                 (5U)

#define GPIO_LOW_LEVEL              (0U)
#define GPIO_HIGH_LEVEL             (1U)

#define TTP224_ACTIVE_HIGH          (1U)
#define MAIN_LOOP_DELAY_MS          (10U)

/*******************************************************************************
* Prototypes
*******************************************************************************/
static void GPIO_SelectGpioFunction(uint32_t gpioNumber);
static void LED_InitRegister(void);
static void LED_SetOnRegister(void);
static void LED_SetOffRegister(void);
static void TTP224_InitRegister(void);
static uint32_t TTP224_ReadLevelRegister(void);
static uint32_t TTP224_IsTouched(void);

/*******************************************************************************
* Variables
******************************************************************************/

/*******************************************************************************
* Code
*******************************************************************************/
static void GPIO_SelectGpioFunction(uint32_t gpioNumber)
{
    /* Select normal GPIO function for the selected pin. */
    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[gpioNumber], PIN_FUNC_GPIO);
}

static void LED_InitRegister(void)
{
    /* Select GPIO function for LED pin. */
    GPIO_SelectGpioFunction(LED_GPIO);

    /* Configure LED GPIO as output. */
    REG_WRITE(GPIO_ENABLE_W1TS_REG, (1UL << LED_GPIO));

    /* Turn LED off at startup. */
    REG_WRITE(GPIO_OUT_W1TC_REG, (1UL << LED_GPIO));
}

static void LED_SetOnRegister(void)
{
    /* Set LED GPIO output level to high. */
    REG_WRITE(GPIO_OUT_W1TS_REG, (1UL << LED_GPIO));
}

static void LED_SetOffRegister(void)
{
    /* Set LED GPIO output level to low. */
    REG_WRITE(GPIO_OUT_W1TC_REG, (1UL << LED_GPIO));
}

static void TTP224_InitRegister(void)
{
    /* Select GPIO function for TTP224 input pin. */
    GPIO_SelectGpioFunction(TTP224_GPIO);

    /* Enable input path for TTP224 GPIO pin. */
    REG_SET_BIT(GPIO_PIN_MUX_REG[TTP224_GPIO], FUN_IE);

    /* Disable internal pull-up for TTP224 GPIO pin. */
    REG_CLR_BIT(GPIO_PIN_MUX_REG[TTP224_GPIO], FUN_PU);

    /* Disable internal pull-down for TTP224 GPIO pin. */
    REG_CLR_BIT(GPIO_PIN_MUX_REG[TTP224_GPIO], FUN_PD);

    /* Configure TTP224 GPIO as input by clearing output enable bit. */
    REG_WRITE(GPIO_ENABLE_W1TC_REG, (1UL << TTP224_GPIO));
}

static uint32_t TTP224_ReadLevelRegister(void)
{
    uint32_t gpioInputValue = 0U;
    uint32_t ttp224Level = GPIO_LOW_LEVEL;

    /* Read GPIO input register value. */
    gpioInputValue = REG_READ(GPIO_IN_REG);

    /* Extract TTP224 GPIO input level. */
    ttp224Level = ((gpioInputValue >> TTP224_GPIO) & 0x1UL);

    return ttp224Level;
}

static uint32_t TTP224_IsTouched(void)
{
    uint32_t ttp224Level = GPIO_LOW_LEVEL;
    uint32_t isTouched = 0U;

    /* Read TTP224 output level. */
    ttp224Level = TTP224_ReadLevelRegister();

#if TTP224_ACTIVE_HIGH
    if (ttp224Level == GPIO_HIGH_LEVEL)
    {
        isTouched = 1U;
    }
    else
    {
        isTouched = 0U;
    }
#else
    if (ttp224Level == GPIO_LOW_LEVEL)
    {
        isTouched = 1U;
    }
    else
    {
        isTouched = 0U;
    }
#endif /* TTP224_ACTIVE_HIGH */

    return isTouched;
}

void app_main(void)
{
    uint32_t isTouched = 0U;

    /* Initialize LED output and TTP224 input. */
    LED_InitRegister();
    TTP224_InitRegister();

    while (1)
    {
        /* Read TTP224 touch state continuously. */
        isTouched = TTP224_IsTouched();

        if (isTouched != 0U)
        {
            LED_SetOnRegister();
        }
        else
        {
            LED_SetOffRegister();
        }

        vTaskDelay(pdMS_TO_TICKS(MAIN_LOOP_DELAY_MS));
    }
}