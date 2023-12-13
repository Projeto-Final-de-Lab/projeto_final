<h1 align="center">Processamento de imagens por meio da Matriz coocorrencia estrutural</h1>


## Sumário

<!--ts-->
   * [Sobre](#sobre)
   * [Filtro da média](#Filtro_da_média)
   * [Quantização das imagens](#Quantização_das_imagens)
   * [SCM](#SCM)
   * [Testes](#Teste_de_Imagens)
<!--te-->


## Sobre
O código segue as etapas de fazer uma suavização das imagens que estão no formato .PGM. Após isso, as seguintes imagens(suavizadas) e as imagens originais, sofrem uma quantização
para que sejam usadas e comparadas na matriz SCM. No fim, será gerado um arquivo .CSV contendo o indice para o WEKA e para cada linha desse csv contém a imagem pronta para ser usada
no algoritmo de random forest

![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/b813b2f9-264d-4fb2-9501-a2093c028732)


## Filtro da média
Foi criada uma função para ser feita a média das matrizes, explicando de uma forma mais objetiva, a imagem será "suavizada", borrando ela.
No incio da função ela cópia todos os valores para criar uma nova imagem, assegurando que a memória 
esteja devidamente alocada.

![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/45ac37cf-9a0b-4c2f-83de-9a3ba8f3c09d)

A outra parte do codigo funciona da seguinte forma:
int r = n / 2;: Calcula o raio da janela do filtro. A janela é uma região quadrada com largura e altura iguais a n. O raio é metade dessa dimensão.

sum += img->Data[(i + k) * img->width + (j + l)]; count++;: Se o pixel vizinho estiver dentro dos limites, adiciona o valor do pixel à soma e incrementa a contagem.

O -r no loop for interno serve para garantir que a janela do filtro esteja centrada no pixel atual da imagem. Vamos analisar a lógica por trás disso.

A variável r é o raio da janela do filtro, e n é o tamanho total da janela. Se a janela tem tamanho n, ela tem n linhas e n colunas. O raio, r, seria então a metade desse tamanho, ou seja, r = n / 2.

A intenção é percorrer todos os pixels dentro dessa janela. Para fazer isso, o loop interno vai de -r até r tanto em relação às linhas quanto às colunas. A escolha de iniciar em -r é para garantir que a posição central da janela seja incluída.

![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/3edae21e-859a-4961-9a06-64ba2f0cbf88)

## Quantização da Imagem

int intervalo = (img->maxval + 1) / N;: Calcula o intervalo de cada nível de quantização. O valor máximo da intensidade de cor (maxval) mais 1 é dividido pelo número de níveis (N) para determinar o intervalo.

Os próximos dois loops aninhados (for e for) percorrem cada pixel da imagem original.

int valor = img->Data[i * img->width + j];: Obtém o valor do pixel na imagem original.

int nivel = valor / intervalo;: Calcula o nível de quantização correspondente dividindo o valor do pixel pelo intervalo.

out->Data[i * out->width + j] = nivel * intervalo + intervalo / 2;: Atribui o valor médio do intervalo ao pixel correspondente na imagem quantizada. Isso é feito para evitar que todos os pixels tenham o mesmo valor, o que resultaria em uma imagem com menos variação visual. O valor médio é calculado multiplicando o nível de quantização pelo intervalo e adicionando metade do intervalo.

Em resumo, essa função quantiza os valores de intensidade de cor da imagem original para reduzir o número de níveis de intensidade para um número especificado (N). Isso pode ser útil para reduzir a complexidade da imagem e economizar espaço de armazenamento.
![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/0646a356-797c-4e22-a2e4-25a4a0a01bc7)

##  Computação da Matriz SCM

int applyscm(struct Image *img, struct Image *qtzd, int N, char *final, FILE *fptr);
Recebe como parâmetro uma variável de ponteiro para duas structs, img para receber a imagem original quantizada e qtzd a quantizada com filtro, o N níveis da SCM, uma variável ponteiro do tipo char da função encontrarNome, que recebe o nome do arquivo e determinar se vai ser epithelium(0) ou stroma(1) pelo o primeiro valor do arquivo. Também recebe a variável de ponteiro de arquivo fptr para fazer a escrita dos dados.

![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/9c86ca9a-b4bf-41fe-a0fa-939ba0daa166)


Aloca a matriz **scm usando o maloc com um tamanho de NxN para ser a matriz SCM

![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/bd1f3ea2-1533-44e8-8360-59d10c5d6674)

Faz alocação do vetor da matriz scm usando calloc que zera todo o espaço locado inicialmente para ela começar em 0

![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/7a6ac137-d9f8-4b81-a880-96562facbf4b)



Pecorre os pixel imagens usando dois laços for pelos os tamanhos da linha(height) e coluna(width). Incrementa a frequência dos pares (x, y) na matriz scm com a variável x recebendo o valor de data(pixel) na posição da linha i e coluna j da imagem original quantizada, multiplicando por (N-1)/255 para definir o intervalo entre 0 e N-1 até o valor máximo de cada pixel, fazendo essa divisão para esses valores serem transformados para a correspondência de nível da matriz scm. Da mesma forma para a variável y que é para a imagem filtrada quantizada.

![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/4a9b4d20-03a0-4dbe-943c-dbbdf951b01d)


Pecorre a matriz scm com dois laços for para imprimir no arquivo de csv os valores da linha e coluna que foram incrementados, separando por vírgulas e espaço e por fim acrescenta no csv o valor final de epithelium ou stroma

![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/2df201f6-ed5f-4305-80b4-291c41b2b2ce)



## Testes


SCM 8x8 e Fltro da media 3x3

![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/9bf8b6ee-494b-4985-8a4d-453406849da4)


SCM 8x8 e Fltro da media 5x5

![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/0396ba47-8df5-4fc1-99c6-162d6765ed50)

SCM 8x8 e Fltro da media 5x5

![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/b460fd9c-20f6-4e05-8a4c-4c75ad6b2f89)

SCM 16x16 e Fltro da media 3x3

![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/96285870-e402-488d-86e4-581b7dde02b8)

SCM 16x16 e Fltro da media 5x5

![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/0f300909-0166-4a85-834c-d3af6285940f)

SCM 16x16 e Fltro da media 7x7

![image](https://github.com/Projeto-Final-de-Lab/projeto_final/assets/109428692/22f4696d-7eee-474d-9fd9-f6e2547e9619)










