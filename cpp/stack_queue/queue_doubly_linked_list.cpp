#include <iostream>
#include <stdexcept>
#include <memory>
#include <string>

template<typename T>
class DoublyLinkedList {
private:
    struct ListNode {
        T data;
        std::shared_ptr<ListNode> next;
        std::weak_ptr<ListNode> prev;

        explicit ListNode(T value) : data(value) {
        }
    };

    std::shared_ptr<ListNode> head;
    std::shared_ptr<ListNode> tail;
    size_t size = 0;

    std::shared_ptr<ListNode> get_node_at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        std::shared_ptr<ListNode> current;
        if (index < size / 2) {
            current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
        } else {
            current = tail;
            for (size_t i = size - 1; i > index; --i) {
                current = current->prev.lock();
            }
        }
        return current;
    }

public:
    void push_back(const T &value) {
        auto new_node = std::make_shared<ListNode>(value);

        new_node->data = value;
        if (!head) {
            // если головы ещё нет
            head = new_node;
            tail = new_node;
        } else {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        size++;
    }

    void push_front(const T &value) {
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
        if (head == tail) {
            // если только один элемент, то обнулим указатели
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
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    T get_at(size_t index) {
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

    void insert(size_t index, const T &value) {
        if (index > size) {
            throw std::out_of_range("Index out of bounds");
        }
        if (index == 0) {
            push_front(value);
            return;
        }
        if (index == size) {
            push_back(value);
            return;
        }
        auto new_node = std::make_shared<ListNode>(value);
        auto current = get_node_at(index);
        auto prev_node = current->prev.lock();

        new_node->prev = prev_node;
        new_node->next = current;
        prev_node->next = new_node;
        current->prev = new_node;

        size++;
    }

    void remove(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }

        if (index == 0) {
            pop_front();
            return;
        }

        if (index == size - 1) {
            pop_back();
            return;
        }

        auto node_to_remove = get_node_at(index);
        auto prev_node = node_to_remove->prev.lock();
        auto next_node = node_to_remove->next;

        prev_node->next = next_node;
        next_node->prev = prev_node;

        node_to_remove->prev.reset();
        node_to_remove->next.reset();

        size--;
    }


    [[nodiscard]] size_t get_size() const { return size; }
    [[nodiscard]] bool is_empty() const { return size == 0; }

    [[nodiscard]] T &front() const {
        if (!head) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    [[nodiscard]] T &back() const {
        if (!tail) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }
};


template<typename T>
class MyQueue {
private:
    DoublyLinkedList<T> eternal_list;

public:
    void push_back(const T &value) {
        eternal_list.push_back(value);
    }

    void clear() {
        while (eternal_list.get_size()) {
            eternal_list.pop_front();
        }
    }

    [[nodiscard]] size_t size() const {
        return eternal_list.get_size();
    }

    [[nodiscard]] T front() const {
        return eternal_list.front();
    }

    void pop() {
        eternal_list.pop_front();
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
    MyQueue<int> q;
    std::string input;
    while (true) {
        getline(std::cin, input);

        if (input == "exit") {
            std::cout << "bye" << std::endl;
            return 0;
        }

        if (input.find("push") != std::string::npos) {
            int value = parse_int(input);
            q.push_back(value);
            std::cout << "ok" << std::endl;

        } else if (input == "pop") {
            if (q.size() != 0) {
                std::cout << q.front() << std::endl;
                q.pop();
            } else {
                std::cout << "error" << std::endl;
            }

        } else if (input == "size") {
            std::cout << q.size() << std::endl;

        } else if (input == "clear") {
            q.clear();
            std::cout << "ok" << std::endl;

        } else if (input == "front") {
            if (q.size() != 0) {
                std::cout << q.front() << std::endl;
            } else {
                std::cout << "error" << std::endl;
            }
        }
    }
}
