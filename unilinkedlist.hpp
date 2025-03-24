#pragma once

#include "standard.hpp"

#include <stdio.h>

namespace corelib {
  template<typename T> struct unilinkedlist {
    private:
    struct node {
      node* Next;
      T Value;
    };
    
    node* Head;
    node* Tail;

    public:
    n32 Length;

    void Initialize() {
      Head = nullptr;
      Tail = nullptr;
      Length = 0;
    }

    void Destroy() {
      node* NextNode = Head;
      while (NextNode->Next != nullptr) {
        node* CurrentNode = NextNode;
        NextNode = CurrentNode->Next;
        free(CurrentNode);
      }

      Head = nullptr;
      Tail = nullptr;
      Length = 0;
    }

    void Insert(T Value, n32 Index) {
      node* NewNode = (node*)malloc(sizeof(node));
      NewNode->Value = Value;

      if (Index == 0) {
        Push(Value);
      } else if (Index == Length) {
        Append(Value);
      } else {
        node* Previous = Head;
        for (n32 i = 0; i < Index; i++) {
          Previous = Previous->Next;
        }

        if (Previous == Tail) {
          Previous->Next = NewNode;
          Tail = NewNode;
        } else {
          NewNode->Next = Previous->Next;
          Previous->Next = NewNode;
        }
      }
      
      Length = Length + 1;
    }

    void Append(T Value) {
      node* NewNode = (node*)malloc(sizeof(node));
      NewNode->Value = Value;

      if (Head == nullptr) {
        Head = NewNode;
        Tail = Head;
      } else {
        Tail->Next = NewNode;
        Tail = NewNode;
      }
      
      Length = Length + 1;
    }

    void Push(T Value) {
      node* NewNode = (node*)malloc(sizeof(node));
      NewNode->Value = Value;

      if (Head == nullptr) {
        Head = NewNode;
        Tail = Head;
      } else {
        NewNode->Next = Head;
        Head = NewNode;
      }

      Length = Length + 1;
    }

    void Remove(n32 Index) {
      if (Index == Length) {
        Pop();
      } else if (Index == 0) {
        node* NewHead = Head->Next;
        free(Head);
        Head = NewHead;
      } else {
        node* Previous = Head;
        for (n32 i = 0; i < Index - 1; i++) {
          Previous = Previous->Next;
        }

        node* Target = Previous->Next;
        Previous->Next = Target->Next;
        free(Target);
      }

      Length = Length - 1;
    }

    T Pop() {
      T Result = Tail->Value;
      if (Head == Tail) {
        free(Head);
        Head = nullptr;
        Tail = nullptr;  
      } else {
        node* Previous = Head;
        while (Previous->Next != Tail) {
          Previous = Previous->Next;
        }

        free(Tail);
        Previous->Next = nullptr;
        Tail = Previous;
      }

      Length = Length - 1;
      return Result;
    }

    T Get(n32 Index) {
      node* Result = Head;
      for (n32 i = 0; i < Index; i++) {
        Result = Result->Next;
      }

      return Result->Value;
    }
  };
};