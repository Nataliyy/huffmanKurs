
#include "huffman.h" 

using namespace std;

/*
 * @brief Главная функция программы.
 *
 * Загружает текст из файла, строит дерево Хаффмана, кодирует и записывает закодированный текст в бинарный файл,
 * а затем декодирует и записывает декодированный текст в текстовый файл.
 *
 * @return 0, если программа выполнена успешно, 1 в случае ошибки.
 */
int main() {
    setlocale(LC_ALL, "rus"); 

    string inputfile;
    cout << "Enter file pdth and name:\n"; // Запрос пути к входному файлу от пользователя
    cin >> inputfile;

    /*
     * @brief Загрузка текста из входного файла.
     *
     * Функция loadTextFromFile() (реализация должна быть в huffman.h/.cpp) читает текст из указанного файла.
     */
    string inputText = loadTextFromFile(inputfile);

    /*
     * @brief Проверка на наличие ошибок при загрузке файла.
     * Если функция loadTextFromFile вернула пустую строку - значит файл не был открыт или пуст.
     */
    if (inputText.empty()) {
        cerr << "Ошибка: входной файл пуст или не найден!" << endl;
        return 1; 
    }
    // Проверка на количество уникальных символов 
    unordered_map<char, int> freq;
    for (char ch : inputText) {
        freq[ch]++;
    }
    if (freq.size() <= 1) {
        cerr << "Ошибка: входной файл содержит недостаточно уникальных символов для кодирования Хаффмана (необходимо минимум 2)." << endl;
        return 1;
    }
    unordered_map<char, string> huffmanCode; // Карта для хранения кодов Хаффмана (символ -> код)
    /*
     * @brief Построение дерева Хаффмана.
     * Функция buildHuffmanTree() (реализация должна быть в huffman.h/.cpp) строит дерево Хаффмана на основе входного текста.
     */
    Node* root = buildHuffmanTree(inputText, huffmanCode);

    string encodedString = ""; // Строка для хранения закодированного текста
    /*
     * @brief Кодирование текста с помощью кодов Хаффмана.
     * Каждый символ из inputText заменяется на соответствующий код из huffmanCode
     */
    for (char ch : inputText) {
        encodedString += huffmanCode[ch];
    }

    /*
     * @brief Запись закодированного текста в бинарный файл.
     * Функция writeEncodedMessageToFile() (реализация должна быть в huffman.h/.cpp) записывает закодированный текст в файл encoded.bin.
     */
    writeEncodedMessageToFile(encodedString, "encoded.bin");

    cout << "Huffman Codes (Character -> Code):\n";
    /*
     * @brief Вывод таблицы кодов Хаффмана.
     * Цикл перебирает все пары символ-код и выводит их на экран.
     */
    for (const auto& pair : huffmanCode) {
        if (pair.first == ' ') {
            cout << "' ' -> " << pair.second << '\n'; // Для пробела явно указываем 
        }
        else {
            cout << "'" << pair.first << "' -> " << pair.second << '\n';
        }
    }
    cout << '\n';

    /*
     * @brief Декодирование и запись декодированного текста в файл.
     * Функция decodeMessageFromFile() (реализация в huffman.cpp) читает закодированный текст, декодирует его с помощью дерева Хаффмана и записывает в decoded.txt
     */
    decodeMessageFromFile("encoded.bin", "decoded.txt", root);

    cout << "Процесс завершён. Проверьте файлы encoded.bin и decoded.txt." << endl;

    return 0;
}
