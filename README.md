# -course-project

Темой курсового проекта является «Разработка программы решения систем линейных уравнений».
Нахождение решений систем линейных алгебраических уравнений производится с помощью следующих методов:
-	метод Гаусса;
-	метод квадратных корней.

МОДУЛЬ Matrix
-----------------------------------------------------------------------------------------------------

Содержит шаблонный класс матрицы с соответствующими методами для ее инициализации и объявления, 
математические методы для решения СЛАУ и деструктор, обеспечивающий освобождение выделенной в ходе выполнения программы памяти.

ПОДПРОГРАММЫ МОДУЛЯ Matrix
-----------------------------------------------------------------------------------------------------
SetElements
Процедура для заполнения матрицы пользователем.

Print
Процедура вывода матрицы

calculateGauss
Функция вычисления корней СЛАУ методом Гаусса.

Gauss
Процедура, выполняющая присвоение корней системы по методу Гаусса вектору X и выводящая результаты на экран.

SquareRoot
Функция, рассчитывающая корни СЛАУ по методу квадратных корней (метод Холецкого).

В ходе разработки программы приоритетной выступила задача оптимизации по памяти. Данная задача была реализована на этапе проектирования 
структуры программного кода посредством создания для матрицы класса, вынесенного в отдельный подключаемый модуль. 
Все массивы данных были определены динамически, и выделенная для них память по завершению программы очищается. 
Формирование класса матрицы шаблонным позволило избежать повторяемости кода. 
Кроме того, программа оптимизирована по времени. Для реализации данной задачи были применены такие методы оптимизации, как исключение 
инвариантных выражений в циклах (чистка циклов), сжатие циклов, минимизация преобразования типов в выражениях. 



РУКОВОДСТВО ПОЛЬЗОВАТЕЛЯ
-----------------------------------------------------------------------------------------------------

За запуском последует просьба ввести количество уравнений в системе, которую необходимо решить, после чего необходимо нажать кнопку Enter.
После чего программа предоставит пользователю выбор метода для решения системы линейных алгебраических уравнений посредством выбора пункта меню.
За выбором метода для решения СЛАУ следует просьба ввести расширенную матрицу системы уравнений, как продемонстрировано на рисунке 7.5. 
Ввод упорядочен и имеет ограничения. Допустимо значение коэффициентов в диапазоне от -100 до 100, в противном случае программа вернет пользователю ошибку.
По нажатию кнопки Enter программа осуществляет вывод расширенной матрицы системы и корни, рассчитанные по выбранному методу.
После вывода результатов программа снова выводит меню. При выборе пункта «Выход из программы» осуществляется остановка работы исполняемого файла.

-----------------------------------------------------------------------------------------------------

В ходе разработки была применена методология объектно-ориентированного программирования. Взаимодействие программных объектов в такой системе осуществляется 
путем передачи сообщений.

-----------------------------------------------------------------------------------------------------

В ходе написания курсового проекта была составлена рациональная структура, реализованы спроектированные классы и методы, предусмотрена защита от ошибок. 
Отлаженная программа прошла тестирование в нормальных, экстремальных условиях и исключительных ситуациях. 
Результатом разработки является оптимизированная консольная программа, удовлетворяющая всем заявленным требованиям. 

