class SingleListNode:
    def __init__(self, value):
        self.value = value
        self.next: [SingleListNode, None] = None


class SinglyLinkedList:
    def __init__(self):
        self.__head: [SingleListNode, None] = None
        self.__tail: [SingleListNode, None] = None
        self.__size: int = 0

    def push_back(self, value):
        new_node = SingleListNode(value)

        if not self.__head:
            self.__head = new_node
        else:
            self.__tail.next = new_node

        self.__tail = new_node
        self.__size += 1

    def push_front(self, value):
        new_node = SingleListNode(value)
        if not self.__tail:
            self.__tail = new_node
        else:
            new_node.next = self.__head

        self.__head = new_node

    def pop_front(self):
        pass
        self.__size += 1

    def print_elements(self):
        """
        Это не Python стиль, но я должен показать алгоритмический смысл
        """
        current = self.__head
        print("{", end="")
        while current:
            ending = ", " if current.next else ""
            print(current.value, end=ending)
            current = current.next
        print("}")

    def insert(self, index: int, value):
        if not (0 <= index < self.__size):
            raise IndexError("Ошибка: индекс вне диапазона")

        if index == 0:
            self.push_front(value)
            return
        if index == self.__size - 1:
            self.push_back(value)
            return

        new_node = SingleListNode(value)
        current = self.__head
        for _ in range(index-1):
            current = current.next

        new_node.next = current.next
        current.next = new_node
        self.__size += 1

    def remove(self, index: int):
        if not (0 <= index < self.__size):
            raise IndexError("Ошибка: индекс вне диапазона")

        if index == 0:
            self.pop_front()
            return
        current = self.__head
        for _ in range(index-1):
            current = current.next

        current.next = current.next.next
        self.__size -= 1


    def head(self):
        if not self.__head:
            raise IndexError("Обращение к пустому списку")

        return self.__head.value

    def tail(self):
        if not self.__tail:
            raise IndexError("Обращение к пустому списку")
        return self.__tail.value

    @property
    def size(self):
        return self.__size

