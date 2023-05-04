#include <stdio.h>
#include <winsock2.h>


#pragma comment(lib, "ws2_32.lib") // Enlaza con la biblioteca ws2_32.lib

int main() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server;
    char message[100];
    char server_reply[200];

    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        printf("Error: no se pudo inicializar Winsock\n");
        return 1;
    }
    
    // Crear el socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Error: no se pudo crear el socket\n");
        return 1;
    }
    
    // Especificar la dirección del servidor
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Dirección IP del servidor
    server.sin_family = AF_INET; // Familia de direcciones (IPv4)
    server.sin_port = htons(8080); // Puerto del servidor
    
    // Conectar con el servidor
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Error: no se pudo conectar con el servidor\n");
        return 1;
    }
    
    printf("Conexion establecida\n");

    // Enviar datos al servidor
    printf("Ingrese el mensaje: ");
    fgets(message, 1024, stdin);
    strcat(message, "\n"); // Agregar una nueva línea al final del mensaje
    if (send(sock, message, strlen(message), 0) < 0) {
        printf("Error: no se pudo enviar el mensaje\n");
        return 1;
    }
    printf("Mensaje enviado\n");

    // Recibir datos del servidor
    if (recv(sock, server_reply, 200, 0) < 0) {
        printf("Error: no se pudo recibir la respuesta del servidor\n");
        return 1;
    }
    printf("Respuesta del servidor: %s\n", server_reply);

    // Cerrar el socket
    closesocket(sock);
    WSACleanup();
    
    return 0;
}