#include <cstdio>
#include <io.h>
#include <string.h>
#include<iostream>
using namespace std;
#define START int

#define   FUNC()   int a=5; cout<<a<<endl;

START main()/////
{
  /* int a = 5;
    int f = 6;*/

    //FUNC();

    //a = 8;
    //cout << a << endl;


    setlocale(0, "");
    ///////1. Структура для хранения инфо о файле

    ///////   #include <io.h>    _finddata_t    file information in a  structure
    //////  https://docs.microsoft.com/en-us/cpp/c-runtime-library/filename-search-functions?view=msvc-170
    //////#ifdef _USE_32BIT_TIME_T    если определен этот макро то 
    //////#define _finddata_t     _finddata32_t
    //////#define _finddatai64_t  _finddata32i64_t
    //////#else
    //////#define _finddata_t     _finddata64i32_t
    //////#define _finddatai64_t  __finddata64_t
    //////#endif
    //////struct _finddata32_t   один из вариантов для _finddata_t
    //////{
    //////    unsigned    attrib;
    //////    __time32_t  time_create;    // -1 for FAT file systems
    //////    __time32_t  time_access;    // -1 for FAT file systems
    //////    __time32_t  time_write;
    //////    _fsize_t    size;
    //////    char        name[260];
    //////};

    //////Поле  unsigned    attrib  атрибут - битовые значения
    //////#define _A_NORMAL 0x00 // Normal file - No read/write restrictions
    //////#define _A_RDONLY 0x01 // Read only file
    //////#define _A_HIDDEN 0x02 // Hidden file
    //////#define _A_SYSTEM 0x04 // System file
    //////#define _A_SUBDIR 0x10 // Subdirectory
    //////#define _A_ARCH   0x20 // Archive file

    //////2. Функция которая находит файл по маске поиска и заполняет 
    //        /*intptr_t _findfirst(
    //            const char* filespec,           ///Target file specification, маска поиска
    //            struct _finddata_t* fileinfo    ///File information buffer, структура инфо вайла кот заполняется
    //        );
    //        Return Value
    //            If successful, _findfirst returns a unique search handle identifying the file or group of files that match the filespec specification, which can be used in a subsequent call to _findnext or to _findclose.Otherwise, _findfirst returns - 1 and sets errno to one of the following values.

    //            errno value	Condition
    //            EINVAL	Invalid parameter : filespec or fileinfo was NULL.Or, the operating system returned an unexpected error.
    //            ENOENT	File specification that could not be matched.
    //            ENOMEM	Insufficient memory.
    //            EINVAL	Invalid file name specification or the file name given was larger than MAX_PATH.*/


    _finddata_t data = {};//////структура для хранения инфо о файле

    // Путь, содержащий маску поиска.
    char szPath[] = "F:\\*";

    // Поиск файлов и папок по указанной маске.
    intptr_t hFile = _findfirst(szPath, &data);///// 

    // Если был найдем хотя бы один файл или папка.
    if (hFile != -1)
    {
        do
        {
            if (strcmp(data.name, ".") != 0 && strcmp(data.name, ".."))///////////
            {
                // Атрибуты:
                // _A_NORMAL - Обычный файл без запретов на чтение или запись. 
                // _A_RDONLY - Файл только для чтения. 
                // _A_HIDDEN - Скрытый файл. 
                // _A_SYSTEM - Системный файл. 
                // _A_SUBDIR - Директория. 
                // _A_ARCH - Архивный файл.

                // Если была найдена папка.
                if (data.attrib & _A_ARCH && !(data.attrib & _A_SYSTEM))
                {
                    printf("%-10s: %s\n", "File", data.name);
                }

             /*   if (data.attrib & _A_SUBDIR && !(data.attrib & _A_SYSTEM))
                {
                    printf("%-10s: %s\n", "Folder", data.name);
                }*/
                // Если был найден файл.
                else
                {
                    continue;
                }
                /*}*/
            }
           }
            // Переход на следующий найденный файл или папку.
            while (_findnext(hFile, &data) != -1);

            // Очистка памяти от группы найденных файлов.
            _findclose(hFile);
     }
   
   
    else
    {
        printf("No files or directories that match the specified mask.\n");
    }

    return 0;
   
}

