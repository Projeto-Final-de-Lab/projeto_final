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

## Filtro da média
