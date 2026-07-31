# Placa de Energia do Projeto 8810

![Imagem da PCB](/power-supply-board/power-supply-pcb.png)

## Objetivo
O objetivo da PCB (Placa de circuito impresso) de Energia que ficará dentro do módulo de eletrônica digital desenvolvido é fornecer energia estável para a PCB de cima do módulo, na qual estão localizados a lógica e os componentes que são responsáveis pelas funcionalidades do módulo, além daqueles componentes eletrônicos utilizados pelos próprios usuários.

## Modularidade
Uma das metas do módulo é ser modular, ou seja ter a capacidade de ser utilizado em qualquer lugar que possa fornecer energia, desde que a interface utilizada esteja disponível.
Para isso, decidimos utilizar uma porta USB-C para fornecer energia ao módulo, de modo que podem ser conectados carregadores (seja de notebook ou seja de celular) ou até powerbanks.
No entanto, para que isso funcione o carregador (ou powerbank) deve implementar o USB-C PD (Power Delivery Protocol), um protocolo que permite negociar a tensão estabelecida na porta USB-C, a qual é de 20 V usada nesse projeto.
Portanto, desde que o dispositivo carregador tenha suporte aos 20 V USB-C, o módulo deve funcionar normalmente.

## Por dentro da Placa de Energia
Umas das principais mudanças do módulo da Datapool 8810 © para o desenvolvido aqui na questão da energia, além da porta USB-C, é que o módulo usa conversores DC-DC buck para transformar a tensão recebida (20 V) nas tensões utilizadas (±12 V e 5 V), de modo que a eficiência energética é bem maior e o calor dissipado bem menor que o outro módulo, o qual usa reguladores de tensão lineares. O leitor que estiver interessado em saber mais sobre quais CIs foram utilizados pode buscar pelos esquemáticos disponíveis no repositório.
