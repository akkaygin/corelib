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

    n32 CachedIndex;
    node* CachedNode;

    public:
    n32 Length;

    void Initialize() {
      Head = nullptr;
      Tail = nullptr;
      Length = 0;

      CachedNode = nullptr;
    }

    void Destroy() {
      node* NextNode = Head;
      while (NextNode != Tail) {
        node* CurrentNode = NextNode;
        NextNode = CurrentNode->Next;
        free(CurrentNode);
      }
      free(Tail);

      Head = nullptr;
      Tail = nullptr;
      Length = 0;

      CachedNode = nullptr;
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

      CachedIndex = Index;
      CachedNode = NewNode;
      
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

      CachedIndex = CachedIndex + 1;
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

      if (CachedIndex == Index) {
        CachedNode = nullptr;
      } else if (CachedIndex > Index) {
        CachedIndex = CachedIndex - 1;
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

      if (CachedIndex == Length) {
        CachedNode = nullptr;
      }

      Length = Length - 1;
      return Result;
    }

    T Get(n32 Index) {
      if (Index == Length) {
        return Tail->Value;
      } else if (Index == 0) {
        return Head->Value;
      }

      node* Result = Head->Next;
      n32 i = 1;

      if (CachedNode != nullptr && CachedIndex <= Index) {
        Result = CachedNode;
        i = CachedIndex;
      }

      for (; i < Index; i++) {
        Result = Result->Next;
      }

      CachedIndex = Index;
      CachedNode = Result;
      return Result->Value;
    }
  };
};