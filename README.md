# 🚦 Projeto: Temporizadores com Raspberry Pi Pico W

Este repositório contém duas atividades práticas utilizando temporizadores na Raspberry Pi Pico W, simuladas no Wokwi e na ferramenta educacional BitDogLab.

## 📌 Atividade 1: Temporizador Periódico (Semáforo)

### 📝 Como Funciona
O código implementa um semáforo utilizando a função `add_repeating_timer_ms()` do Pico SDK. O temporizador alterna os LEDs a cada 3 segundos, seguindo a sequência:
1. **LED Vermelho aceso** → **LED Amarelo acende, LED Vermelho apaga**.
2. **LED Amarelo aceso** → **LED Verde acende, LED Amarelo apaga**.
3. **LED Verde aceso** → **LED Vermelho acende, LED Verde apaga**.

Além disso, um segundo temporizador imprime a mensagem "Semáforo ativo" no monitor serial a cada 1 segundo.

O código principal configura os GPIOs dos LEDs e inicializa os temporizadores. O loop `while(1)` não executa nenhuma lógica direta, pois o funcionamento ocorre dentro dos callbacks dos temporizadores.

---

## 🕹️ Atividade 2: Temporizador de Um Disparo (One-Shot)

### 📝 Como Funciona
O código implementa um sistema de acionamento de LEDs ao pressionar um botão, utilizando `add_alarm_in_ms()`. O funcionamento ocorre da seguinte maneira:
1. Ao pressionar o botão, todos os LEDs (azul, vermelho e verde) acendem simultaneamente.
2. A cada 3 segundos, um LED é desligado na seguinte sequência:
   - O LED azul apaga primeiro.
   - O LED vermelho apaga em seguida.
   - O LED verde apaga por último.
3. Após o desligamento do último LED, o sistema fica pronto para receber um novo acionamento do botão.

O botão é configurado para gerar uma interrupção quando pressionado. Se o ciclo já estiver em andamento, novos pressionamentos não têm efeito. Quando todos os LEDs são desligados, o ciclo pode ser reiniciado ao pressionar o botão novamente.

O código principal configura os GPIOs dos LEDs e do botão, além de definir a interrupção do botão para ativar a sequência de temporização.

---

## 🚀 Como Executar no Wokwi
1. Clone este repositório.
2. Abra o projeto no [Wokwi](https://wokwi.com/).
3. Configure os GPIOs conforme especificado.
4. Compile e execute o código para testar o comportamento dos LEDs e do botão.

## 🛠️ Como Executar na BitDogLab
1. Conecte a Raspberry Pi Pico W à BitDogLab.
2. Compile o código utilizando o SDK da Pico.
3. Faça o upload para a placa.
4. Teste o funcionamento com os LEDs e botões conectados.

---

## 📜 Licença
Este projeto é de uso educacional e está disponível sob a licença MIT.

## ✨ Créditos
Desenvolvido como parte de atividades práticas para o estudo de temporizadores na Raspberry Pi Pico W.
