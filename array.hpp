#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

namespace corelib {
  template<typename T> struct array {
    unsigned Capacity;
    unsigned Length;
    T* Data;

    void Initialize(int Capacity = 2) {
      Capacity = 2;
      Length = 0;
      Data = (T*)malloc(2 * sizeof(T));
    }

    void Destroy() {
      free(Data);
      Data = nullptr;
    }

    void Resize(int Target) {
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

    void Remove(int Index) {
      if (Length > 0) {
        Length = Length - 1;
        Data[Index] = Data[Length];

        if (Length < Capacity / 4) {
          Resize(Capacity / 2);
        }
      }
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