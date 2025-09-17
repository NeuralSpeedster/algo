from linked_list.singly_linked_list import SinglyLinkedList

if __name__ == '__main__':
    l1 = SinglyLinkedList()

    for i in range(5):
        l1.push_back(i)

    l1.print_elements()  # {0, 1, 2, 3, 4}

    l1.push_front(10)
    l1.print_elements()  # {10, 0, 1, 2, 3, 4}

    l1.insert(2, 100)
    l1.print_elements()  # {10, 0, 100, 1, 2, 3, 4}

    l1.remove(3)
    l1.print_elements()

