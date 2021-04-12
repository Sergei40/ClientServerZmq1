простой клиент-сервер ZMQ

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
