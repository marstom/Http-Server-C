#include "server.h"
#include "request_parser/request_parser.h"
#include "utils/file_checker.h"

volatile sig_atomic_t done = 0;

void term(int signum){
    done = 1;
}

void setBasicHeaders(char **httpContent, const char *contentType){
    char *content = *httpContent;
    // http verion and status
    char httpHeader[80] = "HTTP/1.1 200 OK\r\n";
    strcat(content, httpHeader);
    
    // cookies
    char cookie[120] = "Set-Cookie: CIASTKO=Mojeciastko;\r\n";
    strcat(content, cookie);
    
    char contentHeader[80];
    contentHeader[0] = '\0'; // memory has random data, I must clean it first
    strcat(contentHeader, "Content-type: ");
    strcat(contentHeader, contentType);
    strcat(contentHeader, "\r\n");
    strcat(content, contentHeader);

    char endOfHeaders[80] = "\r\n";
    strcat(content, endOfHeaders);
    (*httpContent) = content;   
}


size_t processRequestResponse(char **httpContent, char *rawRequestData){
    char *response = *httpContent;

    puts("process request from client\n-----------\n");
    size_t contentLength = 0;
    HeaderContent *headerContent;
    headerContent = malloc(sizeof(HeaderContent));
    initHeaderContent(&headerContent, rawRequestData);
    puts(rawRequestData);
    putchar('\n');

    headerContent->requestSplittedLine = malloc(sizeof(char*) * 500);
    // todo create function for tear down Header whole content
    getSplittedLine(headerContent, 0);

    char* filename = calloc(100, sizeof(char));
    strcat(filename, ".");
    strcat(filename, headerContent->requestSplittedLine[1]);


    puts(filename);
    puts("-----------------\n");

    //prepare response for client
    tearDownHeaderContent(&headerContent);
    //binary types
    if(isFileBinary(filename) == true){
        if(strstr(filename, "png") != NULL || strstr(filename, "ico") != NULL){
            // Image handler
            setBasicHeaders(&response, CONTENT_PNG);
            FILE *data = fopen(filename, "rb");
            if(data == NULL){
                printf("File open status: %d\n", errno);
                return 0;
            }
            fseek(data, 0, SEEK_END);
            size_t fsize = ftell(data);
            fseek(data, 0, SEEK_SET);
            char *buffer = malloc(fsize+1);
            size_t bytesRead = fread(buffer, 1, fsize, data);
            size_t responseLen = strlen(response);
            fclose(data);
            response = realloc(response, bytesRead+1024);
            for (size_t i = 0; i < bytesRead; i++){
                response[responseLen + i] = buffer[i];
            }
            buffer[fsize] = 0;
            free(buffer);
            size_t payloadLen = fsize;
            contentLength = responseLen + payloadLen;
        }
    } else { 
        if(strstr(filename, "html") != NULL){
            setBasicHeaders(&response, CONTENT_HTML);
        } else if(strstr(filename, "css") != NULL){
            setBasicHeaders(&response, CONTENT_CSS);
        } else if(strstr(filename, "js") != NULL){
            setBasicHeaders(&response, CONTENT_JAVASCRIPT);
        }
        FILE *data = fopen(filename, "r");
        if(data == NULL){
            printf("File open status: %d\n", errno);
            return 0;
        }
        char line[100];
        while (fgets(line, 100, data) != 0) {
            strcat(response, line);
        }
        fclose(data);
        contentLength = strlen(response);
    }
    free(filename);
    (*httpContent) = response;
    return contentLength;
}


void parseClientRequest(char *request){
}

void prepareClientResponse(char **response){
    char *content = *response;
    // setBasicHeaders(&content, CONTENT_HTML);
    // strcat(content, "<h1>To ja</h1>");
    (*response) = content;
}

void cleanFileContent(char **httpContent){
    *httpContent[0] = '\0';
}

/*
Cannot be in h file, don't know why
*/
void report(struct sockaddr_in *serverAddress){
    char hostBuffer[INET6_ADDRSTRLEN];
    char serviceBuffer[NI_MAXSERV]; // defined in `<netdb.h>`
    socklen_t addr_len = sizeof(*serverAddress);
    int err = getnameinfo(
        (struct sockaddr *) serverAddress,
        addr_len,
        hostBuffer,
        sizeof(hostBuffer),
        serviceBuffer,
        sizeof(serviceBuffer),
        NI_NUMERICHOST
    );
    if (err != 0) {
        printf("It's not working!!\n");
    }
    printf("\n\n\tServer listening on http://%s:%s\n", hostBuffer, serviceBuffer);
}

int main(void)
{
    signal(SIGINT ,term);

    // this is initial size, content is realloc later
    char *httpContent = calloc(8000, sizeof(char));
    size_t contentLength = 0;
    // Socket setup: creates an endpoint for communication, returns a descriptor
    // -----------------------------------------------------------------------------------------------------------------
    int serverSocket = socket(
        AF_INET,      // Domain: specifies protocol family
        SOCK_STREAM,  // Type: specifies communication semantics
        0             // Protocol: 0 because there is a single protocol for the specified family
    );

    int _ok = 1;
    if(setsockopt(serverSocket, SOL_SOCKET,SO_REUSEADDR, &_ok, sizeof(int)) == -1){
        perror("Unable set socket options.");
        exit(1);
    }

    printf("Socket number %d \n", serverSocket);

    // Construct local address structure
    // -----------------------------------------------------------------------------------------------------------------
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8001);
    serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);//inet_addr("127.0.0.1");

    // Bind socket to local address
    // -----------------------------------------------------------------------------------------------------------------
    // bind() assigns the address specified by serverAddress to the socket
    // referred to by the file descriptor serverSocket.
    if(bind(
        serverSocket,                         // file descriptor referring to a socket
        (struct sockaddr *) &serverAddress,   // Address to be assigned to the socket
        sizeof(serverAddress)                 // Size (bytes) of the address structure
    ) == -1){
        perror("Unable to bind!");
        exit(1);
    }
    // Mark socket to listen for incoming connections
    // -----------------------------------------------------------------------------------------------------------------
    int listening = listen(serverSocket, BACKLOG);
    if (listening < 0) {
        printf("Error: The server is not listening.\n");
        return 1;
    }
    report(&serverAddress);     // Custom report function
    int clientSocket;

    // Wait for a connection, create a connected socket if a connection is pending
    // -----------------------------------------------------------------------------------------------------------------
    while(!done) {
        clientSocket = accept(serverSocket, NULL, NULL);
        char requestData[REQUEST_BUFFER_SIZE];
        if(recv(clientSocket, requestData, REQUEST_BUFFER_SIZE, 0) < 0){
            puts("non response\n");
            contentLength = 0;
        }else{
            contentLength = processRequestResponse(&httpContent, requestData);
        }
        send(clientSocket, httpContent, contentLength, 0);
        memset(requestData, '\0', REQUEST_BUFFER_SIZE);
        cleanFileContent(&httpContent);
        close(clientSocket);
    }
    free(httpContent);
    close(serverSocket);
    puts("memory freed!\n");
    return 0;
}

