# Trabalho Prático: Análise Experimental de Algoritmos de Ordenação e Busca

Trabalho realizado pelas alunas <b>Beatriz Caroline Moggio</b> e <b>Isabela Camille Barotto Janguas</b>, para a disciplina de <b>Algoritmos e Estrutura de Dados I</b>.

## Sobre o trabalho
O trabalho consiste na implementação e análise de algoritmos de ordenação e busca em arquivos binários. Com o objetivo de compreender a relação entre a complexidade teórica e o seu comportamento real em diversos cenários.

## Instruções de execução dos códigos
Para realizar a execução dos arquivos é necessário criar, caso ela ainda não exista, uma pasta chamada "dados" no diretório principal do projeto. Em seguida, compile cada um dos arquivos utilizando um compilador C++, gerando assim três executáveis: um para o gerador de dados, 
outro para os algoritmos de ordenação e outro para as buscas.

### Ordem de execução:
Após a compilação execute cada um dos arquivos na seguinte ordem:

1 - gerador de dados;

2 - Ordenação;

3 - Busca.

## Explicação dos códigos

### `gerador_dados.cpp`
Este código tem o papel de gerar, na pasta `/dados/`, 9 arquivos binários com valores inteiros, combinando três tamanhos (pequeno, médio, grande) e três cenários (aleatório, crescente, descrescente).
Para a sua implementação foram utilizadas as seguintes funções:
<ul>
  <li><b>main(): </b> É responsável por criar os vetores que possuem os tamanhos que cada arquivo terá e os seus respectivos cenários. Em seguida é feito uma padronização do nome dos arquivos que serão gerados e é chamada a função `gerarArquivo()`;</li>
  
  <li><b>gerarArquivo(const string nomeArquivo, int N, const string cenario): </b> Esta função é responsável por gerar os números inteiros aleatórios, de acordo com a quantidade passada pela variável `N`. Em seguida ele verifica se o cenário que está sendo criado
  é crescente ou decrescente, ordenando caso haja a necessidade. Ao final do código ele pega o vetor `dados` que possui os valores gerados e os escreve em um arquivo binário, deletando o vetor ao final.</li>
</ul>


### `ordenacao.cpp`
Este código tem o papel de realizar testes nos arquivos gerados, utilizando quatro tipos de algoritmos de ordenação diferentes: Selection Sort, Insertion Sort, Bubble Sort padrão e Bubble Sort otimizado.
Para a sua implementação foram utilizadas as seguintes funções:
<ul>
  <li><b>main(): </b>Dentro da função principal temos a declaração de uma lista com todos os nomes dos arquivos gerados e um vetor com os nomes e funções de cada algoritmo de ordenação. A função main utiliza um laço de repetição para passar
por todos os arquivos criados, chamando a função `executarTeste`;</li>
  
  <li><b>lerBinario(const string nomeArquivo): </b> Esta função é responsável por receber o nome de um arquivo, acessá-lo e realizar a leitura do seu conteúdo, armazenado todos os valores obtidos dentro de um vetor;</li>
 
  <li><b> executarTeste(const string nomeArquivo, void (*algoritmo)(vector<int>&, Metricas&), const string nomeAlgoritmo): </b>Nesta função é feito a chamada da função lerBinario explicada acima, passando o nome do arquivo desejado. Logo em seguida é iniciado um cronômetro
  marcando o início da execução de algum algoritmo de ordenação. Em seguida, é marcado o momento que este algoritmo termina a sua execução, obtendo assim o tempo que ele levou para executar a ordenação. Ao final é realizada a apresentação de todos os valores obtidos ao executar o algoritmo em um arquivo específico;</li>
  <li><b>Algoritmos de ordenação: </b> 
    
  - Selection Sort: Realiza uma busca pelo menor valor na parte não ordenada da lista e o coloca na posição correta.
  - Insertion Sort: Ele começa no segundo elemento e o compara com os anteriores, deslocando os elementos maiores para a direita até encontrar a posição correta para inseri-lo.
Esse processo é repetido para todos os elementos, construindo uma lista ordenada à esquerda.
  - Bubble Sort padrão: Ele percorre o vetor repetidamente comparando pares de elementos adjacentes. Se estiverem fora de ordem, troca-os. A cada passada, o maior valor é deslocado para o final do vetor. Isso se repete até ordenar toda a lista.
  - Bubble Sort otimizado: Ele segue a mesma lógica do padrão, mas utiliza um flag para verificar se houve pelo menos uma troca na passada. Se nenhuma troca ocorrer, significa que o vetor já está ordenado, então o algoritmo termina mais cedo.
</li>
</ul>


### `busca.cpp`
Este código tem o papel de realizar testes de busca no arquivo grande e aleatório gerado, utilizando dois tipos de buscas diferentes: A busca sequencial e a binária.
Para a sua implementação foram utilizadas as seguintes funções:
<ul>
  <li><b>main(): </b> A função principal é responsável por chamar a função `lerBinario()`, igual a descrita no código acima, e armazenar os valores em um vetor. Logo em seguida é realizada a ordenação deste vetor em
  outra variável para realizar os testes de busca binária. São criadas duas variáveis inteiras que recebem um valor existente e outro inexistente neste vetor e logo em seguida é iniciada as buscas.
  Para a busca sequencial é utilizado o vetor desordenado, verificando o tempo de busca e a quantidade de comparações para os valores existentes e inexistentes. Para a busca binária é feita o mesmo teste, porém utilizando
  o vetor ordenado.</li>
 
  <li><b>Algoritmos de busca</b>
    
  - Busca sequencial: percorre todos os elementos da lista até que o elemento procurado seja encontrado.
  - Busca binária: Utiliza o tamanho da lista e o seu meio para definir se a busca será realizada do final à metade ou do início à metade.
  </li>
</ul>
