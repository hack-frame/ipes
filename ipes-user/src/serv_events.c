#include "ipes_user.h"

struct Server_Data * connect_to_serv(uint8_t ip_family, uint8_t socket_type, char * ip, int port)
{
        struct Server_Data * serv;

        if (ip_family > 12)
                fast_exit("ip family is not correct");
        if (!(socket_type >= 1 && socket_type <= 5) && socket_type != 10)
                fast_exit("socket type is not correct");
        /* IP string should have separate function to check values */
        if (ip_family != AF_INET)
                fast_exit("ip is not correct");
        /* Use only these ports: 49152-65535 */
        if (port < 49152 || port > 65535)
                fast_exit("port is not correct");

        if (!(serv = (struct Server_Data *)malloc(sizeof(struct Server_Data))))
                fast_exit("malloc for serv failed");
        serv->serv_ip = ip;
        serv->serv_port = port;
        serv->msg = NULL;

        bzero(&serv->servaddr, sizeof(serv->servaddr));
        serv->servaddr.sin_family = ip_family;
        serv->servaddr.sin_port = htons(port);
        inet_pton(serv->servaddr.sin_family, serv->serv_ip, &serv->servaddr.sin_addr);

        return serv;
}

/* 
    int client_fd;
    struct sockaddr_un server_addr;

    // Create a socket
    if ((client_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connect failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
 *
 * */

struct Server_Data * connect_to_unix_serv(uint8_t ip_family, uint8_t socket_type, char * path, int port)
{
	#define SOCKET_PATH "/tmp/unix_socket_example"
	#define MESSAGE "Hello from client!"

    int client_fd;
    struct sockaddr_un server_addr;

    // Create a socket
    if ((client_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connect failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Send a message to the server
    if (write(client_fd, MESSAGE, strlen(MESSAGE)) == -1) {
        perror("Write failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Message sent to server: %s\n", MESSAGE);

    // Clean up
    close(client_fd);

    return 0;

}

bool send_to_serv(struct Server_Data * serv, struct Ipes_msg * msg)
{
   if((connect(serv->sock_fd, (struct sockaddr *)&serv->servaddr, sizeof(serv->servaddr)) == -1))
    {
        fprintf(stderr, "failed connect to server\n");
        return false;
    }

    printf("input val:\n");
    scanf("%s", serv->buff);
    send(serv->sock_fd, serv->buff, strlen(serv->buff), 0);
    bzero(&serv->buff, BUFF_SIZE);
    recv(serv->sock_fd, serv->buff, BUFF_SIZE -1, 0);
    printf("got: %s", serv->buff);
    close(serv->sock_fd);

    return true;
}

