#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

// Tamanho do buffer utilizado para capturar os pedidos HTTP
#define REQ_BUF_SZ 50

// Setando Endereço MAC e IP para a placa Ethernet
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// Configurando o endereço IP (mudar conforme sua rede)
IPAddress ip(192, 168, 2, 120);
EthernetServer server(80); // Criar um servidor na porta 80
File webFile;              // Arquivo da página web no cartão SD
// Armazena o buffer requerido a página web
char HTTP_req[REQ_BUF_SZ] = {0};
char req_index = 0; // Índice no HTTP_req buffer

void setup()
{
    // Desativar o chip de Ethernet
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);

    Serial.begin(9600); // Adicionado para depuração

    // Inicializa o SD card
    Serial.println("Initializing SD card...");
    if (!SD.begin(4))
    {
        Serial.println("ERROR - SD card initialization failed!");
        return; // Inicialização falhou
    }
    Serial.println("SUCCESS - SD card initialized.");
    // Verifica se exite o arquivo index.htm
    if (!SD.exists("index.htm"))
    {
        Serial.println("ERROR - Can't find index.htm file!");
        return; // Não pode encontrar o arquivo especificado
    }
    Serial.println("SUCCESS - Found index.htm file.");
    // Arquivo index.htm encontrado com sucesso

    Ethernet.begin(mac, ip); // Inicializa o dispositivo Ethernet
    server.begin();          // Inicializa o servidor web
}

void loop()
{
    EthernetClient client = server.available(); // tentar obter cliente

    if (client)
    {
        boolean currentLineIsBlank = true;
        while (client.connected())
        {
            if (client.available())
            {                           // Dados do cliente disponível para leitura
                char c = client.read(); // Lê 1 byte (atributo) do cliente
                // Primeira parte do pedido HTTP em ordem HTTP_req
                /* Deixa o último elemento na matriz como 0 para terminar...
a string (REQ_BUF_SZ - 1)*/
                if (req_index < (REQ_BUF_SZ - 1))
                {
                    HTTP_req[req_index] = c; // Salva o atributo HTTP requerido
                    req_index++;
                }
                // A última linha da requisão do cliente fica em branco e ternina com \n
                // Responde para o cliente somente depois da última linha recebida
                if (c == '\n' && currentLineIsBlank)
                {
                    // Enviar um cabeçalho de resposta HTTP padrão
                    client.println("HTTP/1.1 200 OK");

                    // Restante do cabeçalho segue abaixo, dependendo se...
                    // Página web ou página XML é solicitada
                    // Pedido Ajax - Enviar arquivo XML
                    if (StrContains(HTTP_req, "ajax_inputs"))
                    {
                        // Enviar restante do cabeçalho HTTP
                        client.println("Content-Type: text/xml");
                        client.println("Connection: keep-alive");
                        client.println();

                        // Enviar arquivo XML contendo estados de entrada
                        XML_response(client);
                    }
                    else
                    { // Solicitação de página web
                        // Enviar restante do cabeçalho HTTP
                        client.println("Content-Type: text/html");
                        client.println("Connection: keep-alive");
                        client.println();
                        // Envia página web
                        // Abre o arquivo da página web
                        webFile = SD.open("index.htm");
                        if (webFile)
                        {
                            while (webFile.available())
                            {
                                client.write(webFile.read()); // Cliente recebe a página web
                            }
                            webFile.close();
                        }
                    }
                    // Exibição na porta de serial o pedido recebido de HTTP
                    Serial.print(HTTP_req);
                    // Reseta o buffer para 0
                    req_index = 0;
                    StrClear(HTTP_req, REQ_BUF_SZ);
                    break;
                }
                // Cada linha de texto recebidas do cliente termina com \ r \ n
                if (c == '\n')
                {

                    // Iniciar nova linha com a próxima leitura de caracteres
                    currentLineIsBlank = true;
                }
                else if (c != '\r')
                {
                    // Caracter recebido pelo cliente
                    currentLineIsBlank = false;
                }
            }
        }
        delay(1);      // Dá um tempo para o browser receber os dados
        client.stop(); // Fecha a conexão
    }                  // Fim do laço if (client)
}

// Envia ao arquivo XML os valores do pino analogico
void XML_response(EthernetClient cl)
{
    int analog_val;

    cl.print("");
    cl.print("");
    // Lê o pino A3
    analog_val = analogRead(3);
    cl.print("");
    cl.print(analog_val);
    cl.print("");
    cl.print("");
}

// Seta todos os elementos de str para 0 (limpa o vetor)
void StrClear(char *str, char length)
{
    for (int i = 0; i < length; i++)
    {
        str[i] = 0;
    }
}

char StrContains(char *str, char *sfind)
{
    char found = 0;
    char index = 0;
    char len;

    len = strlen(str);

    if (strlen(sfind) > len)
    {
        return 0;
    }
    while (index < len)
    {
        if (str[index] == sfind[found])
        {
            found++;
            if (strlen(sfind) == found)
            {
                return 1;
            }
        }
        else
        {
            found = 0;
        }
        index++;
    }

    return 0;
}
