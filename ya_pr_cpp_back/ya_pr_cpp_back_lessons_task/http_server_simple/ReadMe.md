
Подготовка проекта к сборке:
1. Очистить папку build
2. Выполнить в папке build: 
conan install ..
cmake ..
cmake --build .
3. В каталоге build/bin появится собранный файл
4. Запустить ./bin/ИмяФайла


Запуск Docker:
docker build -t my_http_server .
docker run --rm -p 8080 my_http_server


Запуск сервера:
./game_server ../../data/config.json
Server has started...

Обращение к серверу из браузера:
http://127.0.0.1:8080/api/v1/maps
http://127.0.0.1:8080/api/v1/maps/map1

'images/cube.svg'


Запуск сервера с картинками из папки bin:
./game_server ../../data/config.json ../../static

Обращение к серверу из браузера:
http://127.0.0.1:8080/images/cube.svg
