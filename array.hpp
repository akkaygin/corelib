#pragma once

#include "standard.hpp"

namespace corelib {
  template<typename T> struct array {
    n32 Capacity;
    n32 Length;
    T* Data;

    void Initialize(n32 Capacity = 2) {
      Capacity = 2;
      Length = 0;
      Data = (T*)malloc(2 * sizeof(T));
    }

    void Destroy() {
      free(Data);
      Data = nullptr;
    }

    void Resize(n32 Target) {
      Capacity = Target;
      Data = (T*)realloc(Data, Capacity * sizeof(T));
    }

    void Append(T Value) {
      if (!(Length < Capacity)) {
        Resize(Capacity * 2);
      }

      Data[Length] = Value;
      Length = Length + 1;
    }

    void Remove(n32 Index) {
      if (Length > 0) {
        Length = Length - 1;
        Data[Index] = Data[Length];

        if (Length < Capacity / 4) {
          Resize(Capacity / 2);
        }
      }
    }

    T Pop() {
      T Result = Data[Length];
      Remove(Length);
      return Result;
    }

    array<T>* Copy() {
      array<T>* Result = (array<T>*)malloc(sizeof(array<T>));
      Result->Capacity = Capacity;
      Result->Length = Length;
      Result->Data = (T*)malloc(Result->Capacity * sizeof(T));
      memcpy(Result->Data, Data, Length * sizeof(T));
      return Result;
    }
  };
};