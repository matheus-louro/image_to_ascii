#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "stb/stb_image.h"
#include "stb/stb_image_resize.h"

// Estrutura de uma imagem
typedef struct img
{
    unsigned char *data;
    int width, height, channels;
} IMAGE;

// Headers das funções
IMAGE grayscale(IMAGE img);
void output_filename(char *filename, char *output);
void convert_to_ascii(unsigned char *img_data, FILE *file, int height, int width, int channels);

int main(int argc, char *argv[])
{
    // Verifica se o usuário forneceu uma imagem
    if (argc == 1)
    {
        printf("Voce precisa fornecer uma imagem\n");
        printf("use o comando: ./ascii 'caminho da imagem'\n");
        return -1;
    }

    // Carrega a imagem na memória
    IMAGE img;
    img.data = stbi_load(argv[1], &img.width, &img.height, &img.channels, 0);
    int new_width = img.width;
    int new_height = img.height;
    int new_channels = img.channels;

    if (!img.data)
    {
        printf("nao foi possivel carregar a imagem\n");
        return -1;
    }

    // Redimensiona a imagem
    if (img.width > 500 && img.height > 450)
    {
        new_width = 500;
        new_height = 450;
        new_channels = img.channels;
        stbir_resize_uint8(img.data, img.width, img.height, 0, img.data, new_width, new_height, 0, new_channels);
    }

    // Aplica filtro preto e branco
    img = grayscale(img);

    // Gera o nome do arquivo.txt e cria o arquivo que será armazenado a ASCII-ART
    char out[100];
    char path_output[100] = "ascii-arts/";
    output_filename(argv[1], out);
    strcat(path_output, out);

    FILE *file = fopen(path_output, "w");
    if (file == NULL)
    {
        printf("Erro ao gerar arquivo txt\n");
        return -1;
    }

    // Converte os pixels em caracteres e imprime no arquivo.txt
    convert_to_ascii(img.data, file, new_height, new_width, new_channels);

    stbi_image_free(img.data);
    fclose(file);
    return 0;
}

IMAGE grayscale(IMAGE img)
{
    for (unsigned char *p = img.data; p != img.data + img.height * img.width * img.channels; p += img.channels)
    {
        int average = ((*p) + (*(p + 1)) + (*(p + 3))) / 3;
        *p = (uint8_t)average;
        *(p + 1) = (uint8_t)average;
        *(p + 2) = (uint8_t)average;
    }

    return img;
}

void output_filename(char *filename, char *output)
{
    char *last_slash = strrchr(filename, '/');
    if (last_slash != NULL)
    {
        filename = last_slash + 1;
    }

    char *dot = strrchr(filename, '.');
    if (dot != NULL)
    {
        strncpy(output, filename, dot - filename);
        output[dot - filename] = '\0';
    }
    else
    {
        strcpy(output, filename);
    }

    strcat(output, ".txt");
}

void convert_to_ascii(unsigned char *img_data, FILE *file, int height, int width, int channels)
{
    char chars[] = "@%#*+=-:. ";
    int charsLen = strlen(chars);

    for (int i = 0; i < height * width * channels; i += channels)
    {
        int intesity = img_data[i];

        int index = intesity * charsLen / 256;

        fputc(chars[index], file);

        if ((i / channels) % width == width - 1)
            fputc('\n', file);
    }
}
