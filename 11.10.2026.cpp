#include <iostream>
#include <string>

using namespace std;


class Item {
private:
    string name;      
    double price;     

public:
    
    Item(string itemName, double itemPrice) : name(itemName), price(itemPrice) {
        cout << "[Система] Создан товар: " << name << endl;
    }

    
    ~Item() {
        cout << "[Система] Память освобождена для: " << name << endl;
    }

    
    void printInfo() const {
        cout << "Товар: " << name << " Цена: " << price << " руб." << endl;
    }

    
    string getName() const {
        return name;
    }
};


class Warehouse {
private:
    static const int MAX_CAPACITY = 10;  
    Item* items[MAX_CAPACITY];           
    int currentCount;                    

public:
  
    Warehouse() : currentCount(0) {
        for (int i = 0; i < MAX_CAPACITY; i++) {
            items[i] = nullptr;
        }
        cout << "[Система] Склад создан, вместимость: " << MAX_CAPACITY << endl;
    }

   
    bool addItem(Item* newItem) {
        if (currentCount >= MAX_CAPACITY) {
            cout << "[Ошибка] Склад заполнен! Товар '" << newItem->getName()
                << "' не может быть добавлен." << endl;
            delete newItem;  
            return false;
        }

       
        for (int i = 0; i < MAX_CAPACITY; i++) {
            if (items[i] == nullptr) {
                items[i] = newItem;
                currentCount++;
                cout << "[Система] Товар '" << newItem->getName()
                    << "' добавлен на склад (позиция " << i << ")" << endl;
                return true;
            }
        }
        return false;
    }

    
    bool removeItemByName(string name) {
        for (int i = 0; i < MAX_CAPACITY; i++) {
            if (items[i] != nullptr && items[i]->getName() == name) {
                cout << "[Система] Удаление товара: " << name << endl;

                
                delete items[i];
                items[i] = nullptr;
                currentCount--;

                
                for (int j = i; j < MAX_CAPACITY - 1; j++) {
                    items[j] = items[j + 1];
                }
                items[MAX_CAPACITY - 1] = nullptr;  

                return true;
            }
        }
        cout << "[Ошибка] Товар '" << name << "' не найден на складе." << endl;
        return false;
    }

    
    void printAllItems() const {
        cout << "\n Содержимое склада " << endl;
        int count = 0;
        for (int i = 0; i < MAX_CAPACITY; i++) {
            if (items[i] != nullptr) {
                cout << "[" << i << "] ";
                items[i]->printInfo();
                count++;
            }
        }
        cout << "Всего товаров на складе: " << count << endl;
        
    }

    
    ~Warehouse() {
        cout << "\n[Система] Закрытие склада..." << endl;
        for (int i = 0; i < MAX_CAPACITY; i++) {
            if (items[i] != nullptr) {
                cout << "[Система] Принудительное удаление: " << items[i]->getName() << endl;
                delete items[i];
                items[i] = nullptr;
            }
        }
        cout << "[Система] Склад закрыт, вся память освобождена." << endl;
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    cout << " Демонстрация управления памятью n" << endl;

   
    Warehouse warehouse;

    cout << "\n Добавление товаров на склад " << endl;

    
    warehouse.addItem(new Item("Ноутбук", 75000.0));
    warehouse.addItem(new Item("Смартфон", 45000.0));
    warehouse.addItem(new Item("Планшет", 30000.0));
    warehouse.addItem(new Item("Монитор", 25000.0));

    warehouse.printAllItems();

    cout << "\n Удаление товара по имени " << endl;
    warehouse.removeItemByName("Смартфон");
    warehouse.printAllItems();

    cout << "\n Добавление нового товара " << endl;
    warehouse.addItem(new Item("Клавиатура", 5000.0));
    warehouse.printAllItems();

    cout << "\n Попытка удалить несуществующий товар " << endl;
    warehouse.removeItemByName("Наушники");

    cout << "\n Завершение программы " << endl;
    cout << "Деструктор Warehouse автоматически очистит оставшиеся товары.\n" << endl;

    return 0;
}
