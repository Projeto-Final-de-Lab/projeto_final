<h1 align="center">Processamento de imagens por meio da Matriz coocorrencia estrutural</h1>


## Sumário

<!--ts-->
   * [Sobre](#sobre)
   * [Filtro da média](#Filtro_da_média)
   * [Quantização das imagens](#Quantização_das_imagens)
   * [SCM](#SCM)
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
