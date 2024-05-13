# ASCII Art Converter

Este é um simples programa em C que converte imagens para ASCII art.

## Funcionamento

Depois de baixar os arquivos, siga estas etapas para usar o programa:

1. **Compilação**: No terminal, utilize o comando `make` para compilar o programa.

2. **Execução**: Use o seguinte comando para executar o programa:

````
./ascii caminho_da_imagem
````

Onde `caminho_da_imagem` é o caminho para a imagem que você deseja converter.

## Exemplos

O projeto já vem com uma pasta chamada `imagens`, que contém algumas imagens de exemplo para você testar o programa.

Além disso, após a conversão, as ASCII arts geradas serão salvas na pasta `ascii-arts`.

## Biblioteca STB

O projeto utiliza a biblioteca [stb_image](https://github.com/nothings/stb) para carregar e redimensionar as imagens. Os arquivos headers necessários estão incluídos na pasta `stb`.

