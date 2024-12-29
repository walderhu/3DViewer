cmake_minimum_required(VERSION 3.10)
project(s21_3DViever_Tests C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/opt/Qt/6.7.2/gcc_64/lib/cmake")

# Установка флагов покрытия для компилятора
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")

if(ENABLE_COVERAGE)
    target_compile_options(s21_3DViever_Tests PRIVATE ${GCOV_FLAGS})
endif()

# Определяем переменные для платформы
if(APPLE)
    set(det_OS "-lcheck")
    set(GCOV_FLAGS "-fprofile-arcs -ftest-coverage")
elseif(UNIX AND NOT APPLE)
    set(det_OS "-lcheck -lm -lpthread -lrt -lsubunit")
else()
    set(det_OS "-lcheck -lm -lpthread -lrt")
    set(GCOV_FLAGS "-fprofile-arcs -ftest-coverage")
endif()

# Включаем директории для проекта
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Получаем все .c файлы из директории тестов
file(GLOB TEST_SOURCES
    # s21_3DViever_Tests/*.c
    ./*.c
)

# Добавляем исполняемый файл для тестов
add_executable(s21_3DViever_Tests
    ../Core/affine.c
    ../Core/parser.c
    s21_3DViever_Tests.c
    ${TEST_SOURCES}
)

# Линкуем необходимые библиотеки
target_link_libraries(s21_3DViever_Tests
    m
    ${det_OS}
)

# Включаем опции покрытия, если это требуется
option(ENABLE_COVERAGE "Enable coverage reporting" ON)
if(ENABLE_COVERAGE)
    target_compile_options(s21_3DViever_Tests PRIVATE ${GCOV_FLAGS})
endif()

# Добавляем цель для запуска тестов
add_custom_target(test
    COMMAND s21_3DViever_Tests
    DEPENDS s21_3DViever_Tests
)

# Добавляем цель для генерации отчета о покрытии
add_custom_target(gcov_report
    COMMAND lcov -t "s21_3DViever_Tests" -o test.info -c -d .
    COMMAND genhtml -o report test.info
    COMMAND open report/index.html
    DEPENDS test
)