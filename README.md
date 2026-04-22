# embeddingProjects

STM32F10x learning projects based on Keil MDK.

This repository currently contains two small embedded demos built around an OLED display:

- `experiments`: a rotary encoder counter demo that shows the current count on the OLED.
- `WaterfallScreen`: a simple scrolling-text demo that animates Chinese characters across the OLED.

## Project Structure

```text
embeddingProjects/
|- experiments/
|  |- Hardware/
|  |- Library/
|  |- Start/
|  `- User/
`- WaterfallScreen/
   |- Hardware/
   |- Library/
   |- Start/
   `- User/
```

Both projects follow a typical STM32 Standard Peripheral Library layout:

- `Start/`: startup files, system initialization, and core headers
- `Library/`: STM32F10x peripheral library sources
- `Hardware/`: device drivers such as the OLED module
- `User/`: application entry and user logic

## Demos

### experiments

The `experiments` project initializes an OLED and a rotary encoder connected to `GPIOB Pin 0` and `GPIOB Pin 1`. It updates the displayed encoder count whenever the interrupt-driven value changes.

Main file:

- `experiments/User/main.c`

### WaterfallScreen

The `WaterfallScreen` project shows a horizontal scrolling text effect on the OLED by repeatedly redrawing a short set of Chinese characters with a changing X offset.

Main file:

- `WaterfallScreen/User/main.c`

## Development Environment

- MCU family: STM32F10x
- IDE: Keil MDK
- Language: C
- Display: OLED

Project files:

- `experiments/ppp.uvprojx`
- `WaterfallScreen/ppp.uvprojx`

## Notes

- Build output folders such as `Objects/` and `Listings/` are ignored in version control.
- User-specific IDE files are also ignored where appropriate.

