# bpoptim
Bond Portfolio Optimization

Эта программа осуществляет минимизацию дюрации портфеля облигаций. 
Исходными данными являются дюрации, входящих в портфель бумаг, и целевая доходность портфеля.

Использование программы:
bpoptim targetrate csvfile
где:
	targetrate 	- целевая ставка доходности портфеля в %
	csvfile		- CSV-файл с данными.

Пример:
bpoptim 12 portfolio.csv

Пример CSV-файла (portfolio.csv) находится в корневой директории.
Иходные данные для файла можно скачать с сайта https://www.rusbonds.ru/ в формате Excel.

(например, по ссылке: https://www.rusbonds.ru/compare.asp).

Далее нужно убрать из скачанного файла "шапку", ненужные строки внизу, добавить столбец с нумерацией и сохранить в формате CSV.


КОМПИЛЯЦИЯ ПРОГРАММЫ ТРЕБУЕТ ПРИСОЕДИНЕНИЯ БИБЛИОТЕКИ ALGLIB (http://www.alglib.net/). 


Оговорки:

Использование программы допускается только в личных, некоммерческих целях.

Допускается дополнение/изменение кода, направленное на совершенствование программы для дальнейшего индивидуального использования или в ознакомительных/учебных целях.

Не допускает публикация программы или её части без согласия автора.

Автор не несет ответственности за любые инвестиционные решения, принятые на основании результатов работы программы, за возможные ошибки или 
некорректную работу программы.
