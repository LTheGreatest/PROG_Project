PROJETO PROG

//*
Este projeto é uma componente da UC de programação da LEIC. Neste trabalho serão implementadas algumas funções que manipulam imagens no formato PNG
e outras funções para o formato XMP2.
Espera-se que os elementos que participam neste trabalho não façam o obséquio de javardar na sua execução!!!
*//
  
SABER EXPLICAR BEM CODIGO TODO!!!

!--> Fazer um recap de todo o código para comentar tudo direitinho (se for preciso), ver se está tudo claro e percebido e tentar melhorar:
- Por codigo consistente/coerente (i.e variaveis), mais legível (variáveis explicitas) e comentar bem
- Tentar por tudo mais eficiente ???
- Ter especial atenção ao código mais ineficiente (median_filter)

TO-DO LIST: TUDO FEITO
- Color.hpp -> feito e testado
- Color.cpp -> feito e testado
- Image.hpp -> feito e testado
- Image.cpp -> feito e testado
- Script.hpp -> feito e testado
- Script.cpp -> tudo feito e testado
- Advanced functionality commands:
  - median_filter -> feito e testado (muito pesado, necessita otimização quando estiver tudo concluido), melhorar variáveis
  - xpm2_open -> feito e testado
  - xpm2_save -> feito e testado 
  - XPM2.cpp -> feito

ERROS: 

	
***Erro***
Script.cpp:352:10: error: no declaration matches ‘void prog::Script::xpm2_save(const string&)’
  352 |     void Script::xpm2_save(const string& filename){
      |          ^~~~~~
In file included from Script.cpp:8:
Script.hpp:31:12: note: candidate is: ‘void prog::Script::xpm2_save()’
   31 |       void xpm2_save();
      |            ^~~~~~~~~
Script.hpp:10:9: note: ‘class prog::Script’ defined here
   10 |   class Script{
      |         ^~~~~~
XPM2.cpp: In function ‘std::string prog::colortohexa(const prog::Color&)’:
XPM2.cpp:49:17: error: ‘setfill’ was not declared in this scope
   49 |         out1 << setfill('0') << setw(2) << hex << red;
      |                 ^~~~~~~
XPM2.cpp:49:33: error: ‘setw’ was not declared in this scope; did you mean ‘getw’?
   49 |         out1 << setfill('0') << setw(2) << hex << red;
      |                                 ^~~~
      |                                 getw
make: *** [Makefile:40: runscript] Error 1




SUBMISSION INFORMATION
======================

Group identifier: 15.02

Summary of implemented features:
- Color.hpp -> everything implemented
- Color.cpp -> everything implemented
- Image.hpp -> everything implemented
- Image.cpp -> everything implemented
- Script.hpp -> everything implemented
- Script.cpp -> all commands implemented
- Advanced functionality commands:
- median_filter -> implemented in Script
- xpm2_open -> implemented in XPM2.hpp/cpp and Script
- xpm2_save -> implemented in XPM2.hpp/cpp and Script
