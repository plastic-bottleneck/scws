#include <microhttpd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DEFAULT_PORT 8888       // Edit this port to your likes :)
#define DEFAULT_IP "0.0.0.0"    // Also the IP address. 0.0.0.0 sets the 
                                // web server's IP address to the default IPv4 of your intranet!

#define HTML_FILE "index.html"  // index.html and style.css have to be located at the
#define CSS_FILE "style.css"    // directory of the webserver binary file.

// ANSI escape codes for colors and formatting
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define LIGHT_BLUE "\033[94m"

struct server_options {
    const char *ip;
    int port;
};

// Reading the file content for the server
char *read_file(const char *filename, size_t *filesize) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    *filesize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *content = malloc(*filesize + 1);
    if (content) {
        fread(content, 1, *filesize, file);
        content[*filesize] = '\0';
    }
    
    fclose(file);
    return content;
}

// Handler to respond to client requests...
static enum MHD_Result request_handler(void *cls, struct MHD_Connection *connection,
                                       const char *url, const char *method,
                                       const char *version, const char *upload_data,
                                       size_t *upload_data_size, void **con_cls) {
    struct MHD_Response *response;
    enum MHD_Result ret;
    char *content;
    size_t content_length;
    const char *mime;

    if (strcmp(url, "/") == 0 || strcmp(url, "/index.html") == 0) {
        content = read_file(HTML_FILE, &content_length);
        mime = "text/html";
    } else if (strcmp(url, "/style.css") == 0) {
        content = read_file(CSS_FILE, &content_length);
        mime = "text/css";
    } else {
        const char *not_found = "404 Not Found";
        response = MHD_create_response_from_buffer(strlen(not_found),
                                                   (void *)not_found,
                                                   MHD_RESPMEM_PERSISTENT);
        if (!response) {
            return MHD_NO;
        }
        ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
        MHD_destroy_response(response);
        return ret;
    }

    if (!content) {
        const char *error_msg = BOLD RED "[ERROR]" RESET " Error loading file";
        response = MHD_create_response_from_buffer(strlen(error_msg),
                                                   (void *)error_msg,
                                                   MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return ret;
    }

    response = MHD_create_response_from_buffer(content_length,
                                               (void *)content,
                                               MHD_RESPMEM_MUST_FREE);
    MHD_add_response_header(response, "Content-Type", mime);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

// Main function to start the server finally!
int main(int argc, char **argv) {
    struct server_options options = {DEFAULT_IP, DEFAULT_PORT};
    struct MHD_Daemon *daemon;
    struct sockaddr_in serv_addr;

    // Check for command-line arguments to set IP and port
    if (argc > 1) {
        options.ip = argv[1];
    }
    if (argc > 2) {
        options.port = atoi(argv[2]);
    }

    // Set up the server address structure
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(options.port);
    if (inet_pton(AF_INET, options.ip, &serv_addr.sin_addr) <= 0) {
        fprintf(stderr, BOLD RED "[ERROR]" RESET " Invalid IP address: %s\n", options.ip);
        return 1;
    }

    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, options.port, NULL, NULL,
                              &request_handler, NULL, MHD_OPTION_SOCK_ADDR, (struct sockaddr *)&serv_addr, MHD_OPTION_END);
    if (NULL == daemon) {
        fprintf(stderr, BOLD RED "[ERROR]" RESET " Failed to start server!!!\n");
        return 1;
    }

    printf(RESET BOLD "\n[" BOLD GREEN "!!" RESET BOLD "] " RESET "Yay! Server is running on " BOLD GREEN "%s" RESET ":" BOLD LIGHT_BLUE "%d" RESET "\n\n", options.ip, options.port);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}
