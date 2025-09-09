#include <iostream>
#include <memory>
#include <stdexcept>

/*
Односвязный список.

Добавление/удаление в начало: O(1).

Добавление в конец: O(1)

Удаление из конца не реализуется в данной структуре, ввиду того, что это будет стоить O(n)
на каждый запрос.

Доступ к случайному элементу: O(n)
*/


template<typename T>
class SinglyLinkedList {
private:
    struct ListNode {
        T data;
        std::shared_ptr<ListNode> next;

        explicit ListNode(const T &value) : data(value) {}
    };
    std::shared_ptr<ListNode> head;
    std::weak_ptr<ListNode> tail;
    size_t size = 0;

public:
    void push_back(const T& value) {
        auto new_node = std::make_shared<ListNode>(value);
        new_node->data = value;
        if (!head) {
            head = new_node;
            tail = new_node;
        }
        else {
            tail.lock()->next = new_node;
            tail = new_node;
        }
        size++;

    }
    void push_front(const T& value) {
        auto new_node = std::make_shared<ListNode>(value);
        new_node->data = value;
        if (!head) {
            head = new_node;
            tail = new_node;
        }
        else {
            new_node->next = head;
            head = new_node;
        }
        size++;
    }
    void pop_front() {
        if (!head) {
            return;
        }
        head = std::move(head->next); // удалятся старый head
        if (!head) {
            tail.reset();
        }
        size--;
    }
    T& front() {
        if (!head) {
            throw std::out_of_range("list is empty");
        }
        return head->data;
    }
    T& back() {
        if (auto shared_tail = tail.lock()) {
            return shared_tail->data;
        }
        throw std::out_of_range("list is empty");
    }
    void print() const {
        auto current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
    T& get_val(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        auto current = head;
        while (current && index > 0) {
            index--;
            current = current->next;
        }
        return current->data;
    }
    [[nodiscard]] size_t get_size() const {
        return size;
    }

};

int main() {
     // тесты
    SinglyLinkedList<int> list;

    for (int i = 0; i < 6; i++) {
        list.push_back(i);
    }

    list.print();
    list.pop_front();
    list.print();

    list.push_front(-10);
    list.push_front(100);
    list.print();

    std::cout << list.front() << std::endl;
    std::cout << list.back() << std::endl;
    std::cout << list.get_size() << std::endl;

    std::cout<<list.get_val(5)<<std::endl;

    return 0;
}
