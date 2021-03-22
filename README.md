# ClientServerZmq1

 == ЗАДАЧА 1 (С++ ZMQ) == 

Программа обработки и передачи информации о студентах клиентам от сервера по протоколу ZeroMQ.

Действия сервера:
 - Сформировать обобщенный список студентов. В качестве исходных данных использовать 2 файла student_file_1.txt и student_file_2.txt в следующем формате:

        student_file_1.txt
        ----
        1 Ivan Ivanovich 01.01.1988
        2 Petr Petrov 04.07.1988
        3 Denis Denisov 43.01.1988
        4 Vladimir Jukov 04.5.1987
        5 Vladimir Kochkin 11.10.1989
        ----
    
        student_file_2.txt
        ----
        34 Ivan Ivanovich 01.01.1988
        54 Petr Kazakov 05.07.1986
        23 Denis Denisov 04.03.1988
        12 Vladimir Jukov 04.5.1987
        43 Vladimir Kochkin 11.11.1989
        ----
 - Объединить одинаковых студентов по ФИО и дате рождения
 - Отправить полученный список на клиент по протоколу ZeroMQ pub
 
Действия клиента (sub):
 - Принять все полученные данные от сервера по протоколу ZeroMQ sub
 - Отсортировать студентов по ФИО
 - Отобразить отсортированный список студентов на экране

Для компиляции и запуска сервера через командную строку выполнитe:
 -  cd server/build/
 -  cmake ..
 -  make
 -  ./server 3 student_file_1.txt student_file_2.txt 

Для клиента:
 -  cd client/build/
 -  cmake ..
 -  make
 -  ./client

Дополнительное 

 == ЗАДАЧА 2 (C++ HTTP) ==

Реализовать аналогичный обмен (с задачей 1) по протоколам HTTP\REST.

 == ДОПОЛНИТЕЛЬНЫЕ ТРЕБОВАНИЯ К ЗАДАЧА 1 и ЗАДАЧА 2 (ОПЦИОНАЛЬНО):
 - решение задачи 2 должно являться расширением функционала задачи 1
 - обеспечить одновременную работу задачи 1 и задачи 2 в рамках разных потоков одного адресного пространства
 - многопоточность
  -- прием и обработка данных должны выполняться в отдельных потоках (для http свой, для zmq свой)
  -- обработка данных должна всегда проходить в отдельном потоке (всегда в одном)
  -- Gui поток не должен выполнять задачи по приему, разбору и обработке данных

 == ЗАДАЧА 3 (SQL) ==

Имеется table1(id, value) и table2(id, value) с однородными, местами дублирующими данными. 
Необходимо:
 - Написать SQL скрипт создания таблицы table3(id, value)
 - Написать SQL скрипт наполняющий созданную таблицу данными по следующим правилам:
     - все записи из table1, которых нет в table2 поместить в table3
     - все записи из table2, которых нет в table1 поместить в table3
