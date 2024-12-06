#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;

struct Contact {
    string name;
    string phone;
};

class HashTable {
private:
    vector<list<Contact>> table;
    size_t table_size;
    size_t total_inserts = 0;
    double total_insert_time = 0.0;
    double total_search_time = 0.0;

    size_t hashFunction(const string &key) {
        size_t hash = 0;
        for (char ch : key) {
            hash += ch;
        }
        return hash % table_size;
    }

public:
    HashTable(size_t size) : table_size(size) {
        table.resize(size);
    }

    void addContact(const string &name, const string &phone) {
        auto start = chrono::high_resolution_clock::now();
        size_t index = hashFunction(name);
        for (auto &contact : table[index]) {
            if (contact.name == name) {
                contact.phone = phone;
                return;
            }
        }
        table[index].push_back({name, phone});
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duration = end - start;
        total_inserts++;
        total_insert_time += duration.count();
    }

    void searchContact(const string &name) {
        auto start = chrono::high_resolution_clock::now();
        size_t index = hashFunction(name);
        for (const auto &contact : table[index]) {
            if (contact.name == name) {
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration = end - start;
                total_search_time += duration.count();
                cout << "Telefone de " << name << ": " << contact.phone
                     << " (tempo de busca: " << fixed << setprecision(2) << duration.count() << " ms)\n";
                return;
            }
        }
        cout << "Contato não encontrado.\n";
    }

    void removeContact(const string &name) {
        size_t index = hashFunction(name);
        auto &chain = table[index];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->name == name) {
                chain.erase(it);
                return;
            }
        }
        cout << "Contato não encontrado.\n";
    }

    void displayContacts() {
        for (size_t i = 0; i < table_size; ++i) {
            if (!table[i].empty()) {
                cout << "Índice " << i << ":\n";
                for (const auto &contact : table[i]) {
                    cout << "  Nome: " << contact.name << ", Telefone: " << contact.phone << "\n";
                }
            }
        }
    }

    void displayPerformance() {
        cout << "Tempo médio de inserção: "
             << (total_inserts > 0 ? total_insert_time / total_inserts : 0.0) << " ms\n";
        cout << "Tempo médio de busca: "
             << (total_inserts > 0 ? total_search_time / total_inserts : 0.0) << " ms\n";
    }
};

int main() {
    HashTable phoneBook(10);
    int option;

    do {
        cout << "1 - Adicionar contato\n2 - Buscar contato por nome\n3 - Remover contato\n4 - Exibir todos os contatos\n5 - Exibir desempenho\n0 - Sair\n";
        cin >> option;

        string name, phone;
        switch (option) {
            case 1:
                cout << "Nome: ";
                cin.ignore();
                getline(cin, name);
                cout << "Telefone: ";
                getline(cin, phone);
                phoneBook.addContact(name, phone);
                break;
            case 2:
                cout << "Nome: ";
                cin.ignore();
                getline(cin, name);
                phoneBook.searchContact(name);
                break;
            case 3:
                cout << "Nome: ";
                cin.ignore();
                getline(cin, name);
                phoneBook.removeContact(name);
                break;
            case 4:
                phoneBook.displayContacts();
                break;
            case 5:
                phoneBook.displayPerformance();
                break;
        }
    } while (option != 0);

    return 0;
}