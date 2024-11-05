#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

char *find(char *h, size_t h_len, const char *n, size_t n_len) {
    if (!h || !n || h_len < n_len) return NULL;
    if (n_len == 0) return h;
    for (size_t i = 0; i <= h_len - n_len; i++) {
        if (memcmp(h + i, n, n_len) == 0) return (h + i);
    }
    return NULL;
}

void replace_urls(const char *pdf, const char *old_url, const char *new_url) {
    FILE *file = fopen(pdf, "r+b");
    if (!file) {
        perror("Error opening file");
        return;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    char *old_buffer = (char *)malloc(file_size);
    if (!old_buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }
    fread(old_buffer, 1, file_size, file);
    rewind(file);
    char *new_buffer = (char *)malloc((long)file_size * 2);
    if (!new_buffer) {
        perror("Memory allocation failed");
        free(old_buffer);
        fclose(file);
        return;
    }
    char *old_pos = old_buffer;
    char *new_pos = new_buffer;
    char *old_end = old_buffer + file_size;
    char *pos;
    size_t old_url_len = strlen(old_url);
    size_t new_url_len = strlen(new_url);
    size_t copy_size;
    while ((pos = find(old_pos, old_end - old_pos, old_url, old_url_len)) != NULL) {
        copy_size = pos - old_pos;
        memcpy(new_pos, old_pos, copy_size);
        old_pos = pos + old_url_len;
        new_pos += copy_size;
        memcpy(new_pos, new_url, new_url_len);
        new_pos += new_url_len;
    }
    copy_size = old_end - old_pos;
    memcpy(new_pos, old_pos, copy_size);
    new_pos += copy_size;
    free(old_buffer);
    fwrite(new_buffer, 1, new_pos - new_buffer, file);
    free(new_buffer);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Missing old URL argument\n");
        return 1;
    }
    const char *old_url = argv[1];
    if (strncmp(old_url, "http", 4) != 0) {
        fprintf(stderr, "Error: old URL must begin with \"http\"\n");
        return 1;
    }
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        for (char *p = cwd; *p != '\0'; ++p) { if (*p == '\\') { *p = '/'; } }
    } else {
        perror("getcwd() error");
        return 1;
    }
    struct dirent *entry;
    DIR *dp = opendir(".");
    if (dp == NULL) {
     perror("opendir() error");
     return 1;
    }
    char new_url[2048];
    snprintf(new_url, sizeof(new_url), "file:///%s", cwd);
    while ((entry = readdir(dp))) {
        if (strstr(entry->d_name, ".pdf") != NULL) {
            printf("Processing %s\n", entry->d_name);
            replace_urls(entry->d_name, old_url, new_url);
        }
    }
    closedir(dp);
    return 0;
}
