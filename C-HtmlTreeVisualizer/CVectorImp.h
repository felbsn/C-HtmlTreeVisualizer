
#pragma once
#ifndef CVectorImp_H
#define CVectorImp_H

#include <stdio.h>
#include <stdlib.h>


    #define newVector(VectorType)({\
    VectorType vec;\
    vec.size = 0;\
    vec.capacity = 2;\
    vec.data = malloc(sizeof(*vec.data) *2 ); \
    vec; })


    #define freeVector(vec)\
    {\
      vec.size = 0;\
      vec.capacity = 0;\
      free(vec.data);\
    }

    #define VectorClear(vec)\
    {\
      vec.size = 0;\
    }


    #define VectorAppend(vec , value)({\
    if((vec).size >= (vec).capacity ) {  \
      (vec).capacity *= (vec).capacity*1.5f; \
      (vec).data = (typeof((vec).data)) realloc((vec).data ,(sizeof(*(vec).data))*(vec).capacity);}\
    (vec).data[(vec).size] = (value);\
    (vec).size++;})\


   #define VectorBinarySearch(vec , value,functorCmp)({\
  int left = 0 , right =(vec).size-1;\
  int curIndex;\
  int retIndex = -1;\
  while(retIndex < 0 && right >= left)\
  {\
    curIndex = (right+left)/2;\
    int res =  functorCmp(value  ,  (vec).data[curIndex]);\
    if(res == 0 ) {retIndex = curIndex;}\
    else\
    if(res < 0)\
    {left = curIndex+1;}\
    else\
    {right = curIndex-1;}\
  };\
  retIndex;\
  })


    #define VectorDeleteFS(vec , index )({\
    (vec).data[index] = (vec).data[(vec).size-1]; \
    (vec).size--;}) \

    #define VectorDelete(vec , index )({\
    int i;\
    for( i = index;  i <  (vec).size-1  ; i++){\
      (vec).data[i] = (vec).data[i+1];\
    }\
    (vec).size--;\
  })

    #define VectorSort(vec  , functor)({  \
     int i;\
     typeof(*(vec).data) cur;\
      for (i = 1; i < (vec).size; i++) \
      {\
       cur = (vec).data[i];\
       int j = i-1;\
       while (j >= 0 && (functor((vec).data[j] , cur) )) \
       {\
           (vec).data[j+1] = (vec).data[j];\
           j = j-1;\
       }\
       (vec).data[j+1] = cur;\
      }\
   })






 /*   void insertionSort(int arr[], int n)
{
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1;
 
        Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position 
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}*/

   /*#define VectorFind(vec , value  , functor) ({\
    if(vec.size >= vec.capacity ) {  \
      vec.capacity *= vec.capacity*1.5f; \
      vec.data = (typeof(vec.data)) realloc(vec.data ,(sizeof(*vec.data))*vec.capacity);}\
    vec.data[vec.size] = (value);\
    vec.size++;})\*/

   #define VectorReserve( vec,newSize) ({\
      if(newSize > (vec).size) \
      { \
        (vec).data = realloc((vec).data ,newSize*sizeof(*(vec).data)); \
        (vec).capacity = newSize; \
      } \
    })

    #define VectorResize( vec,newSize) ({\
      if(newSize > (vec).size) \
      { \
        (vec).data = realloc((vec).data ,newSize*sizeof(*(vec).data)); \
        (vec).capacity = newSize; \
        (vec).size = newSize;\
      } \
    })

    #define VectorShrink(vec)({\
    if((vec).size <= 2){ \
      (vec).capacity = 2; \
      (vec).data = (typeof((vec).data))realloc((vec).data ,sizeof(*(vec).data)* (vec).capacity);\
    }\
  })








#endif

