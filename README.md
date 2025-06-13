Participante:
• Luigi Thiengo Pires • RM 560755
• Alexandre Colvet Delfino • RM 560059
•	Enzo Luciano Barros de Oliveira • RM 559557
•	Lívia Pereira Dias Correa • RM 559414
•	Felipe Gomes Molinari Lopes • RM 559885

# Sistema de Monitoramento de Bem-Estar do Paciente

## Objetivo

Este projeto tem como objetivo desenvolver uma solução baseada em IoT para o **monitoramento contínuo do bem-estar do paciente**. A proposta é identificar, de forma automática, se o paciente encontra-se em estado estável ou em situação de possível emergência, utilizando sensores ambientais e atuadores locais para emitir alertas.

---

## Arquitetura da Solução

A arquitetura é dividida em três camadas principais:

### 1. IoT – Microcontrolador e Sensores

- **Placa Arduino**: Responsável por ler sensores e controlar os atuadores.
- **Sensor DHT11**: Mede a temperatura e umidade do ambiente.
- **LEDs e buzzer**:
  - LED verde indica que o ambiente está em condições normais.
  - LED vermelho e som do buzzer indicam situação de alerta (possível emergência).

### 2. Processamento – Node-RED

- **Node-RED**:
  - Recebe os dados da placa Arduino via porta serial.
  - Processa os dados e envia para a plataforma TagoIO via requisições HTTP.
  - Permite aplicar lógica de decisão local e integração com nuvem.

### 3. Visualização – Plataforma TagoIO

- **TagoIO**:
  - Recebe os dados do Node-RED por HTTP.
  - Exibe os valores de temperatura e umidade em tempo real.
  - Pode ser configurado para gerar gráficos, alertas e dashboards.

---

## Estrutura dos Arquivos

- `Arduino.ino`: Código para a placa Arduino com leitura do sensor e controle dos atuadores.
- `flows.json`: Fluxo Node-RED com leitura de dados via serial e envio HTTP para o TagoIO.
- `README.md`: Documento explicativo do projeto.
- `diagrama.drawio`: Diagrama da arquitetura do sistema.

---

## Funcionalidades

- Leitura contínua da temperatura e umidade ambiente.
- Avaliação simples das condições de bem-estar com base nos valores lidos.
- Sinalização local por meio de LEDs e buzzer.
- Envio de dados para o Node-RED via porta serial.
- Transmissão dos dados para o TagoIO via HTTP.
- Visualização remota dos dados por meio de dashboards.

---

## Requisitos Técnicos

- Placa Arduino com biblioteca DHT instalada.
- Arduino IDE ou PlatformIO para programação do microcontrolador.
- Node-RED instalado com suporte à porta serial e ao nó HTTP request.
- Conta gratuita no TagoIO para recebimento dos dados e configuração dos dashboards.

---

## Como Executar

1. Grave o código `Arduino.ino` na placa Arduino.
2. Conecte a placa ao computador via cabo USB.
3. Importe o arquivo `flows.json` no Node-RED.
4. Configure o token e o endpoint da API do TagoIO nos nós HTTP.
5. Execute o fluxo e observe os dados sendo enviados e exibidos no TagoIO.

---

