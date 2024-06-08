// https://contest.yandex.ru/contest/25597/run-report/115056965/
// Задача показалась интересной, и изначально стал её решать пробуя разные методы:
// 1. Заметил, что мы можем только при четном числе получить положительный резульат
// 2. Заметил, что если число четное и мы ищем две половины, то нам достаточно посичитать только одну из них.
// 3. В итоге, полумал подумал и узнал задачу из спринта, по подбору монет.
// 4. В этом случае, нам необходимо было подобрать монетки для половины суммы, значит оставшиеся монетки 
//    принесли бы втрую часть - что и требуется :)
// 5. Сделал решение на основе "банкомата", с последовательным расчетом сумм.
// 6. Столкнулся с тем, что работает быстро, НО ни как не смог попасть в требуемые условия: 0.25 секунд, 8Mb.
//    Либо первый либо второй показатель не выполнялся.
// 7. Пробовал: векторы, наборы, мапы, мультимапы, даже минисборщик мусора сделал :)))) чтобы чистить память
//    только при достижения границы, всё равно границу пересекал :)
// 8. Пройдя 100 попыток, решил посмотреть, альтернативные решения, хотя опечалился, т.к. придется реализовывать типовой механиз.
// 9. Почитал, и выяснилос, что задача типовая, с несколькими алгоритмами решений :(
// 10. Ну что поделать, стал смотреть варианты алгоритмов.     
// 11. Текущее задание сводится к задае разбиения множества чисел: 
// 11.1. https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D1%80%D0%B0%D0%B7%D0%B1%D0%B8%D0%B5%D0%BD%D0%B8%D1%8F_%D0%BC%D0%BD%D0%BE%D0%B6%D0%B5%D1%81%D1%82%D0%B2%D0%B0_%D1%87%D0%B8%D1%81%D0%B5%D0%BB
// 11.2. Partition problem: https://en.wikipedia.org/wiki/Partition_problem
// 11.3. Существует несколько алгоритмов решения задачи, выбрал Псевдополиномиальный алгоритм, 
//        как, на мой взгляд, наиболее понятный:
//        https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D1%80%D0%B0%D0%B7%D0%B1%D0%B8%D0%B5%D0%BD%D0%B8%D1%8F_%D0%BC%D0%BD%D0%BE%D0%B6%D0%B5%D1%81%D1%82%D0%B2%D0%B0_%D1%87%D0%B8%D1%81%D0%B5%D0%BB#%D0%9F%D1%81%D0%B5%D0%B2%D0%B4%D0%BE%D0%BF%D0%BE%D0%BB%D0%B8%D0%BD%D0%BE%D0%BC%D0%B8%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B9_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC
//        https://en.wikipedia.org/wiki/Pseudopolynomial_time_number_partitioning
// 11.4. Перешел к его реализации на основе собранного материала.

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

    std::cout << (solvePartitionProblem(scores, scores.size(), sumScoresParties) ? "True" : "False");

	return 0;
}   

bool solvePartitionProblem(std::vector<int>& scores, int countParties, int sumScoresParties)
{
	if (sumScoresParties % 2 != 0)
		return false;

    int calculatingVectorSize = sumScoresParties / 2 + 1;
    std::vector <bool> calculatingVector(calculatingVectorSize);

	for (int partNum = 0; partNum < countParties; ++partNum)
		for (int score = sumScoresParties / 2; score >= scores[partNum]; --score)
			if (calculatingVector[score - scores[partNum]] == true || score == scores[partNum])
				calculatingVector[score] = true;

	return calculatingVector[sumScoresParties / 2];
}
