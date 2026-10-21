#include "Queue.h"
#include <iostream>
using namespace std;

Queue::Queue()
{
    front = nullptr;
    rear = nullptr;
    count = 0;
}

Queue::~Queue()
{
    int dummy;
    while (dequeue(dummy));
}

void Queue::enqueue(int value)
{
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    if (isEmpty())
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    count++;
}

bool Queue::dequeue(int& value)
{
    if (isEmpty())
        return false;

    Node* temp = front;
    value = front->data;
    front = front->next;
    if (front == nullptr)
    {
        rear = nullptr;
    }
    delete temp;
    count--;
    return true;
}

bool Queue::peek(int& value) const
{
    if (isEmpty())
        return false;

    value = front->data;
    return true;
}

bool Queue::isEmpty() const
{
    return front == nullptr;
}

int Queue::size() const
{
    return count;
}

void Queue::display() const
{
    cout << "front ->";
    if (isEmpty())
    {
        cout << " (empty)";
    }
    else
    {
        Node* curr = front;
        while (curr != nullptr)
        {
            cout << " " << curr->data;
            curr = curr->next;
        }
    }
    cout << " <- rear" << endl;
}