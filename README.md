# Sistema de Monitoramento de Clima Regional

**Disciplina**: Fundamentos de Sistemas Embarcados (UnB) - Professor Renato Coral.<br>
**Tópicos**: esp32, gpio, wifi, http, rest api, weather tracker.<br>

## Sobre o Projeto 03

O trabalho tem por objetivo a criação de um **sistema de monitoramento de clima regional**. O sistema utiliza o serviço de identificação de localização baseado em endereço IP da plataforma [ipstack](https://ipstack.com/) e o serviço de meteorologia da plataforma [OpenWeather](https://openweathermap.org/api) a fim de verificar, através da esp32, as condições climáticas da região.

Maiores informações e requisitos do trabalho disponíveis em:
*   [Gitlab - FSE - Projeto 3](https://gitlab.com/fse_fga/projetos/projeto-3).

## Execução do Projeto

Para executar o projeto, faça o clone do repositório e proceda com as instruções:

1. Siga o guia de instalação da esp32 na [documentação da espressif](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html);
2. Para facilitar a execução do projeto, defina no arquivo `~/.bashrc` o seguinte alias: `alias get_idf='. $HOME/esp/esp-idf/export.sh'`;
3. Externalize os recursos da esp-idf no diretório do projeto: `get_idf`;
4. **Configure as variáveis de ambiente do tópico "Instruções de Uso"**;
5. **Faça o build do projeto**: `idf.py build`;
6. **Inicialize o projeto**: `idf.py -p preencher_porta flash monitor`.

## Instruções de Uso

A aplicação utiliza serviços de duas REST APIs, [ipstack](https://ipstack.com/) e [OpenWeather](https://openweathermap.org/api). Portanto, siga os passos abaixo para realizar a configuração das chaves de acesso:

1. Na pasta do projeto, digite: `idf.py menuconfig`;
2. No menu "Configuração de rede wireless", informe:
   1. Nome da rede wifi;
   2. Senha do wifi;
   3. Número máximo de tentativas de conexão (opcional).
3. No menu "Configuração de chaves de acesso", informe:
   1. Chave de acesso ao serviço do ipstack;
   2. Chave de acesso ao serviço do openweather.

## Autor

|Matrícula | Estudante |
| -- | -- |
| 17/0024121  |  Welison Lucas Almeida Regis |

## Referências

*   [Documentação do serviço ipstack](https://ipstack.com/documentation)
*   [Documentação do serviço OpenWeather](https://openweathermap.org/api)
*   [Descrição do trabalho prático 03](https://gitlab.com/fse_fga/projetos/projeto-3)
