---------------------------------------------------------EMBARCATECH----------------------------------------------------------------

UNIDADE 4 | CAPÍTULO 6 | Introdução às Interfaces de Comunicação Serial com RP2040 - UART, SPI e I2C
____________________________________________________________________________________________________________________________________

## Aluno (matrícula) => Joelson Santana Alves (tic370101150)

A tarefa propôs o desenvolvimento de um projeto utilizando a placa de desenvolvimento BitDogLab para explorar o uso de interfaces de comunicação serial (UART e I2C) no RP2040, incluindo manipulação de LEDs, botões e um display OLED SSD1306.

## Funcionalidades Implementadas ao Projeto

1. Modificação da Biblioteca font.h
- Adição de caracteres minúsculos à biblioteca font.h para exibição no display SSD1306.

2. Entrada de caracteres via PC
- Utilização do Serial Monitor do VS Code para digitação de caracteres.
- Exibição do caractere digitado no display SSD1306.
- Exibição de símbolos correspondentes a números (0-9) na matriz de LEDs 5x5 WS2812.

3. Interação com o Botão A
- Alterna o estado do LED RGB Verde (ligado/desligado).
- Exibição de mensagem informativa no display SSD1306.
- Envio de mensagem descritiva para o Serial Monitor.

4. Interação com o Botão B
- Alterna o estado do LED RGB Azul (ligado/desligado).
- Exibição de mensagem informativa no display SSD1306.
- Envio de mensagem descritiva para o Serial Monitor.

## Instruções

1 - Faça o download dos arquivos do projeto clonando o repositório com o comando
| git clone <link do repositório>
ou baixe o arquivo .zip seguindo as opções "CODE > Download ZIP";

2 - No VSCode, utilizando a extensão do Raspberry Pi Pico, selecione "Import Project" e clique em "Change" para selecionar a pasta do projeto extraída caso seja o .zip. Outra maneira seria entrar na pasta do projeto, clicar no botão direito do mouse e selecionar "Mostrar mais opções > Open Git Bash here" e por fim, para a abriar o projeto no VSCode digite no Git Bash o comando
| code .

3 - Após aberto no VSCode, compile o código-fonte;

4 - Para execução na prática, conecte a placa BitDogLab à porta USB do seu computador/notebook. No VSCode, selecione a opção Run no menu inferior do editor.

5- Se atente que a placa deverá está em modo BOOTSEL antes de selecionar o Run. A ativação do modo BOOTSEL pode ser feita de suas maneiras, sendo-as 
- No momento da coneção do cabo USB da placa ao notebook, simultaneamente o botão presente no Raspberry na parte de baixo pode ser pressionado para ativar o modo BOOTSEL;
- Pressionar esse botão citado anteriormente e simultaneamente clicar em um outro botão que fica na parte de cima da placa que tem o nome de Reset. Após o clique, ambos podem ser "soltados". 

## Requisitos

Hardware

- Microcontrolador Raspberry Pi Pico W.
- Matriz 5x5 de LEDs WS2812 (conectada à GPIO 7).
- LED RGB (conectado às GPIOs 11, 12 e 13).
- Botão A (conectado à GPIO 5).
- Botão B (conectado à GPIO 6).
- Display SSD1306 via I2C (conectado às GPIOs 14 e 15).

Software

- SDK do Raspberry Pi Pico configurado.
- Compilador C compatível (como GCC);
- Ferramentas para upload do código para o Pico (VSCode e extensões do Raspberry Pi Pico).

## Link do repositório Git Hub: https://github.com/joelson-santana22/Comunicao-Serial-RP2040-BitDogLab.git 

## Link para o vídeo desmonstrativo: https://drive.google.com/drive/folders/1zHN2uS_fAlJFTZml5L6yQcZvUDiLMHp-?usp=sharing
____________________________________________________________________________________________________________________________________
