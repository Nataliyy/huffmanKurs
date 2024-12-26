#ifndef HUFFMAN_H 
#define HUFFMAN_H 

#include <string> 
#include <unordered_map> 
#include <iostream> 
#include <fstream> 
#include <queue> 

/**
 * @brief ���������, �������������� ���� � ������ ��������.
 *
 * �������� ������, ��� �������, � ����� ��������� �� ������ � ������� ��������.
 */
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
};
/**
 * @brief �������� ������ �� �����.
 *
 * ������ ����� �� ���������� ����� � ���������� ��� � ���� ������.
 *
 * @param filename ���� � �����.
 * @return ������, ���������� ����� �� �����, ��� ������ ������ � ������ ������.
 */
std::string loadTextFromFile(const std::string& filename);

/**
 * @brief ���������� ������ �������� � ��������� ����� ��������.
 *
 * ������ ������ �������� �� ������ ������� �������� �� ������� ������ � ���������� ���� �������� ��� ������� �������.
 *
 * @param text ������� �����.
 * @param huffmanCode �����, � ������� ����� �������� ���� �������� (������ -> ���).
 * @return ��������� �� ������ ������ ��������.
 */
Node* buildHuffmanTree(const std::string& text, std::unordered_map<char, std::string>& huffmanCode);

/**
 * @brief ������ ��������������� ��������� � �������� ����.
 *
 * ���������� �������������� ������ � ��������� �������� ����.
 *
 * @param encodedString �������������� ������.
 * @param filename ��� ����� ��� ������.
 */
void writeEncodedMessageToFile(const std::string& encodedString, const std::string& filename);

/**
 * @brief ������ ��������������� ��������� �� ��������� �����.
 *
 * ������ �������������� ��������� �� ���������� ��������� ����� � ���������� ��� � ���� ������.
 *
 * @param filename ��� ����� ��� ������.
 * @return �������������� ������, ��� ������ ������ � ������ ������.
 */
std::string readEncodedMessageFromFile(const std::string& filename);
/**
 * @brief ������������� ��������� �� �����.
 *
 * ������ �������������� ��������� �� ��������� �����, ���������� ��� ��������� ������ �������� � ���������� ��������� � ��������� ����.
 *
 * @param inputFilename ��� �������� ��������� ����� (�������������� ���������).
 * @param outputFilename ��� ��������� ���������� ����� (�������������� ���������).
 * @param root ��������� �� ������ ������ ��������.
 */
void decodeMessageFromFile(const std::string& inputFilename, const std::string& outputFilename, Node* root);


#endif
