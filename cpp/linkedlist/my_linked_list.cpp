#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class DoublyLinkedList {
private:
    struct ListNode {
        T data;
        std::shared_ptr<ListNode> next;
        std::weak_ptr<ListNode> prev;

        explicit ListNode(T value): data(value) {}
    };
    std::shared_ptr<ListNode> head;
    std::shared_ptr<ListNode> tail;
    size_t size = 0;

public:
    void push_back(const T& value) {
        auto new_node = std::make_shared<ListNode>(value);

        new_node->data = value;
        if (!head) { // если головы ещё нет
            head = new_node;
            tail = new_node;
        } else {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        size++;
    }
    void push_front(const T& value) {
        auto new_node = std::make_shared<ListNode>(value);
        if (!head) {
            head = new_node;
            tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        size++;
    }
    void pop_back() {
        if (!tail) {
            return;
        }
        if (head == tail) { // если только один элемент, то обнулим указатели
            head.reset();
            tail.reset();
        } else {
            auto new_tail = tail->prev.lock(); // элемент перед хвостом
            if (new_tail) {
                new_tail->next.reset(); // обнулили указатель на удалённый хвост
                tail = new_tail;
            }
        }
        size--;
    }
    void pop_front() {
        if (!head) {
            return;
        }
        if (head == tail) {
            head.reset();
            tail.reset();
        } else {
            auto new_head = head->next;
            if (new_head) {
                new_head->prev.reset();
                head = new_head;
            }
        }
        size--;
    }
    void print() {
        auto current = head;
        while (current) {
            std::cout<<current->data<<" ";
            current = current->next;
        }
        std::cout<<std::endl;
    }
    T get_val(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index is more than size of list");
        }
        auto current = head;
        while (current && index > 0) {
            current = current->next;
            index--;
        }
        // здесь гарантированно current != nullptr, так как мы проверили index
        return current->data;
    }
    [[nodiscard]] size_t get_size() const {
        return size;
    }

};

int main() {
    DoublyLinkedList<int> list;

    std::cout << "Empty list size: " << list.get_size() << std::endl;

    list.push_back(100);
    list.pop_back();
    std::cout << "After push/pop single: " << list.get_size() << std::endl;

    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    list.print();

    while (list.get_size() > 0) {
        list.pop_back();
        list.print();
    }
}
