#include <iostream>
#include <stdexcept>
#include <memory>
#include <string>

/*
Стек на односвязном списке
*/

template<typename T>
class SinglyLinkedList {
private:
    struct ListNode {
        T data;
        std::shared_ptr<ListNode> next;

        explicit ListNode(const T &value) : data(value) {
        }
    };

    std::shared_ptr<ListNode> head;
    std::weak_ptr<ListNode> tail;
    size_t size = 0;

public:
    void push_back(const T &value) {
        auto new_node = std::make_shared<ListNode>(value);
        new_node->data = value;
        if (!head) {
            head = new_node;
            tail = new_node;
        } else {
            tail.lock()->next = new_node;
            tail = new_node;
        }
        size++;
    }

    void push_front(const T &value) {
        auto new_node = std::make_shared<ListNode>(value);
        new_node->data = value;
        if (!head) {
            head = new_node;
            tail = new_node;
        } else {
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

    [[nodiscard]] T &front() const {
        if (!head) {
            throw std::out_of_range("list is empty");
        }
        return head->data;
    }

    T &back() {
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

    T &get_val_at(size_t index) {
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


template<typename T>
class MyStack {
private:
    SinglyLinkedList<T> eternal_list;

public:
    void push(T value) {
        eternal_list.push_front(value); // O(1)
    }

    void pop() {
        eternal_list.pop_front();
    }

    [[nodiscard]] T back() const {
        return eternal_list.front();
    }

    [[nodiscard]] size_t size() const {
        return eternal_list.get_size();
    }

    void clear() {
        while (eternal_list.get_size()) {
            eternal_list.pop_front();
        }
    }
};

int parse_int(const std::string &str) {
    auto pos = str.find_first_not_of("push ");
    if (pos != std::string::npos) {
        auto value = str.substr(pos);
        return std::stoi(value);
    }
    throw std::invalid_argument("Invalid input");
}


int main() {
    MyStack<int> st;
    std::string input;
    while (true) {
        getline(std::cin, input);

        if (input == "exit") {
            std::cout << "bye" << std::endl;
            return 0;
        }
        if (input.find("push") != std::string::npos) {
            int value = parse_int(input);
            st.push(value);
            std::cout << "ok" << std::endl;
        } else if (input == "pop") {
            if (st.size() != 0) {
                std::cout << st.back() << std::endl;
                st.pop();
            } else {
                std::cout << "error" << std::endl;
            }
        } else if (input == "size") {
            std::cout << st.size() << std::endl;
        } else if (input == "clear") {
            st.clear();
            std::cout << "ok" << std::endl;
        } else if (input == "back") {
            if (st.size() != 0) {
                std::cout << st.back() << std::endl;
            } else {
                std::cout << "error" << std::endl;
            }
        }
    }
}
