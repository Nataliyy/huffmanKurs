#ifndef HUFFMAN_H 
#define HUFFMAN_H 

#include <string> 
#include <unordered_map> 
#include <iostream> 
#include <fstream> 
#include <queue> 

/**
 * @brief Структура, представляющая узел в дереве Хаффмана.
 *
 * Содержит символ, его частоту, а также указатели на левого и правого потомков.
 */
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
};
/**
 * @brief Загрузка текста из файла.
 *
 * Читает текст из указанного файла и возвращает его в виде строки.
 *
 * @param filename Путь к файлу.
 * @return Строка, содержащая текст из файла, или пустая строка в случае ошибки.
 */
std::string loadTextFromFile(const std::string& filename);

/**
 * @brief Построение дерева Хаффмана и генерация кодов Хаффмана.
 *
 * Строит дерево Хаффмана на основе частоты символов во входном тексте и генерирует коды Хаффмана для каждого символа.
 *
 * @param text Входной текст.
 * @param huffmanCode Карта, в которую будут записаны коды Хаффмана (символ -> код).
 * @return Указатель на корень дерева Хаффмана.
 */
Node* buildHuffmanTree(const std::string& text, std::unordered_map<char, std::string>& huffmanCode);

/**
 * @brief Запись закодированного сообщения в бинарный файл.
 *
 * Записывает закодированную строку в указанный бинарный файл.
 *
 * @param encodedString Закодированная строка.
 * @param filename Имя файла для записи.
 */
void writeEncodedMessageToFile(const std::string& encodedString, const std::string& filename);

/**
 * @brief Чтение закодированного сообщения из бинарного файла.
 *
 * Читает закодированное сообщение из указанного бинарного файла и возвращает его в виде строки.
 *
 * @param filename Имя файла для чтения.
 * @return Закодированная строка, или пустая строка в случае ошибки.
 */
std::string readEncodedMessageFromFile(const std::string& filename);
/**
 * @brief Декодирование сообщения из файла.
 *
 * Читает закодированное сообщение из бинарного файла, декодирует его используя дерево Хаффмана и записывает результат в текстовый файл.
 *
 * @param inputFilename Имя входного бинарного файла (закодированное сообщение).
 * @param outputFilename Имя выходного текстового файла (декодированное сообщение).
 * @param root Указатель на корень дерева Хаффмана.
 */
void decodeMessageFromFile(const std::string& inputFilename, const std::string& outputFilename, Node* root);


#endif
