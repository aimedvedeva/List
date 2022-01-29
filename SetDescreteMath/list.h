#pragma once

typedef struct tag_ListElement{
  struct tag_ListElement *Next;
  struct tag_ListElement *Prev;

  union{
    void *Data;
    int ListElementsNum;
  };
  
}ListElement;

typedef struct tag_ListHead{
  ListElement *AdditionalElement;
}ListHead;

typedef enum{
  Variants_Less = -1,
  Variants_Bigger = 1,
  Variants_Equal = 0
}Variants;

typedef enum{
  MyBool_false,
  MyBool_true
}MyBool;

ListHead *CreateList();
ListElement *SearchElement(ListHead *ListHead, void *Data, MyBool(*Comparator) (void *, void *));
MyBool AddElement(ListHead *ListHead, void *Data, void(*Comparator) (void *, void *, Variants *));
void DeleteElement(ListHead *ListHead, void *Data, MyBool(*Comparator) (void *, void *));
void ForEachElementOfList(ListHead *ListHead, void(*Do) (void *ListElementData));
void DeleteList(ListHead *ListHead);
