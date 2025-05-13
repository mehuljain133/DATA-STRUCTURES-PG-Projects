# Unit-I Basic data Structures: Primitive Data Types, Abstract Data Types, Arrays - Static and
# Dynamic, 2D Arrays, Linked Lists - Single, Doubly-linked, Circular; Stacks and Queues using arrays
# and linked lists; operations, their analysis; Applications to searching & sorting

# ----------------------------
# Primitive & Abstract Data Types
# ----------------------------

# Primitive: int, float, char, boolean (Python: int, float, str, bool)
# Abstract Data Types (ADT): List, Stack, Queue, etc.

# ----------------------------
# Static and Dynamic Arrays
# ----------------------------

# Static Array (Fixed size)
class StaticArray:
    def __init__(self, size):
        self.size = size
        self.data = [None] * size

    def set(self, index, value):
        if 0 <= index < self.size:
            self.data[index] = value

    def get(self, index):
        if 0 <= index < self.size:
            return self.data[index]

# Dynamic Array (Python list behaves like dynamic array)
class DynamicArray:
    def __init__(self):
        self.data = []

    def append(self, value):
        self.data.append(value)

    def get(self, index):
        return self.data[index]

# 2D Array (List of Lists)
class TwoDArray:
    def __init__(self, rows, cols):
        self.matrix = [[0 for _ in range(cols)] for _ in range(rows)]

    def set(self, r, c, value):
        self.matrix[r][c] = value

    def get(self, r, c):
        return self.matrix[r][c]

# ----------------------------
# Linked Lists
# ----------------------------

# Singly Linked List
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class SinglyLinkedList:
    def __init__(self):
        self.head = None

    def insert(self, data):
        new = Node(data)
        new.next = self.head
        self.head = new

    def display(self):
        curr = self.head
        while curr:
            print(curr.data, end=" -> ")
            curr = curr.next
        print("None")

# Doubly Linked List
class DNode:
    def __init__(self, data):
        self.data = data
        self.next = self.prev = None

class DoublyLinkedList:
    def __init__(self):
        self.head = None

    def insert_front(self, data):
        new = DNode(data)
        new.next = self.head
        if self.head:
            self.head.prev = new
        self.head = new

    def display(self):
        curr = self.head
        while curr:
            print(curr.data, end=" <-> ")
            curr = curr.next
        print("None")

# Circular Linked List
class CircularLinkedList:
    def __init__(self):
        self.last = None

    def insert(self, data):
        new = Node(data)
        if self.last is None:
            self.last = new
            new.next = new
        else:
            new.next = self.last.next
            self.last.next = new
            self.last = new

    def display(self):
        if self.last is None:
            print("List is empty")
            return
        temp = self.last.next
        while True:
            print(temp.data, end=" -> ")
            temp = temp.next
            if temp == self.last.next:
                break
        print("(back to head)")

# ----------------------------
# Stack and Queue using Array
# ----------------------------

class StackArray:
    def __init__(self):
        self.stack = []

    def push(self, item):
        self.stack.append(item)

    def pop(self):
        return self.stack.pop() if self.stack else None

    def peek(self):
        return self.stack[-1] if self.stack else None

class QueueArray:
    def __init__(self):
        self.queue = []

    def enqueue(self, item):
        self.queue.append(item)

    def dequeue(self):
        return self.queue.pop(0) if self.queue else None

# ----------------------------
# Stack and Queue using Linked List
# ----------------------------

class StackLinkedList:
    def __init__(self):
        self.head = None

    def push(self, data):
        new = Node(data)
        new.next = self.head
        self.head = new

    def pop(self):
        if self.head is None:
            return None
        temp = self.head.data
        self.head = self.head.next
        return temp

class QueueLinkedList:
    def __init__(self):
        self.front = self.rear = None

    def enqueue(self, data):
        new = Node(data)
        if self.rear is None:
            self.front = self.rear = new
        else:
            self.rear.next = new
            self.rear = new

    def dequeue(self):
        if self.front is None:
            return None
        temp = self.front.data
        self.front = self.front.next
        if self.front is None:
            self.rear = None
        return temp

# ----------------------------
# Searching Algorithms
# ----------------------------

def linear_search(arr, key):
    for i in range(len(arr)):
        if arr[i] == key:
            return i
    return -1

def binary_search(arr, key):
    low, high = 0, len(arr) - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] == key:
            return mid
        elif key < arr[mid]:
            high = mid - 1
        else:
            low = mid + 1
    return -1

# ----------------------------
# Sorting Algorithms
# ----------------------------

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]

def selection_sort(arr):
    n = len(arr)
    for i in range(n):
        min_i = i
        for j in range(i+1, n):
            if arr[j] < arr[min_i]:
                min_i = j
        arr[i], arr[min_i] = arr[min_i], arr[i]

def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j+1] = arr[j]
            j -= 1
        arr[j+1] = key

# ----------------------------
# Usage Example
# ----------------------------

if __name__ == "__main__":
    # Stack example
    print("Stack Example:")
    s = StackArray()
    s.push(10)
    s.push(20)
    print("Popped:", s.pop())

    # Queue example
    print("\nQueue Example:")
    q = QueueLinkedList()
    q.enqueue(1)
    q.enqueue(2)
    print("Dequeued:", q.dequeue())

    # Linked List
    print("\nSingly Linked List:")
    l = SinglyLinkedList()
    l.insert(5)
    l.insert(10)
    l.display()

    # Searching
    print("\nBinary Search:")
    arr = [1, 3, 5, 7, 9]
    print("Index of 5:", binary_search(arr, 5))

    # Sorting
    print("\nSorting Example:")
    unsorted = [64, 34, 25, 12, 22, 11, 90]
    bubble_sort(unsorted)
    print("Bubble Sorted:", unsorted)
