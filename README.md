--- Ваше ФИО: Рогов Константин


--- Номер решаемой задачи: 2


--- Описание, как решение скомпилировать / запустить:
1. Скомпилировать компилятором g++ (17ой версии плюсов)
2. Исполнить получившийся исполняемый файл

Код запуска:
g++ --std=c++17 -o plague_inc_solution
./plague_inc_solution


Также в репозитории в папке tests есть тесты, для их запуска достаточно:

g++ --std=c++17 -o plague_inc_solution
cat ./tests/test<i>.txt | ./plague_inc_solution, где <i> может быть равно 1,2 или 3



--- Описание принятых проектных решений:
Я реализовал достаточно простой алгоритм - это жадный алгоритм.
Дальше города и вершины графа - одно и то же.

Алгоритм:
1) Сначала необходимо заразить все вершины, являющиеся изолированными или листьями - те у кого только один сосед. Эти вершины сложим в отдельный список (вектор) вершин, которые надо изначально заразить.
1.2) После заражения каждого города (вершины), мы проверяем не появилось ли новых зараженных, согласно условию задачи. Достаточно проверять только соседей данной вершины, ведь только у них появился один новых зараженный город сосед, остальные не могли бы заразиться, так как у них ничего не изменилось и значит, в случае их заражения они должны были бы быть заражены ещё на предыдущих шагах. Если новые зараженные города появились, то проводим аналогичную проверку на зараженнных ещё раз, ведь могли появится новые незараженные города, удолетворяющие условию заражения. Сама проверка для отдельного города проста - я буду просто для каждой вершины держать количество зараженных и незараженных её соседей (хотя на самом деле было бы достаточно только одного из этих чисел, ведь второе число вычисляется как количество соседей минус первое число), и если это число зараженных соседей хотя бы два, то вершина стала зараженной.

2) Итеративно работаем в бесконечном цикле, пока все вершины графа не будут заражены.
	2.1) (В цикле) Ищем "лучшую" с нашей точки зрения вершину для её заражения - это будет вершина с максимальным количеством незараженных соседей. (Докозательство что это реально хорошее приближение на "лучшую" для заражения вершину будет отдельным пунктом, если я успею это написать)
	2.2) Заражаем эту "лучшую" вершину из предыдущего шага (2.1) - добавляем её в тот же список вершин, которые надо заразить из пункта 1). Смотрим появились ли в результате этого новые зараженные вершины - делаем это аналогично пункту 1.2)

3) Когда мы точно завершимся ведь, на каждой итерации пункта 2) мы заражаем хотя бы одну вершину, а так как число вершин конечно, то за это же конечное число итераций мы заразим все города (как минимум если на каждой итерации будем добавлять их в список городов, которые надо изначально заразить) 

4) Сложность алгоритма: 
N, M - число вершин и ребр соответственно

По времени:

1) Обход всех вершин для поиска изолированных вершин и листьев - это O(N)
2) Как максимум будет N итераций цикла. В каждой итерации мы проходимся по всем вершинам и ищем "лучшую" с нашей точки зрения (пункт 2.1). То есть всего на цикл потратим N * O(N) = O(N^2)
3) Итого всего по времени сложность - O(N) + O(N^2) = O(N^2)

По памяти:
1) Все численные переменные - это O(1)

2) Также я сохраняю список того, заражена ли каждый вершина, и сколько у каждой вершины зараженных и незараженных соседей соседей - это 3 * O(N) = O(N)

3) Ещё ребра я храню, как список списков, что требует O(N + M) памяти

И того требуется O(1) + O(N) + O(N + M) = O(N + M) памяти


5) Про выбор "лучшей" вершины из пункта 2.1:




--- Любая другая информация на ваше усмотрение:
Может быть это не совсем уместно писать именно здесь, но я забыл об этом написать в заявке.

Я проходил летнюю сттажировку в Яндексе на роли аналитика в команде Алисы. На стажировке я в оснвоном работал с базамы данных. Весь код, что я писал был на питоне и SQL - это были как раз запросы к базам данных, и последущая обработка данных. 

Также за стажировку я успел настроить небольшой процес потока данных - это был поток специфических оценок Алисы. Сначала мой скрипт подготавливал задания, по которым будет оцениваться Алисы. Потом происходили сами оценки Алисы, специально нанятыми на это людьми. Затем эти оценки поступали на мой другой скрипт, который обрабатывал данные. После обработки данные поступали в датасет из datalens. А уже на основе этих датасетов из datalens я строил графики и объединял их в дашборды.
