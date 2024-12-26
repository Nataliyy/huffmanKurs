
#include "huffman.h" 

using namespace std;

/*
 * @brief ������� ������� ���������.
 *
 * ��������� ����� �� �����, ������ ������ ��������, �������� � ���������� �������������� ����� � �������� ����,
 * � ����� ���������� � ���������� �������������� ����� � ��������� ����.
 *
 * @return 0, ���� ��������� ��������� �������, 1 � ������ ������.
 */
int main() {
    setlocale(LC_ALL, "rus"); 

    string inputfile;
    cout << "Enter file pdth and name:\n"; // ������ ���� � �������� ����� �� ������������
    cin >> inputfile;

    /*
     * @brief �������� ������ �� �������� �����.
     *
     * ������� loadTextFromFile() (���������� ������ ���� � huffman.h/.cpp) ������ ����� �� ���������� �����.
     */
    string inputText = loadTextFromFile(inputfile);

    /*
     * @brief �������� �� ������� ������ ��� �������� �����.
     * ���� ������� loadTextFromFile ������� ������ ������ - ������ ���� �� ��� ������ ��� ����.
     */
    if (inputText.empty()) {
        cerr << "������: ������� ���� ���� ��� �� ������!" << endl;
        return 1; 
    }
    // �������� �� ���������� ���������� �������� 
    unordered_map<char, int> freq;
    for (char ch : inputText) {
        freq[ch]++;
    }
    if (freq.size() <= 1) {
        cerr << "������: ������� ���� �������� ������������ ���������� �������� ��� ����������� �������� (���������� ������� 2)." << endl;
        return 1;
    }
    unordered_map<char, string> huffmanCode; // ����� ��� �������� ����� �������� (������ -> ���)
    /*
     * @brief ���������� ������ ��������.
     * ������� buildHuffmanTree() (���������� ������ ���� � huffman.h/.cpp) ������ ������ �������� �� ������ �������� ������.
     */
    Node* root = buildHuffmanTree(inputText, huffmanCode);

    string encodedString = ""; // ������ ��� �������� ��������������� ������
    /*
     * @brief ����������� ������ � ������� ����� ��������.
     * ������ ������ �� inputText ���������� �� ��������������� ��� �� huffmanCode
     */
    for (char ch : inputText) {
        encodedString += huffmanCode[ch];
    }

    /*
     * @brief ������ ��������������� ������ � �������� ����.
     * ������� writeEncodedMessageToFile() (���������� ������ ���� � huffman.h/.cpp) ���������� �������������� ����� � ���� encoded.bin.
     */
    writeEncodedMessageToFile(encodedString, "encoded.bin");

    cout << "Huffman Codes (Character -> Code):\n";
    /*
     * @brief ����� ������� ����� ��������.
     * ���� ���������� ��� ���� ������-��� � ������� �� �� �����.
     */
    for (const auto& pair : huffmanCode) {
        if (pair.first == ' ') {
            cout << "' ' -> " << pair.second << '\n'; // ��� ������� ���� ��������� 
        }
        else {
            cout << "'" << pair.first << "' -> " << pair.second << '\n';
        }
    }
    cout << '\n';

    /*
     * @brief ������������� � ������ ��������������� ������ � ����.
     * ������� decodeMessageFromFile() (���������� � huffman.cpp) ������ �������������� �����, ���������� ��� � ������� ������ �������� � ���������� � decoded.txt
     */
    decodeMessageFromFile("encoded.bin", "decoded.txt", root);

    cout << "������� ��������. ��������� ����� encoded.bin � decoded.txt." << endl;

    return 0;
}
