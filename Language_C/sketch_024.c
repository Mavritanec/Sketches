// Function of reading a record of a given type from a file by its serial number
// Функция чтения записи заданного типа из файла по ее порядковому номеру
struct my_struct read_record_from_file(FILE *pfile, int index)
{
    // Calculation of the offset at which desired entry should be located from the beginning of the file
    // Вычисление смещения, по которому искомая запись должна располагаться от начала файла
    int offset = index * sizeof(struct my_struct);
    // Move the position pointer to the calculated offset from the beginning of the file
    // Переместите указатель позиции на рассчитанное смещение от начала файла
    fseek(pfile, offset, SEEK_SET);

    // Reading a record of the specified type from a file
    // Чтение записи указанного типа из файла
    struct my_struct record;
    fread(&record, sizeof(struct my_struct), 1, pfile);

    // For safety reasons, we return the file position pointer to the beginning of the file
    // В целях безопасности мы возвращаем указатель позиции файла в начало файла
    rewind(pfile);

    // Return read record
    // Вернуть прочитанную запись
    return record;
}

// Function of writing a record of the specified type to the file at the specified serial number
// Функция записи записи указанного типа в файл по указанному порядковому номеру
void write_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index)
{
    // Calculation of the offset at which the required record should be located from the beginning of the file
    // Вычисление смещения, по которому должна располагаться искомая запись от начала файла
    int offset = index * sizeof(struct my_struct);
    // Move the position pointer to the calculated offset from the beginning of the file
    // Переместите указатель позиции на рассчитанное смещение от начала файла
    fseek(pfile, offset, SEEK_SET);

    // Write a record of the specified type to a file
    // Записать запись указанного типа в файл
    fwrite(record_to_write, sizeof(struct my_struct), 1, pfile);

    // Just in case, force the I/O subsystem to write the contents of its buffer to a file right now
    // На всякий случай заставьте подсистему ввода-вывода прямо сейчас записать содержимое своего буфера в файл
    fflush(pfile);

    // For safety reasons, return the file position pointer to the beginning of the file
    // В целях безопасности верните указатель позиции файла в начало файла
    rewind(pfile);
}

// Function of mutual transfer of two records in the file by their indexes
// Функция взаимного переноса двух записей в файле по их индексам
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2)
{
    // Read both records from file to variables
    // Прочитать обе записи из файла в переменные
    struct my_struct record1 = read_record_from_file(pfile, record_index1);
    struct my_struct record2 = read_record_from_file(pfile, record_index2);

    // Rewrite records in file
    // Переписать записи в файл
    write_record_in_file(pfile, &record1, record_index2);
    write_record_in_file(pfile, &record2, record_index1);
}

// Function to get file size in bytes
// Функция для получения размера файла в байтах
int get_file_size_in_bytes(FILE *pfile)
{
    int size = 0;
    // Move the position pointer to the end of the file
    // Переместите указатель позиции в конец файла
    fseek(pfile, 0, SEEK_END);
    // Read the number of bytes from the beginning of the file to the current position pointer
    // Прочитать количество байтов от начала файла до указателя текущей позиции
    size = ftell(pfile);
    // For safety reasons, move the position pointer back to the beginning of the file
    // В целях безопасности переместите указатель позиции обратно в начало файла
    rewind(pfile);
    return size;
}

// Function to get count of records in file
// Функция для получения количества записей в файле
int get_records_count_in_file(FILE *pfile)
{
    return get_file_size_in_bytes(pfile) / sizeof(struct my_struct);
}
