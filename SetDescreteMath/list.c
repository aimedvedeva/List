#include <stdlib.h>
#include "list.h"

ListElement *CreateAdditionalElement(){
  ListElement *AdditionalElement = (ListElement*)malloc(sizeof(ListElement));
  AdditionalElement->ListElementsNum = 0;
  AdditionalElement->Next = NULL;
  AdditionalElement->Prev = NULL;
  return AdditionalElement;
}

ListHead *CreateList(){
  ListHead *NewList = (ListHead*)malloc(sizeof(ListHead));
  ListElement *AdditionalElement = CreateAdditionalElement();
  NewList->AdditionalElement = AdditionalElement;
  return NewList;
}

ListElement *CreateListElement(void *Data){
  ListElement *Element = (ListElement*)malloc(sizeof(ListElement));
  Element->Next = NULL;
  Element->Prev = NULL;
  Element->Data = Data;
  return Element;
}

void ClearElementMemory(ListElement *Element){
  free(Element->Data);
}

ListElement *SearchElement(ListHead *ListHead, void *Data, void (*Comparator) (void *, void *, Variants *)){
  if (ListHead->AdditionalElement->ListElementsNum == 0){
    return ListHead->AdditionalElement;
  }

  if (ListHead->AdditionalElement->ListElementsNum == 1){
    Variants *ResultOfComparing = (Variants*)malloc(sizeof(Variants));
    Comparator(ListHead->AdditionalElement->Next->Data, Data, ResultOfComparing);
    if (ResultOfComparing < 0){
      free(ResultOfComparing);
      return ListHead->AdditionalElement;
    }
    else if (ResultOfComparing > 0){
      free(ResultOfComparing);
      return ListHead->AdditionalElement->Next;
    }
    else if (ResultOfComparing == 0){
      free(ResultOfComparing);
      return NULL;
    }
  }

  if (ListHead->AdditionalElement->ListElementsNum > 1){
    
    ListElement *Iterator = ListHead->AdditionalElement->Next;
    while (Iterator->Next != NULL){
      Variants *ResultOfComparing = (Variants*)malloc(sizeof(Variants));
      Comparator(Iterator->Data, Data, ResultOfComparing);
      if (*ResultOfComparing == Variants_Less){
        Iterator = Iterator->Next;
      }
      else if (*ResultOfComparing == Variants_Equal){
        free(ResultOfComparing);
        return NULL;
      }
      else if (*ResultOfComparing == Variants_Bigger){
        free(ResultOfComparing);
        return Iterator->Prev;
      }
      free(ResultOfComparing);
    }
    
    return Iterator->Prev;
  }
  
}

MyBool AddElement(ListHead *ListHead, void *Data, void (*Comparator) (void *, void *, Variants *)){
  ListElement *NewElement = CreateListElement(Data);
  ListElement *PrevElement = SearchElement(ListHead, Data, Comparator);

  if (PrevElement == NULL){
    return MyBool_false;
  }

  NewElement->Next = PrevElement->Next;
  NewElement->Prev = PrevElement;
  if (PrevElement->Next != NULL){
    PrevElement->Next->Prev = NewElement;
  }
  PrevElement->Next = NewElement;

  ListHead->AdditionalElement->ListElementsNum += 1;

  return MyBool_true;
}

void DeleteElement(ListHead *ListHead, void *Data, MyBool(*Comparator) (void *, void *)){

  ListElement *Iterator = ListHead->AdditionalElement->Next;

  while (Iterator != NULL){
    if (Comparator(Iterator->Data, Data)){
      ClearElementMemory(Iterator);
      if (Iterator->Prev != NULL){
        Iterator->Prev->Next = Iterator->Next;
      }
      if (Iterator->Next != NULL){
        Iterator->Next->Prev = Iterator->Prev;
      }
      free(Iterator);
      ListHead->AdditionalElement->ListElementsNum -= 1;
      return;
    }
    Iterator = Iterator->Next;
  }
}

void DeleteList(ListHead *ListHead){
  ListElement *Iterator = ListHead->AdditionalElement->Next;

  while (Iterator != NULL){
    ListElement *Tmp = Iterator->Next;
    ClearElementMemory(Iterator);
    free(Iterator);
    Iterator = Tmp;
  }

  free(ListHead->AdditionalElement);
  free(ListHead);
}

void ForEachElementOfList(ListHead *ListHead, void (*Do) (void *ListElementData)){
  ListElement *Iterator = ListHead->AdditionalElement->Next;

  while (Iterator != NULL){
    Do(Iterator->Data);
    Iterator = Iterator->Next;
  }
}