/*
   Ссылка на отчёт в контесте:
   https://contest.yandex.ru/contest/25597/run-report/115061039/

-- ПРИНЦИП РАБОТЫ --
   Задача показалась интересной, и изначально стал её решать пробуя разные методы:
1. Заметил, что мы можем только при четном числе получить положительный результат
2. Заметил, что если число четное и мы ищем две половины, то нам достаточно посичитать только одну из них.
3. В итоге, полумал подумал, и узнал задачу из спринта, по подбору монет.
4. В этом случае, нам необходимо было подобрать монетки для половины суммы, значит оставшиеся монетки 
   принесли бы вторую часть - что и требуется :)
5. Сделал решение на основе "банкомата", с последовательным расчетом сумм.
6. Столкнулся с тем, что работает быстро, НО ни как не смог попасть в требуемые условия: 0.25 секунд, 8Mb.
   Либо первый либо второй показатель не выполнялся.
7. Пробовал: векторы, наборы, мапы, мультимапы, даже минисборщик мусора сделал :)))) чтобы чистить память
   только при достижения границы, всё равно границу пересекал :)
8. Пройдя 100 попыток, решил посмотреть альтернативные решения, хотя опечалился, т.к. придется реализовывать типовой механиз.
9. Почитал, и выяснилос, что задача типовая, с несколькими алгоритмами решений :(
10. Ну что поделать, стал смотреть варианты алгоритмов.     
11. Текущее задание сводится к задаче разбиения множества чисел: 
11.1. https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D1%80%D0%B0%D0%B7%D0%B1%D0%B8%D0%B5%D0%BD%D0%B8%D1%8F_%D0%BC%D0%BD%D0%BE%D0%B6%D0%B5%D1%81%D1%82%D0%B2%D0%B0_%D1%87%D0%B8%D1%81%D0%B5%D0%BB
11.2. Partition problem: https://en.wikipedia.org/wiki/Partition_problem
11.3. Существует несколько алгоритмов решения задачи, выбрал Псевдополиномиальный алгоритм, 
       на мой взгляд, наиболее понятный: https://en.wikipedia.org/wiki/Pseudopolynomial_time_number_partitioning
11.4. Перешел к его реализации на основе собранного материала.
12. Кроме того существует 2 варианта решения по выбранному алгоритму: 
12.1. С использованием матрицы
12.2. С использованием одномерного массив - выберем его, как оптимизированное по памяти - чтобы снова
      не попасть в граничные условия :)
12.3. Суть алгоритма состоит в последовательном обходе всех итогов партий, и остатков 
      разницы между итогом партии (с последовательным обходом возможных остатков) (что имеем и что должно остаться).
12.4. Если мы находим ячейку, где установлен признак наличия числа, дополняющего текущее значение
      до требуемой суммы, то ставим в этой ячейке индикатор, что число найдено.
12.5. Таким образом, в итоге, мы должны получить в ячейке с индексом равным 
      половинной сумме позитивный индикатор, в нашем случае просто Истина.
-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
1. Мы используем для расчета ранее посчитанные данные.
2. Мы смотрим все возможные комбинации чисел.
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
1. O(СуммыЭлементов * КоличествоЭлементов) - последовательно обходим очки партий и остатки.
-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
1. Итоговая пространственная сложность решения равна O(СуммаЭлементов), т.к. храним вектор размером
   половины суммы. Пишу как суммы, т.к. зависит от неё.
*/

#include <iostream>
#include <vector>

bool solvePartitionProblem(std::vector<int>& scores, int countParties, int sumScoresParties);

int main(){

    // Ввод данных
    int sumScoresParties = 0;
    int countParties = 0;
    std::cin >> countParties;

    int inputValue = 0;
    std::vector<int> scores;
    for(int i=0; i<countParties; ++i){
        std::cin >> inputValue;

        // Сразу исключим незначащие нули, для оптимизации
        if (inputValue == 0)
            continue;

        scores.push_back(inputValue);
        sumScoresParties += inputValue;
    }

    // Проверяем возможность построения одинаковых сумм 
    std::cout << (solvePartitionProblem(scores, scores.size(), sumScoresParties) ? "True" : "False");

	return 0;
}   

bool solvePartitionProblem(std::vector<int>& scores, int countParties, int sumScoresParties)
{
	if (sumScoresParties % 2 != 0)
		return false;

    int resultVectorSize = sumScoresParties / 2 + 1;
    std::vector <bool> resultVector(resultVectorSize);

	for (int partNum = 0; partNum < countParties; ++partNum){
        int currentPartiesScore = scores[partNum];
		for (int score = sumScoresParties / 2; score >= currentPartiesScore; --score)
			if (resultVector[score - currentPartiesScore] == true || score == currentPartiesScore)
				resultVector[score] = true;
    }

	return resultVector[sumScoresParties / 2];
}