## 🔥 Projeto: Timer de produção para monitoramento de eficiência

## 📌 Descrição do Projeto

Este projeto visa desenvolver um temporizador de produção para monitorar o tempo gasto na fabricação de peças por funcionários. O sistema mede os tempos de produção, calcula uma média após 10 medições e fornece feedback visual com LEDs para indicar desempenho.

## Objetivos

- Medir o tempo gasto por cada funcionário na fabricação de uma peça.
- Calcular uma média de produção baseada nas últimas 10 medições.
- Fornecer feedback visual através de LEDs RGB para indicar se o tempo está abaixo, dentro ou acima da média.
- Permitir pausar e retomar a medição com um botão dedicado.

## 🛠️ Componentes Utilizados

- **LED RGB**: Conectado às GPIOs 11 (Verde), 12 (Azul) e 13 (Vermelho).
- **Botão A**: Conectado à GPIO 5.
- **Botão B**: Conectado à GPIO 6.
- **Display SSD1306**: Conectado via I2C (GPIO 14 e GPIO 15).

## 📋 Funcionalidades do Projeto

### 1. Iniciar Contagem de Tempo:

- O usuário pressiona o botão A para iniciar a medição do tempo.

### 2. Pausar/Retomar Contagem:

- O usuário pressiona o botão B para pausar ou retomar a contagem do tempo.

### 3. Interromper e Armazenar Medição:

- Ao pressionar o botão A novamente, a contagem é interrompida e o tempo medido é armazenado.

### 4. Cálculo da Média:

- Após 10 medições, o sistema calcula a média dos tempos armazenados.

### 5. Indicação Visual de Desempenho:

- O LED RGB indica o desempenho com base na média calculada:
  - Verde: Tempo abaixo da média (melhor desempenho).
  - Azul: Tempo dentro da média (desempenho médio).
  - Vermelho: Tempo acima da média (pior desempenho).

### 6. Exibição de Informações no Display:

- O display OLED exibe o estado atual do sistema, como o tempo medido, a média e o status da medição.

## 🛠️ Configurando o Projeto no VS Code

1. **Clonar o Repositório**:
```
git clone https://github.com/deciofrancis/EmbarcatechFinalProject.git
cd EmbarcatechFinalProject
```

2. **Pra o primeiro projeto - Abra o VS Code** e **importe o projeto**:
   - Vá até a **Extensão Raspberry Pi Pico**.
   - Selecione **Import Project**.
   - Escolha a pasta do repositório clonado.
   - Clique em **Import**.

3. **Compilar o código**:
   - Utilize a opção de **Build** da extensão.

4. **Rodar no BitDogLab**:
   - Na extensão do VSCode Raspberry PI PICO Project.
   - Clique em **Run Project(USB)** para enviar o arquivo para a BitDogLab.

## Desenvolvedor

[Décio Francis](https://www.linkedin.com/in/deciofrancis/)

## Vídeo de Demonstração

[Assista ao vídeo de demonstração aqui](https://youtu.be/YygEb_MbLJI)