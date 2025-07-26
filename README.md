# Infotecs Intership Test Assignment

## Обзор
Проект является решением тестового задания, видимо, предолженного компанией infotecs на стажерскую позицию C++-разработчика.
Условие тестового задания было взято из [репозитория](https://github.com/toniess/Infotecs_internship/tree/main). 
Также с условием тестового задания можно ознакомиться в соответствующем файле `assets/asssignment.pdf`.

## Сборка и запуск
Для сборки проекта используется CMake. 
В проекте используется Boost.ASIO, поэтому для сборки проекта требуется его предустановить.

### Инструкции по сборке 
```shell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target receiver
cmake --build build --target sender
```