#include "huffman.h" 

using namespace std;
// C:\Users\roma_\source\repos\huffmanKurs\huffmanKurs\input.txt input

/**
 * @brief Создает новый узел дерева Хаффмана.
 *
 * @param ch Символ, хранящийся в узле.
 * @param freq Частота встречаемости символа.
 * @param left Указатель на левый дочерний узел.
 * @param right Указатель на правый дочерний узел.
 * @return Указатель на созданный узел.
 */
Node* getNode(char ch, int freq, Node* left, Node* right) {
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}
/**
 * @brief Структура для сравнения узлов дерева Хаффмана по частоте.
 * Используется в priority_queue для построения дерева.
 */
struct comp {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};
/**
 * @brief Рекурсивно кодирует символы в строке, используя дерево Хаффмана.
 *
 * @param root Указатель на корень дерева Хаффмана.
 * @param str Текущий код символа (последовательность '0' и '1').
 * @param huffmanCode Словарь, где ключ - символ, значение - его код Хаффмана.
 */
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}
/**
 * @brief Построение дерева Хаффмана.
 *
 * @param text Текст для кодирования.
 * @param huffmanCode Словарь для хранения кодов Хаффмана.
 * @return Указатель на корень построенного дерева Хаффмана.
 */
Node* buildHuffmanTree(const string& text, unordered_map<char, string>& huffmanCode) {
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, comp> pq;
    for (auto pair : freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }


    Node* root = pq.top();
    encode(root, "", huffmanCode);

    string str = "";
    for (char ch : text) {
        str += huffmanCode[ch];
    }
    cout << "\nЗакодированная строка:\n" << str << '\n';

    return root;

}
uint32_t crc32(const char* data, size_t length) {
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= static_cast<uint32_t>(data[i]);
        for (size_t j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;  
            }
            else {
                crc >>= 1;
            }
        }
    }
    return ~crc;  
}
/*
 * @brief Запись закодированного сообщения в бинарный файл.
 *
 * Функция записывает закодированную строку в указанный бинарный файл,
 * предварительно добавив длину строки и контрольную сумму CRC32.
 *
 * @param encodedString Закодированная строка (последовательность битов).
 * @param filename Имя файла для записи.
 */
void writeEncodedMessageToFile(const string& encodedString, const string& filename) {
    ofstream outFile(filename, ios::binary);
    /*
     * @brief Проверка успешного открытия файла.
     * Если файл не может быть открыт - выводим сообщение об ошибке и выходим.
     */
    if (!outFile.is_open()) {
        cerr << "Не удалось открыть файл для записи: " << filename << endl;
        return;
    }
    /*
     * @brief Запись длины закодированной строки.
     * Записываем размер строки в начале файла, чтобы потом можно было корректно считать строку.
     */
    size_t bitLength = encodedString.size();
    outFile.write(reinterpret_cast<const char*>(&bitLength), sizeof(size_t));
    /*
     * @brief Запись закодированной строки по 8 бит (1 байт).
     * Цикл проходит по строке с шагом 8 бит (1 байт).
     * Если длина строки меньше 8 бит, то она дополняется нулями до 8 бит.
     */
    
    for (size_t i = 0; i < encodedString.length(); i += 8) {
        string byteStr = encodedString.substr(i, 8);
        if (byteStr.length() < 8) {
            byteStr.append(8 - byteStr.length(), '0');
        }

        unsigned char byte = 0;
        for (int j = 0; j < 8; ++j) {
            if (byteStr[j] == '1') {
                byte |= (1 << (7 - j));
            }
        }

        outFile.put(byte);
    }

    /*
     * @brief Расчет и запись контрольной суммы CRC32.
     * Расчитываем контрольную сумму для проверки целостности данных.
     */
    uint32_t checksum = crc32(encodedString.c_str(), encodedString.size());
    outFile.write(reinterpret_cast<const char*>(&checksum), sizeof(uint32_t));

    outFile.close();
}
/**
 * @brief Читает закодированное сообщение из файла.
 *
 * @param filename Имя файла для чтения.
 * @return Закодированная строка.
 */
string readEncodedMessageFromFile(const string& filename, uint32_t& checksum) {
    ifstream inFile(filename, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Не удалось открыть файл для чтения: " << filename << endl;
        return "";
    }

    size_t bitLength = 0;
    inFile.read(reinterpret_cast<char*>(&bitLength), sizeof(size_t));

    string encodedBits = "";
    char byte;
    while (inFile.get(byte)) {
        for (int i = 7; i >= 0; --i) {
            encodedBits += ((byte & (1 << i)) ? '1' : '0');
        }
    }

    inFile.read(reinterpret_cast<char*>(&checksum), sizeof(uint32_t));

    inFile.close();

    if (bitLength < encodedBits.size()) {
        encodedBits = encodedBits.substr(0, bitLength);
    }

    return encodedBits;
}
/*
 * @brief Рекурсивно декодирует строку, используя дерево Хаффмана.
 *
 * @param root Указатель на корень дерева Хаффмана.
 * @param index Текущий индекс в закодированной строке.
 * @param str Закодированная строка.
 * @param decodedString Декодированная строка.
 */
void decode(Node* root, int& index, const string& str, string& decodedString) {
    if (root == nullptr) return;

    if (!root->left && !root->right) {
        decodedString += root->ch;
        return;
    }

    index++;
    if (str[index] == '0')
        decode(root->left, index, str, decodedString);
    else
        decode(root->right, index, str, decodedString);
}
/*
 * @brief Декодирует сообщение из файла и записывает результат в другой файл.
 *
 * @param inputFilename Имя файла с закодированным сообщением.
 * @param outputFilename Имя файла для записи декодированного сообщения.
 * @param root Указатель на корень дерева Хаффмана.
 */
void decodeMessageFromFile(const string& inputFilename, const string& outputFilename, Node* root) {
    uint32_t originalChecksum = 0;
    string encodedMessage = readEncodedMessageFromFile(inputFilename, originalChecksum);
    if (encodedMessage.empty()) {
        cerr << "Закодированное сообщение пустое или файл не найден." << endl;
        return;
    }

   
    string decodedMessage = "";
    int index = -1;

    while (index < (int)encodedMessage.size() - 1) {
        decode(root, index, encodedMessage, decodedMessage);
    }

    // сумма декодированного
    uint32_t decodedChecksum = crc32(decodedMessage.c_str(), decodedMessage.size());

    
    if (originalChecksum != decodedChecksum) {
        cerr << "Контрольные суммы совпадают!" << endl;
        return;
    }
    
    ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        cerr << "Не удалось открыть файл для записи: " << outputFilename << endl;
        return;
    }

    outFile << decodedMessage;
    outFile.close();
}

/*
 * @brief Загружает текст из файла.
 *
 * @param filename Имя файла для загрузки.
 * @return Строка, содержащая текст из файла.
 */
string loadTextFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return "";
    }

    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    return content;
}