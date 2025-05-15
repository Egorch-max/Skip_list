#pragma once
#include <iostream>
#include <cstdlib>
#include <stdexcept>

struct XNode
{
    int data;

    XNode* right;

    XNode* bottom;

    XNode* top;

    XNode(int val, XNode* b = nullptr, XNode* r = nullptr, XNode* t = nullptr)

        : data(val), bottom(b), right(r), top(t) {}

    ~XNode()
    {
        right = nullptr;

        bottom = nullptr;

        top = nullptr;
    }
};

class Skip_list
{
private:

    XNode* root;

    int height;

    XNode* addElement(XNode* current, int val)
    {
        while (current->right && current->right->data < val)
        {
            current = current->right;
        }

        XNode* lowerNode = nullptr;

        if (current->bottom)
        {
            lowerNode = addElement(current->bottom, val);
        }

        if (lowerNode || !current->bottom)
        {
            XNode* newNode = new XNode(val, lowerNode, current->right);

            current->right = newNode;

            if (lowerNode)
            {
                lowerNode->top = newNode;
            }

            return (rand() % 2 == 0) ? newNode : nullptr;
        }
        return nullptr;
    }

    void removeElement(XNode* current, int val)
    {
        if (!locate(val))
        {
            throw std::logic_error("Element not present");
        }

        while (current->right && current->right->data < val)
        {
            current = current->right;
        }

        if (current->bottom)
        {
            removeElement(current->bottom, val);
        }

        if (current->right && current->right->data == val)
        {
            XNode* temp = current->right;

            current->right = temp->right;

            delete temp;
        }
    }

public:
    Skip_list() : root(nullptr), height(0) {}

    explicit Skip_list(int levels) : height(levels)
    {
        root = new XNode(0);

        XNode* temp = root;

        for (int i = 1; i < height; ++i)
        {
            temp->bottom = new XNode(0);

            temp->bottom->top = temp;

            temp = temp->bottom;
        }
        temp->bottom = new XNode(0);
    }

    ~Skip_list()
    {
        XNode* level = root;

        while (level)
        {
            XNode* curr = level;

            level = level->bottom;

            while (curr)
            {
                XNode* next = curr->right;

                delete curr;

                curr = next;
            }
        }
    }

    int getHeight() const noexcept
    {
        return height;
    }

    void insert(int val)
    {
        addElement(root, val);
    }

    void erase(int val)
    {
        removeElement(root, val);
    }

    XNode* locate(int val) const
    {
        XNode* curr = root;

        while (curr)
        {
            while (curr->right && curr->right->data < val)
            {
                curr = curr->right;
            }

            if (curr->right && curr->right->data == val)
            {
                XNode* found = curr->right;

                while (found->bottom)
                {
                    found = found->bottom;
                }
                return found;
            }
            curr = curr->bottom;
        }
        return nullptr;
    }

    void display() const
    {
        XNode* level = root;

        int levelCount = 0;

        while (level)
        {
            std::cout << "Layer " << levelCount++ << ": ";

            XNode* curr = level->right;

            while (curr)
            {
                std::cout << curr->data << " ";

                curr = curr->right;
            }
            std::cout << std::endl;

            level = level->bottom;
        }
    }
};